#pragma once
#include "CoreMinimal.h"
#include "FConnectionData.h"
#include "FFragmentData.generated.h"

USTRUCT(Blueprintable)
struct GIGANEOINTERACT_API FFragmentData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FConnectionData> Connections;
};
