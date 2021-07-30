// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FragmentsFlow.h"
#include "Interfaces/IHttpRequest.h"

#include "Loader.generated.h"

UCLASS()
class GIGANEOINTERACT_API ALoader : public AActor
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere)
	FString AccessKey;

	UPROPERTY(EditAnywhere)
	FString LoadingText;

	UPROPERTY(EditAnywhere)
	FString NoPermissionText;

	UPROPERTY(EditAnywhere)
	FString HttpErrorText;

	UPROPERTY(EditAnywhere)
	FString Json;

	UPROPERTY(EditAnywhere)
	AFragmentsFlow* FragmentsFlow;

	ALoader();

	UFUNCTION(BlueprintCallable)
	FString GetMessage();

	protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	private:

	FString Message;

	void SendAccessKeyRequest();
	void OnAccessKeysResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void LoadAllData();
};
