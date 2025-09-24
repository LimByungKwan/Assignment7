#include "HW7Pawn.h"
#include "HW7PlayerController.h"
#include "EnhancedInputComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AHW7Pawn::AHW7Pawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // 루트 캡슐
    CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
    RootComponent = CapsuleComp;
    CapsuleComp->SetSimulatePhysics(false);

    // 화살표 (앞방향 표시)
    ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComp"));
    ArrowComp->SetupAttachment(CapsuleComp);

    // 메시
    MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(CapsuleComp);
    MeshComp->SetSimulatePhysics(false);

    // 스프링암
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
    SpringArmComp->SetupAttachment(CapsuleComp);
    SpringArmComp->TargetArmLength = 300.f;
    SpringArmComp->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f)); // 기본 각도

    // 카메라
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AHW7Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (AHW7PlayerController* PC = Cast<AHW7PlayerController>(GetController()))
        {
            if (PC->MoveAction)
            {
                EnhancedInput->BindAction(PC->MoveAction, ETriggerEvent::Triggered, this, &AHW7Pawn::Move);
            }
            if (PC->LookAction)
            {
                EnhancedInput->BindAction(PC->LookAction, ETriggerEvent::Triggered, this, &AHW7Pawn::Look);
            }
        }
    }
}

void AHW7Pawn::Move(const FInputActionValue& Value)
{
    FVector2D Input = Value.Get<FVector2D>();
    if (!Input.IsNearlyZero())
    {
        // ArrowComponent가 바라보는 방향
        FVector Forward = ArrowComp->GetForwardVector();
        FVector Right = ArrowComp->GetRightVector();

        FVector MoveDirection = Forward * Input.X + Right * Input.Y;
        AddActorWorldOffset(MoveDirection * 600.0f * GetWorld()->GetDeltaSeconds(), true);
    }
}

void AHW7Pawn::Look(const FInputActionValue& Value)
{
    FVector2D LookInput = Value.Get<FVector2D>();

    FRotator CurrentRotation = GetActorRotation();
    CurrentRotation.Yaw += LookInput.X * 60.0f * GetWorld()->GetDeltaSeconds();
    CurrentRotation.Pitch = 0.0f; // 평면 회전만 (Pitch 제거)

    SetActorRotation(CurrentRotation);

    PitchValue += LookInput.Y * 60.0f * GetWorld()->GetDeltaSeconds();
    PitchValue = FMath::Clamp(PitchValue, -80.0f, 80.0f); // 상하 제한

    FRotator ArmRotation = SpringArmComp->GetRelativeRotation();
    ArmRotation.Pitch = PitchValue;
    SpringArmComp->SetRelativeRotation(ArmRotation);
}
