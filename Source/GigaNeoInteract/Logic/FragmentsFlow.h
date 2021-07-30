// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GigaNeoInteract/Data/FFragmentData.h"

#include "FragmentsFlow.generated.h"

UCLASS()
class GIGANEOINTERACT_API AFragmentsFlow : public AActor
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere)
	TArray<FFragmentData> Fragments;

	UFUNCTION(BlueprintCallable)
	FString GetCurrentFragmentText() const;

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetCurrentFragmentConnections();

	UFUNCTION(BlueprintCallable)
	void OnChoice(FString ConnectionLable);

	AFragmentsFlow();

	void AddFragment(FFragmentData Fragment);
	void AddConnection(FConnectionData Connection);
	void StartFlow();
	void SetCurrentFragment(FFragmentData Fragment);

	protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	private:

	FFragmentData CurrentFragment;
	TArray<FString> CurrentFragmentConnections;

	FFragmentData GetFragmentById(FString Id) const;
};
