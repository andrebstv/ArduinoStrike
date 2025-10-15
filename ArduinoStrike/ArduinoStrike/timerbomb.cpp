#include "Logger.h"
#include "timerbomb.h"

TimerBomb::TimerBomb(int activationKey) : ToggleableModule(activationKey) {}

void TimerBomb::OnToggleActive(Arduino& arduino, const Config& config)
{
   //Activates the Bomb Timer Overlay
}

