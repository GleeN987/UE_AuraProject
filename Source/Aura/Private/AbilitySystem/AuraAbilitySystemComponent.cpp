// Copyright GleeN


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//get effect tags to broadcast them to widget controller so we can show something in hud
	FGameplayTagContainer EffectTags;
	EffectSpec.GetAllAssetTags(EffectTags);
	for (const FGameplayTag& Tag : EffectTags)
	{
		//broadcast tags to widget controller
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Tag.ToString());
	}
}
