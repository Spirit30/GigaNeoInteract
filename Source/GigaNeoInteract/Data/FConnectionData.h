#pragma once
#include "CoreMinimal.h"
#include "FConnectionData.generated.h"

USTRUCT(Blueprintable)
struct GIGANEOINTERACT_API FConnectionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FromId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ToId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Lable;
};
