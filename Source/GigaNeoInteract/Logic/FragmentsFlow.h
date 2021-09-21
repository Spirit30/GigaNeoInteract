// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MediaPlayer.h"
#include "GigaNeoInteract/Data/FConditionData.h"
#include "GigaNeoInteract/Data/FInstructionData.h"
#include "GigaNeoInteract/Data/FFragmentData.h"

#include "FragmentsFlow.generated.h"

UCLASS()
class GIGANEOINTERACT_API AFragmentsFlow : public AActor
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(EditAnywhere)
	UMediaPlayer* Player;

	UPROPERTY(EditAnywhere)
	TArray<FInstructionData> Instructions;
	
	UPROPERTY(EditAnywhere)
	TArray<FConditionData> Conditions;

	UPROPERTY(EditAnywhere)
	TArray<FFragmentData> Fragments;

	UFUNCTION(BlueprintCallable)
	FString GetCurrentFragmentText() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlaying() const;

	UFUNCTION(BlueprintCallable)
	float GetRemainTime() const;

	UFUNCTION(BlueprintCallable)
	TArray<FString> GetCurrentFragmentConnections();

	UFUNCTION(BlueprintCallable)
	void OnChoice(FString ConnectionLable);

	AFragmentsFlow();

	void AddVariable(FString Key, bool Value);
	void AddInstruction(FInstructionData Instruction);
	void AddCondition(FConditionData Condition);
	void AddFragment(FFragmentData Fragment);
	void AddConnection(FConnectionData Connection);
	void StartFlow();

	protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	private:

	TMap<FString, bool> GlobalVariables;

	FFragmentData CurrentFragment;
	TArray<FString> CurrentFragmentConnections;

	bool TryGetInstructionById(FString Id, FInstructionData& OutInstruction);
	bool TryGetConditionById(FString Id, FConditionData& OutCondition);
	bool TryGetFragmentById(FString Id, FFragmentData& OutFragment) const;
	void SetCurrentFragment(FFragmentData Fragment);
	void SetVariable(FString Key, bool Value);
	bool GetVariable(FString Key) const;
};
