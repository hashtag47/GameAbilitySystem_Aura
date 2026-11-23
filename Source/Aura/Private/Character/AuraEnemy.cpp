// Copyright Druid Mechanics


#include "Character/AuraEnemy.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Aura/Aura.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

AAuraEnemy::AAuraEnemy() 
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

void AAuraEnemy::BeginPlay() {
	Super::BeginPlay();

	check(AbilitySystemComponent);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AAuraEnemy::HighlightActor()
{
	//bHighlighted = true;
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Enemy highlighted!"));
	//}
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}

void AAuraEnemy::UnHighlightActor()
{
	//bHighlighted = false;
	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Enemy unhighlighted!"));
	//}
	GetMesh()->SetRenderCustomDepth(false);

	Weapon->SetRenderCustomDepth(false);
}

//void AAuraEnemy::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);

	//if (bHighlighted) {
	//	DrawDebugSphere(GetWorld(), GetActorLocation(), 32.f, 12, FColor::Red, false, 2.f);
	//}
//}

