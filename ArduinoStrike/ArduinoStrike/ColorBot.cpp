#include "ColorBot.h"

// Base de entidades.
// https://cs2.poggu.me/dumped-data/entity-list#list-of-all-entities

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
    //memify mem("cs2.exe");
    uintptr_t client = mem.GetBase("client.dll"); //Acha a base do client.dll (módulo principal do CS2 para entidades, mira etc)

    int delayx = std::rand() % (20 - 5 + 1) + 5;
    int delayy = std::rand() % (160 - 120 + 1) + 120;

    while (IsKeyHolded(GetKey()))
    {
        auto localPlayer = mem.Read<uintptr_t>(client + cs2_dumper4::offsets::client_dll::dwLocalPlayerPawn); //Acha o endereço das informações do jogador 1a pessoa.
        int entIndex = mem.Read<int>(localPlayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iIDEntIndex); //Acha a instancia de quem está na mira da 1a pessoa.
        
        auto entityList = mem.Read<uintptr_t>(client + cs2_dumper4::offsets::client_dll::dwEntityList); //Address for the Game entity list
        int localTeam = mem.Read<int>(localPlayer + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum); //Here I actually read the value of the localplayer team (usually 2 or 3).

        if (!entityList) //Avoids memmory corruption or invalid reads.
        {
            std::cout << "EntityList inválido!" << std::endl;
            return;
        }
        auto listEntry = mem.Read<uintptr_t>(entityList + (8 * (entIndex >> 9) + 16)); //Get the address to that entity index that it is the crosshair.
        if (!listEntry) return; //Se leitura invalida...
        auto entity = mem.Read<uintptr_t>(listEntry + 120 * (entIndex & 0x1FF)); //Now we have the entity

        //std::cout << "Entidade: <"<< static_cast<int>(entIndex) << std::endl;

        if (entIndex > 0) //O valor da instancia é -1 se nao tiver mirando em nada, e um valor >0 se tiver algo na mira.
        {
            //sleep_for(milliseconds(5));
            int entityTeam = mem.Read<int>(entity + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);
            int entityHealth = mem.Read<int>(entity + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);

            std::cout << "Entidade: <" << static_cast<int>(entityTeam) << "Saude: <" << entityHealth << std::endl;
            if (entityTeam != localTeam)
            {
                arduino.WriteMessage("MOUSE_LEFT_CLICK");
                sleep_for(milliseconds(delayy));
            }
        }
        else sleep_for(milliseconds(5));

    }
}


