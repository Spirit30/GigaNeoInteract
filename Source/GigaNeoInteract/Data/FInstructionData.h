#pragma once
#include "CoreMinimal.h"
#include "FInstructionData.generated.h"

USTRUCT(Blueprintable)
struct GIGANEOINTERACT_API FInstructionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString GlobalVariableKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool GlobalVariableValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ToId;
};
