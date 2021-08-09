#pragma once
#include "CoreMinimal.h"
#include "FConditionData.generated.h"

USTRUCT(Blueprintable)
struct GIGANEOINTERACT_API FConditionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GlobalVariableKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TrueId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FalseId;
};
