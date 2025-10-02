#include "FastReload.h"
#include "RecoilControl.h"

#include <iostream>
#include <cstdlib>   // Para rand() e srand()
#include <ctime>     // Para time()

#include "offsets.hpp" //cs2_dumper4
#include "buttons.hpp" // #cs2_dumper1
#include "client_dll.hpp" // #cs2_dumper
#include "mem.hpp"
#include "recoil.hpp"

#include <thread>  // Necessário para std::this_thread::sleep_for
#include <chrono>  // Necessário para std::chrono::milliseconds

#define ATTACKING 0x10001
#define NOTATTACKING 0x101

bool isAttacking;
bool wasAttacking = false;
Vec3 originalViewAngles;
Vec3 oPunch{ 0,0, 0 };

RecoilControl::RecoilControl(ModuleManager& manager) : manager(manager), weapon(OFF) {}


void RecoilControl::Control(Arduino& arduino, const Config& config)
{
    if (1) //Routine for activation ? Toggleable module.
    {
        memify mem("cs2.exe");
        uintptr_t client = mem.GetBase("client.dll"); //Acha a base do client.dll (módulo principal do CS2 para entidades, mira etc)
        auto localPlayer = mem.Read<uintptr_t>(client + cs2_dumper4::offsets::client_dll::dwLocalPlayerPawn); //Acha a instancia do jogador 1a pessoa.
        bool isAttacking = (mem.Read<int>(client + cs2_dumper1::buttons::attack) == ATTACKING);
        int numShots = mem.Read<int>(localPlayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iShotsFired);

        //std::cout << mem.Read<int>(localPlayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_pClippingWeapon + cs2_dumper::schemas::client_dll::C_AttributeContainer::m_Item) << std::endl;

        if (!isAttacking || numShots < 1)
        {
            //std::cout << "SEM ATIRAR" << std::endl; // debug line
            if (wasAttacking)
            {
                //mem.Write<Vec3>(client + cs2_dumper4::offsets::client_dll::dwViewAngles, originalViewAngles);
                wasAttacking = false;
            }
            oPunch.x = oPunch.y = 0;
            return;
        }


        if (numShots == 1 && !wasAttacking)
        {
            std::cout << "Shooting!" << std::endl; // debug line
            originalViewAngles = mem.Read<Vec3>(client + cs2_dumper4::offsets::client_dll::dwViewAngles);
            wasAttacking = true;
        }

        C_UTL_VECTOR aimPunchCache = mem.Read<C_UTL_VECTOR>(localPlayer + cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchCache);
        Vec3 currentViewAngles = mem.Read<Vec3>(client + cs2_dumper4::offsets::client_dll::dwViewAngles);

        Vec2 aimPunchAngle = mem.Read<Vec2>(aimPunchCache.data + (aimPunchCache.count - 1) * sizeof(Vec3));

        if (numShots > 0)
        {
            Vec3 newViewAngles{
                currentViewAngles.x - (aimPunchAngle.x - oPunch.x) * 2.f, //Engine do CS2 envia só metade do angulo.
                currentViewAngles.y - (aimPunchAngle.y - oPunch.y) * 2.f,
                0.f
            };
            newViewAngles.Normalize();

            //DEBUG printando os angulos.

            std::cout << "newViewAngles: ("
                << newViewAngles.x << ", "
                << newViewAngles.y << ", "
                << newViewAngles.z << ")"
                << std::endl;

            float sensitivity = config.GetSensitivity(); /* buscar do config. */;
            float yawFactor = 0.022f; // Valor típico do CS:GO/CS2 para conversão yaw
            float pitchFactor = 0.022f; // Idem

            currentViewAngles.Normalize();

            // Replique exatamente o cálculo do código original:
            float mouseMoveX = -(-(aimPunchAngle.y - oPunch.y) * 2.f / (yawFactor * sensitivity));
            float mouseMoveY = -(aimPunchAngle.x - oPunch.x) * 2.f / (pitchFactor * sensitivity);

            //std::srand(std::time(nullptr));

            // Gera um número aleatório entre 30 e 50, inclusive para piorar o movimento.
            //int valor = std::rand() % (max - min + 1) + min;

            int delayx = std::rand() % (50 - 30 + 1) + 30;
            int smoothness = std::rand() % (8 - 2 + 1) + 2;

            // MELHORAR ESSA PARTE DO ARDUINO, POIS ELE NÃO USA O DELAY.

             arduino.WriteMessage("MOUSE_LEFT_HOLDED:"
                                + to_string(mouseMoveX)
                                + "," + to_string(mouseMoveY) 
                                + "," + to_string(smoothness)
                                ); //Arduino usa isso pra smoothness
             //std::cout << "Comando: <"<< ("MOUSE_LEFT_HOLDED:" + to_string(mouseMoveX) + "," + to_string(mouseMoveY) + "," + to_string(smoothness)) << "> " << std::endl;
             sleep_for(milliseconds(delayx));

             /*Fica no prego, mas escreve na memoria, cuidado ao usar!!! */
            //mem.Write<Vec3>(client + cs2_dumper4::offsets::client_dll::dwViewAngles, newViewAngles);
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        oPunch.x = aimPunchAngle.x;
        oPunch.y = aimPunchAngle.y;
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}





void RecoilControl::Execute(Arduino& arduino, const Config& config)
{
    weapon = GetWeaponState(weapon, config);
    if (weapon == OFF) return;

    double obs = 0.75 / config.GetZoomSensitivity();
    double modifier = CalculateModifier(config, obs);

    WeaponData data = GetWeaponData(weapon, modifier);

    if (!ValidateWeaponData(data))
    {
        weapon = OFF;
        return;
    }
    Control(arduino,config); //Novo controle via memoria.
    //ProcessRecoilData(arduino, config, data);
}

double RecoilControl::CalculateModifier(const Config& config, double obs)
{
    double modifier = 2.52 / config.GetSensitivity();
    return IsKeyHolded(VK_RBUTTON) ? modifier * obs : modifier;
}

bool RecoilControl::ValidateWeaponData(const WeaponData& data)
{
    return data.x.size() == data.y.size() && data.x.size() == data.delay.size();
}

void RecoilControl::ProcessRecoilData(Arduino& arduino, const Config& config, const WeaponData& data)
{
    for (size_t i = 0; i < data.x.size(); i++)
    {
        if (!IsKeyHolded(VK_LBUTTON) || (config.GetConfirmationKey() != 0 && !IsKeyHolded(config.GetConfirmationKey())))
        {
            return;
        }
        arduino.WriteMessage("MOUSE_LEFT_HOLDED:" + to_string(data.x[i]) + "," + to_string(data.y[i]) + "," + to_string(data.delay[i]));
        sleep_for(milliseconds(data.delay[i]));
    }

    arduino.WriteMessage("MOUSE_LEFT_CLICK");

    if (auto* fastReload = manager.GetModule<FastReload>("FastReload"))
    {
        fastReload->SetCurrentWeapon(weapon);
        fastReload->Process(arduino, config);
    }
}