// The code written in these files is written by Timothy Kardaras & Liam Whitehouse and is intended for this project ONLY (Mythic)

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_BasicAttackDamage.generated.h"

/**
 * 
 */
UCLASS()
class MYTHICISLAND_API UExecCalc_BasicAttackDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecCalc_BasicAttackDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};