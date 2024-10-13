// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GASAbilitySystemComponent.h"
#include "GASAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayEffectModCallbackData;

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {};
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	AActor* TargetActor;

	UPROPERTY()
	AActor* SourceActor;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttrChangeDelegate, float, Attr, int32, StackCount, float, AmountChanged);

/**
 * 
 */
UCLASS()
class MYTHICISLAND_API UGASAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGASAttributeSet();
	~UGASAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	TMap<FGameplayTag, FGameplayAttribute(*)()> TagsToAttributes;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Level);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Armour)
	FGameplayAttributeData Armour;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Armour);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Block)
	FGameplayAttributeData Block;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Block);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_CriticalAccuracy)
	FGameplayAttributeData CriticalAccuracy;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, CriticalAccuracy);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_CriticalPower)
	FGameplayAttributeData CriticalPower;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, CriticalPower);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_SpellPower)
	FGameplayAttributeData SpellPower;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, SpellPower);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_SpellSpeed)
	FGameplayAttributeData SpellSpeed;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, SpellSpeed);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_LifeSteal)
	FGameplayAttributeData LifeSteal;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, LifeSteal);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MeleeResistance)
	FGameplayAttributeData MeleeResistance;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MeleeResistance);
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MagicResistance)
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MagicResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_RangedResistance)
	FGameplayAttributeData RangedResistance;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, RangedResistance);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_HealthRegenerationRate)
	FGameplayAttributeData HealthRegenerationRate;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, HealthRegenerationRate);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Speed)
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Speed);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Essence)
	FGameplayAttributeData Essence;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Essence);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxEssence)
	FGameplayAttributeData MaxEssence;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, MaxEssence);
	
	//Damage is a meta attribute used by the DamageExeceution to calculate final damage.
	//Temporary value that only exists on the server. Not Replicated.
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UGASAttributeSet, Damage);

	FAttrChangeDelegate HealthChangeDelegate;
	FAttrChangeDelegate ArmourChangeDelegate;
	FAttrChangeDelegate IntelligenceChangeDelegate;
	FAttrChangeDelegate StrengthChangeDelegate;
	FAttrChangeDelegate BlockChangeDelegate;
	FAttrChangeDelegate HealthRegnerationRateChangeDelegate;
	FAttrChangeDelegate SpeedChangeDelegate;
	FAttrChangeDelegate CriticalAccuracyChangeDelegate;
	FAttrChangeDelegate CriticalPowerChangeDelegate;
	FAttrChangeDelegate SpellPowerChangeDelegate;
	FAttrChangeDelegate SpellSpeedChangeDelegate;
	FAttrChangeDelegate MeleeResistanceChangeDelegate;
	FAttrChangeDelegate MagicResistanceChangeDelegate;
	FAttrChangeDelegate RangedResistanceChangeDelegate;
	FAttrChangeDelegate LifeStealChangeDelegate;
	FAttrChangeDelegate EssenceChangeDelegate;
	FAttrChangeDelegate MaxEssenceChangeDelegate;

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldLevel);
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_Armour(const FGameplayAttributeData& OldArmour);
	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence);
	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldStrength);
	UFUNCTION()
	virtual void OnRep_Block(const FGameplayAttributeData& OldBlock);
	UFUNCTION()
	virtual void OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal);
	UFUNCTION()
	virtual void OnRep_HealthRegenerationRate(const FGameplayAttributeData& OldHealthRegenerationRate);
	UFUNCTION()
	virtual void OnRep_RangedResistance(const FGameplayAttributeData& OldRangedResistance);
	UFUNCTION()
	virtual void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance);
	UFUNCTION()
	virtual void OnRep_MeleeResistance(const FGameplayAttributeData& OldMeleeResistance);
	UFUNCTION()
	virtual void OnRep_SpellSpeed(const FGameplayAttributeData& OldSpellSpeed);
	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);
	UFUNCTION()
	virtual void OnRep_SpellPower(const FGameplayAttributeData& OldSpellPower);
	UFUNCTION()
	virtual void OnRep_CriticalPower(const FGameplayAttributeData& OldCriticalPower);
	UFUNCTION()
	virtual void OnRep_CriticalAccuracy(const FGameplayAttributeData& OldCriticalAccuracy);
	UFUNCTION()
	virtual void OnRep_Speed(const FGameplayAttributeData& OldSpeed);
	UFUNCTION()
	virtual void OnRep_Essence(const FGameplayAttributeData& OldEssence);
	UFUNCTION()
	virtual void OnRep_MaxEssence(const FGameplayAttributeData& OldMaxEssence);

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
