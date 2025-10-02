#pragma once
#include <Windows.h>
#include <winternl.h>  // <-- definições NTSTATUS
#include <TlHelp32.h>
#include <Psapi.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>

// Definições NTSTATUS
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#endif

#ifndef STATUS_UNSUCCESSFUL
#define STATUS_UNSUCCESSFUL ((NTSTATUS)0xC0000001L)
#endif

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

// Estrutura para armazenar informações do syscall
typedef struct _SYSCALL_INFO {
    DWORD ssn;
    PVOID syscallAddr;
} SYSCALL_INFO;

typedef NTSTATUS(WINAPI* pNtWriteVirtualMemory)(HANDLE Processhandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);

// Declaração da função assembly externa
extern "C" NTSTATUS DirectSyscall(
    DWORD ssn,
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    PVOID Buffer,
    ULONG NumberOfBytesToRead,
    PULONG NumberOfBytesRead
);

class memify
{
private:
    HANDLE handle = 0;
    DWORD processID = 0;

    SYSCALL_INFO syscallInfo = { 0 };
    bool syscallInitialized = false;

    pNtWriteVirtualMemory VWrite;

    bool InitializeSyscall() {
        if (syscallInitialized) return true;

        HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
        if (!hNtdll) return false;

        BYTE* pFunc = (BYTE*)GetProcAddress(hNtdll, "NtReadVirtualMemory");
        if (!pFunc) return false;

        // Verifica o padrão: mov r10, rcx; mov eax, [SSN]; syscall
        if (pFunc[0] == 0x4C && pFunc[1] == 0x8B && pFunc[2] == 0xD1 && pFunc[3] == 0xB8) {
            syscallInfo.ssn = *(DWORD*)(pFunc + 4);
            syscallInfo.syscallAddr = pFunc + 0x12;
            syscallInitialized = true;
            return true;
        }

        return false;
    }

    //// Wrapper para NtReadVirtualMemory via syscall direto
    NTSTATUS VRead(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead) {
        if (!syscallInitialized) {
            if (!InitializeSyscall()) {
                return STATUS_UNSUCCESSFUL;
            }
        }

        return DirectSyscall(
            syscallInfo.ssn,
            ProcessHandle,
            BaseAddress,
            Buffer,
            NumberOfBytesToRead,
            NumberOfBytesRead
        );
    }

    // Versao com debug

    /*NTSTATUS VRead(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead) {
        printf("[VRead] Iniciando leitura...\n");
        printf("[VRead] Handle: %p\n", ProcessHandle);
        printf("[VRead] Address: 0x%llX\n", (uintptr_t)BaseAddress);
        printf("[VRead] Size: %lu bytes\n", NumberOfBytesToRead);

        if (!syscallInitialized) {
            printf("[VRead] Syscall nao inicializado, tentando inicializar...\n");
            if (!InitializeSyscall()) {
                printf("[VRead ERRO] Falha ao inicializar syscall!\n");
                return STATUS_UNSUCCESSFUL;
            }
            printf("[VRead] Syscall inicializado com sucesso!\n");
        }

        printf("[VRead] SSN: 0x%X\n", syscallInfo.ssn);
        printf("[VRead] Chamando DirectSyscall...\n");

        NTSTATUS status = DirectSyscall(
            syscallInfo.ssn,
            ProcessHandle,
            BaseAddress,
            Buffer,
            NumberOfBytesToRead,
            NumberOfBytesRead
        );

        printf("[VRead] Status retornado: 0x%X\n", status);
        if (NumberOfBytesRead && *NumberOfBytesRead > 0) {
            printf("[VRead] Bytes lidos: %lu\n", *NumberOfBytesRead);
        }
        else {
            printf("[VRead] Nenhum byte lido!\n");
        }

        return status;
    }*/



    uintptr_t GetProcessId(std::string_view processName)
    {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (ss == INVALID_HANDLE_VALUE) return 0;

        while (Process32Next(ss, &pe)) {
            if (!processName.compare(pe.szExeFile)) {
                processID = pe.th32ProcessID;
                CloseHandle(ss);
                return processID;
            }
        }

        CloseHandle(ss);
        return 0;
    }

    uintptr_t GetBaseModule(std::string_view moduleName)
    {
        HMODULE modules[1024];
        DWORD neededmodule;

        if (EnumProcessModules(handle, modules, sizeof(modules), &neededmodule))
        {
            int moduleCount = neededmodule / sizeof(HMODULE);

            for (int i = 0; i < moduleCount; ++i)
            {
                char buffer[MAX_PATH];

                if (GetModuleBaseNameA(handle, modules[i], buffer, sizeof(buffer)))
                {
                    if (!moduleName.compare(buffer)) {
                        return reinterpret_cast<uintptr_t>(modules[i]);
                    }
                }
            }
        }

        return 0;
    }

public:
    memify(std::vector<std::string> processes) {
        if (!InitializeSyscall()) {
            printf("[!!] Falha ao inicializar syscall direto\n");
        }

        //VWrite = (pNtWriteVirtualMemory)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtWriteVirtualMemory");

        for (auto& name : processes) {
            processID = GetProcessId(name);

            if (processID != 0) {
                handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, processID);
                if (handle) {
                    //printf("[>>] Anexado ao processo: %s (PID: %d)\n", name.c_str(), processID);
                    break;
                }
                else {
                    printf("[!!] PID valido mas falha ao abrir handle: %s\n", name.c_str());
                    continue;
                }
            }
            continue;
        }

        if (!handle) {
            printf("[!!] Nenhum processo foi encontrado\n");
        }
    }

    memify(std::string_view processName)
    {
        if (!InitializeSyscall()) {
            printf("[!!] Falha ao inicializar syscall direto\n");
        }

        //VWrite = (pNtWriteVirtualMemory)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtWriteVirtualMemory");

        processID = GetProcessId(processName);

        if (processID != 0)
        {
            handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, processID);
            if (!handle) {
                printf("[>>] Falha ao abrir handle para o processo: %.*s\n",
                    (int)processName.length(), processName.data());
            }
            else {
                //printf("[>>] Anexado ao processo: %.*s (PID: %d)\n",
                    //(int)processName.length(), processName.data(), processID);
            }
        }
        else {
            printf("[>>] Processo nao encontrado: %.*s\n",
                (int)processName.length(), processName.data());
        }
    }

    ~memify()
    {
        if (handle)
            CloseHandle(handle);
    }

    uintptr_t GetBase(std::string_view moduleName)
    {
        return GetBaseModule(moduleName);
    }

    template <typename T>
    T Read(uintptr_t address)
    {
        T buffer{ };
        VRead(handle, (void*)address, &buffer, sizeof(T), 0);
        return buffer;
    }

    template <typename T>
    T Write(uintptr_t address, T value)
    {
        if (VWrite) {
            VWrite(handle, (void*)address, &value, sizeof(T), NULL);
        }
        return value;
    }

    bool ReadRaw(uintptr_t address, void* buffer, size_t size)
    {
        SIZE_T bytesRead = 0;
        NTSTATUS status = VRead(handle, (void*)address, buffer, static_cast<ULONG>(size), (PULONG)&bytesRead);

        return (status == 0 && bytesRead == size);
    }

    bool ProcessIsOpen(const std::string_view processName)
    {
        return GetProcessId(processName) != 0;
    }

    bool InForeground(const std::string& windowName)
    {
        HWND current = GetForegroundWindow();

        char title[256];
        GetWindowText(current, title, sizeof(title));

        if (strstr(title, windowName.c_str()) != nullptr)
            return true;

        return false;
    }

    bool IsAttached() const {
        return handle != 0;
    }

    DWORD GetPID() const {
        return processID;
    }
};
