#include "FragmentsFlow.h"
#include "FileMediaSource.h"

AFragmentsFlow::AFragmentsFlow()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFragmentsFlow::AddVariable(FString Key, bool Value)
{
	GlobalVariables.Add(Key, Value);
}

void AFragmentsFlow::AddInstruction(FInstructionData Instruction)
{
	Instructions.Add(Instruction);
}

void AFragmentsFlow::AddCondition(FConditionData Condition)
{
	Conditions.Add(Condition);
}

FString AFragmentsFlow::GetCurrentFragmentText() const
{
	return CurrentFragment.Text;
}

bool AFragmentsFlow::IsPlaying() const
{
	return Player->IsPlaying();
}

float AFragmentsFlow::GetRemainTime() const
{
	return Player->GetDuration().GetTotalSeconds() - Player->GetTime().GetTotalSeconds();
}

TArray<FString> AFragmentsFlow::GetCurrentFragmentConnections()
{
	CurrentFragmentConnections.Empty();

	for(const auto Connection : CurrentFragment.Connections)
	{
		CurrentFragmentConnections.Add(Connection.Lable);
	}
	
	return  CurrentFragmentConnections;
}

void AFragmentsFlow::OnChoice(FString ConnectionLable)
{
	for(int32 i = 0; i < CurrentFragment.Connections.Num(); ++i)
	{
		const auto Connection = CurrentFragment.Connections[i];
		
		if(Connection.Lable == ConnectionLable)
		{
			auto ToId = Connection.ToId;

			FInstructionData Instruction;
			if(TryGetInstructionById(ToId, Instruction))
			{
				SetVariable(Instruction.GlobalVariableKey, Instruction.GlobalVariableValue);
				ToId = Instruction.ToId;
			}

			FConditionData Condition;
			if(TryGetConditionById(ToId, Condition))
			{
				const auto Value = GetVariable(Condition.GlobalVariableKey);
				ToId = Value ? Condition.TrueId : Condition.FalseId;
			}
			
			FFragmentData NextFragment;
			if(TryGetFragmentById(ToId, NextFragment))
			{
				SetCurrentFragment(NextFragment);
			}
		}
	}
}

void AFragmentsFlow::AddFragment(FFragmentData Fragment)
{
	Fragments.Add(Fragment);
}

void AFragmentsFlow::AddConnection(FConnectionData Connection)
{
	for(auto Fragment : Fragments)
	{
		if(Fragment.Id == Connection.FromId)
		{
			Fragment.Connections.Add(Connection);
		}
	}
}

void AFragmentsFlow::StartFlow()
{
	SetCurrentFragment(Fragments[0]);
}

void AFragmentsFlow::SetCurrentFragment(FFragmentData Fragment)
{
	CurrentFragment = Fragment;

	const auto VideoPath = FPaths::GameDevelopersDir() + Fragment.DisplayName + ".wmv";

	UFileMediaSource* MediaSource = NewObject<UFileMediaSource>();
	MediaSource->SetFilePath(VideoPath);

	UE_LOG(LogTemp, Log, TEXT("%s"), *VideoPath);
	
	if(Player->CanPlaySource(MediaSource))
	{
		Player->Play();
		Player->OpenSource(MediaSource);
	}
	else
	{
		const auto VideoNotFoundError = "Video Not Found at: " + VideoPath;
		UE_LOG(LogTemp, Error, TEXT("%s"), *VideoNotFoundError);

		if(Player->IsPlaying())
		{
			Player->Pause();
		}
	}
}

void AFragmentsFlow::SetVariable(FString Key, bool Value)
{
	GlobalVariables[Key] = Value;
}

bool AFragmentsFlow::GetVariable(FString Key) const
{
	return GlobalVariables[Key];
}

void AFragmentsFlow::BeginPlay()
{
	Super::BeginPlay();

}

void AFragmentsFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AFragmentsFlow::TryGetInstructionById(FString Id, FInstructionData& OutInstruction)
{
	for(auto Instruction : Instructions)
	{
		if(Instruction.Id == Id)
		{
			OutInstruction = Instruction;
			return true;
		}
	}

	return false;
}

bool AFragmentsFlow::TryGetConditionById(FString Id, FConditionData& OutCondition)
{
	for(auto Condition : Conditions)
	{
		if(Condition.Id == Id)
		{
			OutCondition = Condition;
			return true;
		}
	}

	return false;
}

bool AFragmentsFlow::TryGetFragmentById(FString Id, FFragmentData& OutFragment) const
{
	for(auto Fragment : Fragments)
	{
		if(Fragment.Id == Id)
		{
			OutFragment = Fragment;
			return true;
		}
	}

	return false;
}
