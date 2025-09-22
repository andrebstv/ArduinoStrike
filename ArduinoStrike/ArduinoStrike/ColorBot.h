#pragma once    HWND overlayWindow

#include "HoldableModule.h"
//#include <windows.h>

class ColorBot : public HoldableModule
{
private:
    int threshold;
    //HWND overlayWindow = nullptr;
    //HWND CreateOverlayWindow();

public:
    ColorBot(int threshold, int activationKey);
    //void SetOverlayWindow(HWND hwnd) { overlayWindow = hwnd; }
    //void UpdateOverlay();

protected:
    void OnKeyHold(Arduino& arduino, const Config& config) override;

    COLORREF GetPixelColor(int x, int y) const;
    bool IsColorDifferent(COLORREF color1, COLORREF color2, int threshold) const;
};