#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HW7Pawn.generated.h"

class UCapsuleComponent;
class UArrowComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;

UCLASS()
class ASSIGNMENT7_API AHW7Pawn : public APawn
{
    GENERATED_BODY()

public:
    AHW7Pawn();

protected:
    // 루트 충돌
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCapsuleComponent* CapsuleComp;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    UArrowComponent* ArrowComp;

    // 메시
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* MeshComp;

    // 카메라
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* CameraComp;

    // 입력 처리
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    float PitchValue = 0.0f;
};
