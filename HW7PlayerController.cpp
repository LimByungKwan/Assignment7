#include "HW7PlayerController.h"
#include "EnhancedInputSubsystems.h"

AHW7PlayerController::AHW7PlayerController()
	:InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr)
{

}

void AHW7PlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}
