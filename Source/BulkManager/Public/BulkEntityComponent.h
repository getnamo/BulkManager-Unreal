// Copyright 2022-current Getnamo. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "BulkEntityComponent.generated.h"

/** Non-minimal entity data */
USTRUCT(BlueprintType)
struct BULKMANAGER_API FBMEntityData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	UBulkEntityComponent* Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	UObject* ObjectData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	FString SerializedData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	FString EntityId;

	FBMEntityData();
	void Clear();	//Used to ensure property nulling
};

USTRUCT(BlueprintType)
struct BULKMANAGER_API FBulkEntitySettings
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Settings")
	FString ManagerId;

	FBulkEntitySettings();
};

UCLASS(ClassGroup = "Actor Management", meta = (BlueprintSpawnableComponent))
class BULKMANAGER_API UBulkEntityComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity")
	FBulkEntitySettings Settings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity")
	FBMEntityData EntityData;


	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
};