// Fill out your copyright notice in the Description page of Project Settings.


#include "GASAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "MythicIsland/MythicGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "MythicIsland/Character/BaseCharacter.h"
#include "MythicIsland/Helpers/PlayerProgressionHelper.h"

UGASAttributeSet::UGASAttributeSet()
{
	const FMythicGameplayTags& GameplayTags = FMythicGameplayTags::Get();
	
	TagsToAttributes.Add(GameplayTags.Attributes_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Armour, GetArmourAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Block, GetBlockAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Health, GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Life_Steal, GetLifeStealAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Attack_Speed, GetAttackSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Critical_Accuracy, GetCriticalAccuracyAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Critical_Power, GetCriticalPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Spell_Power, GetSpellPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Magic_Resistance, GetMagicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Melee_Resistance, GetMeleeResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Ranged_Resistance, GetRangedResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Speed, GetSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_HealthRegenRate, GetHealthRegenerationRateAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Damage, GetDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Essence, GetEssenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MaxEssence, GetMaxEssenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Level, GetLevelAttribute);
}

UGASAttributeSet::~UGASAttributeSet()
{

}

void UGASAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		HealthChangeDelegate.Broadcast(GetHealth(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetArmourAttribute())
	{
		SetArmour(FMath::Clamp(GetArmour(), 0.0f, 100.0f));
		ArmourChangeDelegate.Broadcast(GetArmour(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetIntelligenceAttribute())
	{
		SetIntelligence(FMath::Clamp(GetIntelligence(), 0.0f, 100.0f));
		IntelligenceChangeDelegate.Broadcast(GetIntelligence(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetStrength(FMath::Clamp(GetStrength(), 0.0f, 100.0f));
		StrengthChangeDelegate.Broadcast(GetStrength(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetBlockAttribute())
	{
		SetBlock(FMath::Clamp(GetBlock(), 0.0f, 100.0f));
		BlockChangeDelegate.Broadcast(GetBlock(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetEssenceAttribute())
	{
		SetBlock(FMath::Clamp(GetEssence(), 0.0f, 100.0f));
		EssenceChangeDelegate.Broadcast(GetEssence(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetMaxEssenceAttribute())
	{
		SetBlock(FMath::Clamp(GetMaxEssence(), 0.0f, 100.0f));
		MaxEssenceChangeDelegate.Broadcast(GetMaxEssence(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetCriticalAccuracyAttribute())
	{
		SetBlock(FMath::Clamp(GetCriticalAccuracy(), 0.0f, 100.0f));
		CriticalAccuracyChangeDelegate.Broadcast(GetCriticalAccuracy(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetCriticalPowerAttribute())
	{
		SetBlock(FMath::Clamp(GetCriticalPower(), 0.0f, 100.0f));
		CriticalPowerChangeDelegate.Broadcast(GetCriticalPower(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetSpellPowerAttribute())
	{
		SetBlock(FMath::Clamp(GetSpellPower(), 0.0f, 100.0f));
		SpellPowerChangeDelegate.Broadcast(GetSpellPower(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetSpellSpeedAttribute())
	{
		SetBlock(FMath::Clamp(GetSpellSpeed(), 0.0f, 100.0f));
		SpellSpeedChangeDelegate.Broadcast(GetSpellSpeed(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetLifeStealAttribute())
	{
		SetBlock(FMath::Clamp(GetLifeSteal(), 0.0f, 100.0f));
		LifeStealChangeDelegate.Broadcast(GetLifeSteal(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetMeleeResistanceAttribute())
	{
		SetBlock(FMath::Clamp(GetMeleeResistance(), 0.0f, 100.0f));
		MeleeResistanceChangeDelegate.Broadcast(GetMeleeResistance(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetRangedResistanceAttribute())
	{
		SetBlock(FMath::Clamp(GetRangedResistance(), 0.0f, 100.0f));
		RangedResistanceChangeDelegate.Broadcast(GetRangedResistance(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetMagicResistanceAttribute())
	{
		SetBlock(FMath::Clamp(GetMagicResistance(), 0.0f, 100.0f));
		MagicResistanceChangeDelegate.Broadcast(GetMagicResistance(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetHealthRegenerationRateAttribute())
	{
		SetBlock(FMath::Clamp(GetHealthRegenerationRate(), 0.0f, 100.0f));
		HealthRegnerationRateChangeDelegate.Broadcast(GetHealthRegenerationRate(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		SetSpeed(FMath::Clamp(GetSpeed(), 0.0f, 100.0f));
		SpeedChangeDelegate.Broadcast(GetSpeed(), Data.EffectSpec.GetStackCount(), Data.EvaluatedData.Magnitude);
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalDamage = GetDamage();
		SetDamage(0.f);
		if (LocalDamage > 0.0f)
		{
			if (GetHealth() <= 0.0f)
			{
				return;
			}

			const float NewHealth = GetHealth() - LocalDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			ABaseCharacter* Target = Cast<ABaseCharacter>(Props.TargetActor);
			const bool bFatal = NewHealth <= 0.0f;
			if (Target == nullptr)
			{
				return;
			}

			if (bFatal == true)
			{
				UPlayerProgressionHelper::HandleCharacterDeath(Props.SourceActor, Cast<ABaseCharacter>(Props.TargetActor));
				Target->HandleDeath();
			}
			else
			{
				Target->HandleDamage(Props.SourceActor, LocalDamage);
			}
		}
	}
}

void UGASAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Level, OldLevel);
}

void UGASAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Armour, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Block, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, CriticalAccuracy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, CriticalPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, SpellPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, SpellSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, LifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MeleeResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, RangedResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, HealthRegenerationRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Essence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MaxEssence, COND_None, REPNOTIFY_Always);
}

void UGASAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Health, OldHealth);
}

void UGASAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MaxHealth, OldMaxHealth);
}

void UGASAttributeSet::OnRep_Armour(const FGameplayAttributeData& OldArmour)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Armour, OldArmour);
}

void UGASAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Intelligence, OldIntelligence);
}

void UGASAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Strength, OldStrength);
}

void UGASAttributeSet::OnRep_Block(const FGameplayAttributeData& OldBlock)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Block, OldBlock);
}

void UGASAttributeSet::OnRep_LifeSteal(const FGameplayAttributeData& OldLifeSteal)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, LifeSteal, OldLifeSteal);
}

void UGASAttributeSet::OnRep_HealthRegenerationRate(const FGameplayAttributeData& OldHealthRegenerationRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, HealthRegenerationRate, OldHealthRegenerationRate);
}

void UGASAttributeSet::OnRep_RangedResistance(const FGameplayAttributeData& OldRangedResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, RangedResistance, OldRangedResistance);
}

void UGASAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MagicResistance, OldMagicResistance);
}

void UGASAttributeSet::OnRep_MeleeResistance(const FGameplayAttributeData& OldMeleeResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MeleeResistance, OldMeleeResistance);
}

void UGASAttributeSet::OnRep_SpellSpeed(const FGameplayAttributeData& OldSpellSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, SpellSpeed, OldSpellSpeed);
}

void UGASAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UGASAttributeSet::OnRep_SpellPower(const FGameplayAttributeData& OldSpellPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, SpellPower, OldSpellPower);
}

void UGASAttributeSet::OnRep_CriticalPower(const FGameplayAttributeData& OldCriticalPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, CriticalPower, OldCriticalPower);
}

void UGASAttributeSet::OnRep_CriticalAccuracy(const FGameplayAttributeData& OldCriticalAccuracy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, CriticalAccuracy, OldCriticalAccuracy);
}

void UGASAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Speed, OldSpeed);
}

void UGASAttributeSet::OnRep_Essence(const FGameplayAttributeData& OldEssence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Essence, OldEssence);
}

void UGASAttributeSet::OnRep_MaxEssence(const FGameplayAttributeData& OldMaxEssence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MaxEssence, OldMaxEssence);
}

void UGASAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetInstigatorAbilitySystemComponent();

	Props.SourceActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
	
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	}
}
