#include "ColorBot.h"


ColorBot::ColorBot(int threshold, int activationKey) : HoldableModule(activationKey), threshold(threshold)
{
    SetProcessDPIAware();
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
    memify mem("cs2.exe");
    uintptr_t client = mem.GetBase("client.dll"); //Acha a base do client.dll (módulo principal do CS2 para entidades, mira etc)

    int delayx = std::rand() % (90 - 70 + 1) + 70;
    int delayy = std::rand() % (30 - 10 + 1) + 10;

    while (IsKeyHolded(GetKey()))
    {
        auto localPlayer = mem.Read<uintptr_t>(client + cs2_dumper4::offsets::client_dll::dwLocalPlayerPawn); //Acha a instancia do jogador 1a pessoa.
        int entIndex = mem.Read<int>(localPlayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iIDEntIndex); //Acha a instancia de quem está na mira.
        //Utils utils;
        //utils.ConsoleClear();
        //std::cout << "Entidade: <"<< static_cast<int>(entIndex) << std::endl;

        if (entIndex > 0) //O valor da instancia é -1 se nao tiver mirando em nada, e um valor >0 se tiver algo na mira.
        {
            sleep_for(milliseconds(delayy));
            arduino.WriteMessage("MOUSE_LEFT_CLICK");
            sleep_for(milliseconds(delayx));
        }
        else sleep_for(milliseconds(delayx));

    }
}


