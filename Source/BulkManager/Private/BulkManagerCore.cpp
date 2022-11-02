// Copyright 2022-current Getnamo. All Rights Reserved.
#include "BulkManagerCore.h"

TMap<FString, TSharedPtr<FBulkManagerCore>> FBulkManagerCore::Managers;

FString FBulkManagerCore::NextId()
{
	Data.EntityCounter++;
	return FString::Printf(TEXT("%d"), Data.EntityCounter);
}

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
		Managers[ForManagerId] = Manager;
		return Manager;
	}
}

void FBulkManagerCore::AddEntity(UBulkEntityComponent* Entity)
{
	//Get a unique id, ensure linkage to passed in component
	Entity->EntityData.EntityId = NextId();
	Entity->EntityData.Component = Entity;

	Data.Entities.Add(Entity->EntityData.EntityId, Entity->EntityData);
}

void FBulkManagerCore::RemoveEntity(UBulkEntityComponent* Entity)
{
	Data.Entities.Remove(Entity->EntityData.EntityId);
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
}
