// Copyright Druid Mechanics


#include "Character/AuraEnemy.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

AAuraEnemy::AAuraEnemy() {
	//PrimaryActorTick.bCanEverTick = true;
}

void AAuraEnemy::HighlightActor()
{
	//bHighlighted = true;
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Enemy highlighted!"));
	//}
}

void AAuraEnemy::UnHighlightActor()
{
	//bHighlighted = false;
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Enemy unhighlighted!"));
	//}
}

void AAuraEnemy::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);

	//if (bHighlighted) {
	//	DrawDebugSphere(GetWorld(), GetActorLocation(), 32.f, 12, FColor::Red, false, 2.f);
	//}
}

