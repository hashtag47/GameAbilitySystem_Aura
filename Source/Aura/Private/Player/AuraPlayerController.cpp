// Copyright Druid Mechanics


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../../Public/Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime) 
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	// Bind EnhancedInput to the Player Controller
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	// Cursor settings
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation (0.f , Rotation.Yaw, 0.f );

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) 
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	// When use TScriptInterface<>, we don't need to manually use Cast<IEnemyInterface>(CursorHit.GetActor());
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	/**
	* Line trace from cursor. There are several scenarios:
	* A. LastActor is null && ThisActor is null
	*	- Do nothing
	* B. LastActor is null && ThisActor is valid
	*	- Highlight ThisActor
	* C. LastActor is valid && ThisActor is null
	*	- Unhighlight LastActor
	* D. Both actors are valid, but LastActor != ThisActor (Per Frame)
	*	- Unhighlight LastActor, and Highlight ThisActor
	* E. Both actors are valid, and are the same actor
	*	- Do nothing
	*/

	if (LastActor == nullptr) {
		if (ThisActor != nullptr) {
			// Case B: 
			ThisActor->HighlightActor();
		}
		else {
			// Case A: Both are null, and do nothing
		}
	}
	else {
		if (ThisActor == nullptr) {
			// Case C: 
			LastActor->UnHighlightActor();
		}
		else {
			// Both actors are valid
			if (LastActor != ThisActor) {
				// Case D: 
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else {
				// Case E: do nothing
			}
		}
	}
}

