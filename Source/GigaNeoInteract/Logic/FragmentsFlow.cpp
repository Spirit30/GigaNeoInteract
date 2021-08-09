#include "FragmentsFlow.h"

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
	for(const auto Connection : CurrentFragment.Connections)
	{
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
