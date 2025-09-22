#include "ColorBot.h"



//HWND ColorBot::CreateOverlayWindow() {
//    HWND hwnd = CreateWindowEx(
//        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
//        "OverlayClass",
//        "CS2 Overlay",
//        WS_POPUP,
//        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
//        NULL, NULL, GetModuleHandle(NULL), NULL
//    );
//
//    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
//    return hwnd;
//}

//void DrawOverlay(HDC hdc, COLORREF currentColor) {
//    SetTextColor(hdc, RGB(255, 255, 0));
//    SetBkMode(hdc, TRANSPARENT);
//
//    // Limpar a área anterior
//    RECT clearRect = { 40, 40, 400, 120 };
//    FillRect(hdc, &clearRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
//
//    // Converter COLORREF para valores RGB
//    int red = GetRValue(currentColor);
//    int green = GetGValue(currentColor);
//    int blue = GetBValue(currentColor);
//
//    // Criar strings para exibir
//    char colorText[100];
//    char rgbText[100];
//
//    sprintf_s(colorText, "Color Value: %lu", currentColor);
//    sprintf_s(rgbText, "RGB: (%d, %d, %d)", red, green, blue);
//
//    TextOut(hdc, 50, 50, colorText, strlen(colorText));
//    TextOut(hdc, 50, 70, rgbText, strlen(rgbText));
//    TextOut(hdc, 50, 90, "CPU: 45%", 8);
//}


ColorBot::ColorBot(int threshold, int activationKey) : HoldableModule(activationKey), threshold(threshold)
{
    SetProcessDPIAware();
    // Criar e configurar o overlay
    //overlayWindow = CreateOverlayWindow();
    //SetOverlayWindow(overlayWindow);

    //// Mostrar a janela
    //ShowWindow(overlayWindow, SW_SHOW);
}

COLORREF ColorBot::GetPixelColor(int x, int y) const
{
    HDC hdc = GetDC(NULL);
    COLORREF color = GetPixel(hdc, x, y);
    ReleaseDC(NULL, hdc);

    return color;
}

bool ColorBot::IsColorDifferent(COLORREF color1, COLORREF color2, int threshold) const
{
    int red1 = GetRValue(color1), green1 = GetGValue(color1), blue1 = GetBValue(color1);
    int red2 = GetRValue(color2), green2 = GetGValue(color2), blue2 = GetBValue(color2);

    return (abs(red1 - red2) > threshold || abs(green1 - green2) > threshold || abs(blue1 - blue2) > threshold);
}

void ColorBot::OnKeyHold(Arduino& arduino, const Config& config)
{
    POINT cursor;
    #define pixel_offset -3
    if (!GetCursorPos(&cursor)) return;

    COLORREF initial = GetPixelColor(cursor.x + pixel_offset, cursor.y + pixel_offset);

    while (IsKeyHolded(GetKey()))
    {
        GetCursorPos(&cursor);
        COLORREF current = GetPixelColor(cursor.x + pixel_offset, cursor.y + pixel_offset);
        //OutputDebugStringA("[DEBUGcor] Entrou no RapidFire\n");
        //std::cout << "[DEBUG] Cor = " << current << std::endl;
        // 
        // Atualizar o overlay se a janela existir
        //if (overlayWindow != nullptr) {
        //    HDC hdc = GetDC(overlayWindow);
        //    DrawOverlay(hdc, current);
        //    ReleaseDC(overlayWindow, hdc);
        //}

        if (IsColorDifferent(initial, current, threshold))
        {
            arduino.WriteMessage("MOUSE_LEFT_CLICK");
        }

        sleep_for(milliseconds(5));
    }
}


