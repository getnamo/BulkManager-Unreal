// Copyright 2022-current Getnamo. All Rights Reserved.
#pragma once
#include "BulkEntityComponent.h"

struct FBulkManagerData
{
	TMap<FString, FBMEntityData> Entities;
	int64 EntityCounter;

	FBulkManagerData();
};

/**
  Non-uobject manager that handles everything needed for bulk callbacks.
*/
class BULKMANAGER_API FBulkManagerCore
{
public:

	/** Static getters */
	static TSharedPtr<FBulkManagerCore> DefaultManager();
	static TSharedPtr<FBulkManagerCore> GetManager(const FString& ForManagerId);

	//End static

	//Properties

	/** Unique Id */
	FString ManagerId;


	//Functions
	void AddEntity(UBulkEntityComponent* Entity);
	void RemoveEntity(UBulkEntityComponent* Entity);


	FBulkManagerCore();
	~FBulkManagerCore();

protected:
	static TMap<FString, TSharedPtr<FBulkManagerCore>> Managers;

	FString NextId();

	//Tracking entities
	FBulkManagerData Data;
};
