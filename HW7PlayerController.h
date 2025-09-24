#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HW7PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ASSIGNMENT7_API AHW7PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AHW7PlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	virtual void BeginPlay() override;
};
