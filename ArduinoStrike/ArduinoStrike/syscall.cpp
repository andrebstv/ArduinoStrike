#include <Windows.h>

static LPVOID g_execMemory = nullptr;
static DWORD g_currentSSN = 0xFFFFFFFF;

extern "C" NTSTATUS DirectSyscall(
    DWORD ssn,
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    PVOID Buffer,
    ULONG NumberOfBytesToRead,
    PULONG NumberOfBytesRead
) {
    // Shellcode base
    unsigned char shellcode[] = {
        0x49, 0x89, 0xCA,              // mov r10, rcx
        0xB8, 0x00, 0x00, 0x00, 0x00,  // mov eax, SSN
        0x0F, 0x05,                    // syscall
        0xC3                           // ret
    };

    // Aloca memória apenas uma vez
    if (!g_execMemory) {
        g_execMemory = VirtualAlloc(
            NULL,
            sizeof(shellcode),
            MEM_COMMIT | MEM_RESERVE,
            PAGE_EXECUTE_READWRITE
        );

        if (!g_execMemory) {
            return 0xC0000001L;
        }
    }

    // Atualiza SSN se mudou
    if (g_currentSSN != ssn) {
        *(DWORD*)(shellcode + 4) = ssn;
        memcpy(g_execMemory, shellcode, sizeof(shellcode));
        FlushInstructionCache(GetCurrentProcess(), g_execMemory, sizeof(shellcode));
        g_currentSSN = ssn;
    }

    // Tipo da função
    typedef NTSTATUS(NTAPI* SyscallFunc)(
        HANDLE, PVOID, PVOID, ULONG, PULONG
        );

    SyscallFunc func = (SyscallFunc)g_execMemory;

    // Executa o syscall
    return func(
        ProcessHandle,
        BaseAddress,
        Buffer,
        NumberOfBytesToRead,
        NumberOfBytesRead
    );
}
