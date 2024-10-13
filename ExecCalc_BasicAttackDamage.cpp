// The code written in these files is written by Timothy Kardaras & Liam Whitehouse and is intended for this project ONLY (Mythic)


#include "MythicIsland/GAS/ExecCalc/ExecCalc_BasicAttackDamage.h"

#include "AbilitySystemComponent.h"
#include "MythicIsland/MythicGameplayTags.h"
#include "MythicIsland/Character/BaseCharacter.h"
#include "MythicIsland/GAS/GASAttributeSet.h"

struct MythicDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armour);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	
	MythicDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, Armour, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, Health, Target, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UGASAttributeSet, Strength, Source, false);
		
	}
};

static const MythicDamageStatics& DamageStatics()
{
	static MythicDamageStatics DStatics;

	return DStatics;
}

UExecCalc_BasicAttackDamage::UExecCalc_BasicAttackDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmourDef);
	RelevantAttributesToCapture.Add(DamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
}

void UExecCalc_BasicAttackDamage::Execute_Implementation( const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (SourceASC == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Source Ability System Component is Null in ExecCalc_BasicAttackDamage"));
		return;
	}
	AActor* SourceActor = SourceASC->GetAvatarActor();
	
	if (TargetASC == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Target Ability System Component is Null in ExecCalc_BasicAttackDamage"));
		return;
	}
	AActor* TargetActor = TargetASC->GetAvatarActor();
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = Spec.GetSetByCallerMagnitude(FMythicGameplayTags::Get().Attributes_Damage);
	
	float Armour = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmourDef, EvaluationParameters, Armour);
	Armour = FMath::Max<float>(0.f, Armour);

	float Strength = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().StrengthDef, EvaluationParameters, Strength);
	Armour = FMath::Max<float>(0.f, Armour);
	
	Damage = (Damage * (Strength / 10)) / (Armour / 100);

	if (Damage <= 0.0f)
	{
		Damage = 0.0f;
	}
	
	const FGameplayModifierEvaluatedData EvaluatedData(UGASAttributeSet::GetDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);

	ABaseCharacter* Target = Cast<ABaseCharacter>(TargetActor);
	
	Target->HandleDamage(SourceActor, Damage);
}
