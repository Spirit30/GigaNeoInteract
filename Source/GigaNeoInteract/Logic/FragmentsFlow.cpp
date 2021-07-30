#include "FragmentsFlow.h"

AFragmentsFlow::AFragmentsFlow()
{
	PrimaryActorTick.bCanEverTick = true;
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
			const auto NextFragment = GetFragmentById(Connection.ToId);
			SetCurrentFragment(NextFragment);
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

void AFragmentsFlow::BeginPlay()
{
	Super::BeginPlay();

}

void AFragmentsFlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FFragmentData AFragmentsFlow::GetFragmentById(FString Id) const
{
	for(auto Fragment : Fragments)
	{
		if(Fragment.Id == Id)
		{
			return Fragment;
		}
	}

	return  Fragments[0];
}
