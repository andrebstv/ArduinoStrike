#pragma once    HWND overlayWindow

#include "HoldableModule.h"
//#include <windows.h>
#include "offsets.hpp" //cs2_dumper4
#include "buttons.hpp" // #cs2_dumper1
#include "client_dll.hpp" // #cs2_dumper
#include "mem.hpp"
#include "recoil.hpp"
#include "Utils.h"

#include <thread>  // Necessário para std::this_thread::sleep_for
#include <chrono>  // Necessário para std::chrono::milliseconds
extern memify mem;

class ColorBot : public HoldableModule
{
private:
    int threshold;


public:
    ColorBot(int threshold, int activationKey);

protected:
    void OnKeyHold(Arduino& arduino, const Config& config) override;

    COLORREF GetPixelColor(int x, int y) const;
    bool IsColorDifferent(COLORREF color1, COLORREF color2, int threshold) const;
};