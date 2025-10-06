#include "Weapons.h"

// flags globais para os botões extras
std::atomic<bool> g_xbutton1Down{ false };
std::atomic<bool> g_xbutton2Down{ false };
HHOOK hHook = nullptr;


LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* pMouse = (MSLLHOOKSTRUCT*)lParam;

        switch (wParam) {
        case WM_XBUTTONDOWN:
            if (HIWORD(pMouse->mouseData) == XBUTTON1) g_xbutton1Down = true;
            if (HIWORD(pMouse->mouseData) == XBUTTON2) g_xbutton2Down = true;
            break;
        case WM_XBUTTONUP:
            if (HIWORD(pMouse->mouseData) == XBUTTON1) g_xbutton1Down = false;
            if (HIWORD(pMouse->mouseData) == XBUTTON2) g_xbutton2Down = false;
            break;
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}



bool InstallMouseHook() {
    hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, GetModuleHandle(NULL), 0);
    return hHook != nullptr;
}

//bool IsKeyHolded(int vKey) {
//    if (vKey == VK_XBUTTON1) return g_xbutton1Down;
//    if (vKey == VK_XBUTTON2) return g_xbutton2Down;
//    if (vKey == VK_LBUTTON)
//    {
//        return (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
//    }
//    return (GetAsyncKeyState(vKey) & 0x8000) != 0;
//}

// thread dedicada ao hook
void HookThread() {
    hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, GetModuleHandle(NULL), 0);
    if (!hHook) {
        std::cerr << "Falha ao instalar hook\n";
        return;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
}

// função que substitui o seu IsKeyHolded
bool IsKeyHolded(int key) {
    if (key == VK_XBUTTON1) return g_xbutton1Down.load();
    if (key == VK_XBUTTON2) return g_xbutton2Down.load();
    if (key == VK_LBUTTON)
    {
        return (GetKeyState(VK_LBUTTON) & 0x8000) != 0;
    }
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}