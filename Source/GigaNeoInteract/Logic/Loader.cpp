// Fill out your copyright notice in the Description page of Project Settings.


#include "Loader.h"

#include "HttpModule.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "GigaNeoInteract/Data/FFragmentData.h"
#include "Interfaces/IHttpResponse.h"

ALoader::ALoader()
{
	PrimaryActorTick.bCanEverTick = true;
}

FString ALoader::GetMessage()
{
	return Message;
}

void ALoader::BeginPlay()
{
	Super::BeginPlay();

	SendAccessKeyRequest();
}

void ALoader::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALoader::SendAccessKeyRequest()
{
	Message = LoadingText;
	
	const auto URL = "https://raw.githubusercontent.com/Spirit30/AccessKeys/main/AccessKeys.json";
	
	const auto Http = &FHttpModule::Get();
	const auto Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &ALoader::OnAccessKeysResponse);
	Request->SetURL(URL);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void ALoader::OnAccessKeysResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if(EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		const auto JsonResponse = Response->GetContentAsString();
	
		TSharedPtr<FJsonValue> AccessKeysData;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(JsonResponse);
 
		if (FJsonSerializer::Deserialize(Reader, AccessKeysData))
		{
			const auto AccessKeysArray = AccessKeysData->AsArray();

			for(const auto AccessKeyItem : AccessKeysArray)
			{
				if(AccessKeyItem->AsString() == AccessKey)
				{
					Message.Empty();
					LoadAllData();
					return;
				}
			}

			Message = NoPermissionText;
		}
	}
	else
	{
		Message = HttpErrorText;
	}
}

void ALoader::LoadAllData()
{
	TSharedPtr<FJsonObject> ProjectData;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);

	if (FJsonSerializer::Deserialize(Reader, ProjectData))
	{
		const auto Packages = ProjectData->GetArrayField("Packages");

		if(Packages.Num() > 0)
		{
			const auto Package = Packages[0]->AsObject();
			const auto Models = Package->GetArrayField("Models");

			for(const auto ModelItem : Models)
			{
				const auto Model = ModelItem->AsObject();
				const auto Type = Model->GetStringField("Type");
				
				if(Type == "FlowFragment")
				{
					const auto Properties = Model->GetObjectField("Properties");

					FFragmentData Fragment;

					Fragment.Id = Properties->GetStringField("Id");
					Fragment.DisplayName = Properties->GetStringField("DisplayName");
					Fragment.Text = Properties->GetStringField("Text");

					const auto OutputPins = Properties->GetArrayField("OutputPins");
					const auto OutputPin = OutputPins[0]->AsObject();

					//If NOT end Fragment Nodes
					if(OutputPin->HasField("Connections"))
					{
						const auto Connections = OutputPin->GetArrayField("Connections");

						for(const auto ConnectionItem : Connections)
						{
							const auto Connection = ConnectionItem->AsObject();
						
							const auto Target = Connection->GetStringField("Target");
							const auto Lable = Connection->GetStringField("Label");

							FString LeftLable;
							FString RightLable;
							if(Lable.Split(" / ", &LeftLable, &RightLable))
							{
								FConnectionData ConnectionDataFromLeft;
								ConnectionDataFromLeft.FromId = Fragment.Id;
								ConnectionDataFromLeft.ToId = Target;
								ConnectionDataFromLeft.Lable = LeftLable;

								Fragment.Connections.Add(ConnectionDataFromLeft);

								FConnectionData ConnectionDataFromRight;
								ConnectionDataFromRight.FromId = Fragment.Id;
								ConnectionDataFromRight.ToId = Target;
								ConnectionDataFromRight.Lable = RightLable;

								Fragment.Connections.Add(ConnectionDataFromRight);
							}
							else
							{
								FConnectionData ConnectionData;
								ConnectionData.FromId = Fragment.Id;
								ConnectionData.ToId = Target;
								ConnectionData.Lable = Lable;

								Fragment.Connections.Add(ConnectionData);
							}
						}
					}

					FragmentsFlow->AddFragment(Fragment);
				}
			}
		}
	}
	
	FragmentsFlow->StartFlow();
}

