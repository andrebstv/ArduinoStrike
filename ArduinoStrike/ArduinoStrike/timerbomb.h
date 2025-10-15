#pragma once

#include "ToggleableModule.h"
//#define WIN32_LEAN_AND_MEAN
//#define NOMINMAX
//#define byte win_byte_override
//#undef byte
//#include "imgui/imgui.h"
//#include "imgui/backends/imgui_impl_dx12.h"
//#include "imgui/backends/imgui_impl_win32.h"

class TimerBomb : public ToggleableModule
{
public:
    TimerBomb(int activationKey);

protected:
    void OnToggleActive(Arduino& arduino, const Config& config) override;

private:
    bool isPlanted() const { return _isPlanted; };
    double secondsToBlow() const { return _secondsToBlow; };
    bool _isPlanted = false;
    double _secondsToBlow;
};