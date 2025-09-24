#include "HW7GameMode.h"
#include "HW7Pawn.h"
#include "HW7PlayerController.h"

AHW7GameMode::AHW7GameMode()
{
	DefaultPawnClass = AHW7Pawn::StaticClass();
	PlayerControllerClass = AHW7PlayerController::StaticClass();
}

