// Copyright 2022-current Getnamo. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "BulkEntityComponent.h"

//Event loop data if using game thread ticking
struct FBMTickEventLoopData
{
	FTSTicker::FDelegateHandle DelegateHandle;

	FBMTickEventLoopData()
	{
		DelegateHandle = FTSTicker::FDelegateHandle();
	}
};

struct FBulkManagerData
{
	//Tracking entities
	TMap<FString, FBMEntityData> Entities;
	int64 EntityCounter;

	//Tracking relevancy origin
	USceneComponent* ViewComponent;

	//Settings
	bool bSupportViewFrustumRelevancy;
	bool bShouldTickOnGameThread;

	//defaults
	FBMEntitySettings DefaultEntitySettings;

	FBMTickEventLoopData EventLoop;

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
	static void Shutdown();

	//End static

	//Properties

	//Functions
	
	//Entities
	void AddEntity(UBulkEntityComponent* Entity);
	void RemoveEntity(UBulkEntityComponent* Entity);

	void ClearEntities();

	//Origin relevancy
	void SetViewComponent(USceneComponent* InViewComponent);

	void StartTickLoopIfNeeded();

	FBulkManagerCore();
	~FBulkManagerCore();

protected:
	static TMap<FString, TSharedPtr<FBulkManagerCore>> Managers;

	FString NextId();
	void RelevancyTick();

	//All params are wrapped into a struct
	FBulkManagerData Data;
};
