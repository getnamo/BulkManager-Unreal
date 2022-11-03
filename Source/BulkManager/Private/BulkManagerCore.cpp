// Copyright 2022-current Getnamo. All Rights Reserved.
#include "BulkManagerCore.h"

TMap<FString, TSharedPtr<FBulkManagerCore>> FBulkManagerCore::Managers;

//Static
TSharedPtr<FBulkManagerCore> FBulkManagerCore::DefaultManager()
{
	const FString DefaultManagerId = TEXT("Default");

	return GetManager(DefaultManagerId);
}

TSharedPtr<FBulkManagerCore> FBulkManagerCore::GetManager(const FString& ForManagerId)
{
	if (Managers.Contains(ForManagerId))
	{
		return Managers[ForManagerId];
	}
	else
	{
		TSharedPtr<FBulkManagerCore> Manager = MakeShareable(new FBulkManagerCore());
		Managers.Add(ForManagerId, Manager);
		return Manager;
	}
}

void FBulkManagerCore::Shutdown()
{
	//Shutdown any threads

	//Clear managers
	Managers.Empty();
}

void FBulkManagerCore::AddEntity(UBulkEntityComponent* Entity)
{
	//Get a unique id, ensure linkage to passed in component
	Entity->EntityData.EntityId = NextId();
	Entity->EntityData.BulkComponent = Entity;

	Data.Entities.Add(Entity->EntityData.EntityId, Entity->EntityData);

	StartTickLoopIfNeeded();
}

void FBulkManagerCore::RemoveEntity(UBulkEntityComponent* Entity)
{
	Data.Entities.Remove(Entity->EntityData.EntityId);

	if (Data.Entities.Num() == 0)
	{
		FTSTicker::GetCoreTicker().RemoveTicker(Data.EventLoop.DelegateHandle);
		Data.EventLoop.DelegateHandle = FTSTicker::FDelegateHandle();
	}
}

void FBulkManagerCore::SetViewComponent(USceneComponent* InViewComponent)
{
	Data.ViewComponent = InViewComponent;
}

void FBulkManagerCore::StartTickLoopIfNeeded()
{
	if (!Data.bShouldTickOnGameThread)
	{
		return;
	}

	if (Data.EventLoop.DelegateHandle.IsValid())
	{
		return;
	}

	//Startup loop, one per manager
	Data.EventLoop.DelegateHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([&](float DeltaTime)
	{
		//Early out - todo: remove ticker not just mute if changed during gameplay?
		if (!Data.bShouldTickOnGameThread)
		{
			return true;
		}

		//Tick logic
		RelevancyTick();

		return true;
	}));
}

FString FBulkManagerCore::NextId()
{
	Data.EntityCounter++;
	return FString::Printf(TEXT("%d"), Data.EntityCounter);
}

//Main logic function
void FBulkManagerCore::RelevancyTick()
{
	if (!Data.ViewComponent)
	{
		//TODO: warn
		return;
	}

	const FTransform& ViewTransform = Data.ViewComponent->GetComponentTransform();

	//TODO: order by tick time efficiently to allow
	//ticking by staggering and ticking less often on
	//distant entities

	for (auto& EntityPair : Data.Entities)
	{
		FBMEntityData& Entity = EntityPair.Value;

		const FTransform& EntityTransform = Entity.OriginSceneComponent->GetComponentTransform();

		//Test Distance
		double Distance = (ViewTransform.GetTranslation() - EntityTransform.GetTranslation()).Size();

		if (Entity.BulkComponent)
		{
			//for now we only support real and bulk, TODO: lod support
			if (Distance > Entity.BulkComponent->Settings.BulkRadius)
			{
				if (Distance > Entity.BulkComponent->Settings.VirtualRadius)
				{
					//Should be in virtual state
					if (Entity.BulkState != EBMBulkState::VIRTUAL)
					{
						Entity.BulkState = EBMBulkState::VIRTUAL;
						Entity.BulkComponent->OnStateChanged.Broadcast(Entity.BulkState);
					}
				}
				else
				{
					//Should be in bulk state
					if (Entity.BulkState != EBMBulkState::BULK)
					{
						Entity.BulkState = EBMBulkState::BULK;
						Entity.BulkComponent->OnStateChanged.Broadcast(Entity.BulkState);
					}
				}
			}
			else
			{
				if (Entity.BulkState != EBMBulkState::REAL)
				{
					Entity.BulkState = EBMBulkState::REAL;
					Entity.BulkComponent->OnStateChanged.Broadcast(Entity.BulkState);
				}
			}
		
		}
		else
		{
			//TODO
			//Not an actor with bulk component. needs to be handled by group manager
		}

		//TODO: test view frustrum
	}
}

FBulkManagerCore::FBulkManagerCore()
{

}

FBulkManagerCore::~FBulkManagerCore()
{

}

FBulkManagerData::FBulkManagerData()
{
	EntityCounter = 0;
	bSupportViewFrustumRelevancy = false;
	ViewComponent = nullptr;
	DefaultBulkRadius = 1000.f; //10m
	bShouldTickOnGameThread = true;
}
