// Copyright 2022-current Getnamo. All Rights Reserved.
#pragma once

#include "Components/ActorComponent.h"
#include "BulkEntityComponent.generated.h"

UENUM(BlueprintType)
enum class EBMBulkState : uint8
{
	REAL,	//equivalent to lod0
	LOD1,	//NB: lods may be skipped
	LOD2,
	LOD3,
	LOD4,
	LOD5,
	LOD6,
	LOD7,
	LOD8,	//maximum of 8 lods supported at this time
	BULK,	//equivalent to ISM
	VIRTUAL,//non-visual
	UNKNOWN
};

/** Non-minimal entity data */
USTRUCT(BlueprintType)
struct BULKMANAGER_API FBMEntityData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	UBulkEntityComponent* BulkComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	UObject* ObjectData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	FString SerializedData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	FString EntityId;

	//Change if you want a different start state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	EBMBulkState BulkState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	USceneComponent* OriginSceneComponent;

	FBMEntityData();
	void Reset();	//Used to ensure property nulling
};

USTRUCT(BlueprintType)
struct BULKMANAGER_API FBMEntitySettings
{
	GENERATED_USTRUCT_BODY()

	//For bulk component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Settings")
	FString ManagerId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Settings")
	bool bUseInstanceManagerOnBulk;

	//for instance static mesh types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	UClass* BulkInstanceManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	AActor* RealType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	UStaticMesh* ISMeshType;

	//When this entity should be managed by a group handler (e.g. instance static meshes)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	float BulkRadius;

	//When this entity should no longer be visible
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Data")
	float VirtualRadius;

	/** 
	If component exists and we have LODS defined this these radius' will be
	used to determine individual callbacks for different LOD states.
	NB: not yet implemented.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity Settings")
	TArray<float> LODSRadius;

	FBMEntitySettings();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBulkStateSignature, EBMBulkState, State);

UCLASS(ClassGroup = "Actor Management", meta = (BlueprintSpawnableComponent))
class BULKMANAGER_API UBulkEntityComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY(BlueprintAssignable, Category = "Bulk Manager - Events")
	FBulkStateSignature OnStateChanged;

	//Data relevant only for setup and relevancy testing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity")
	FBMEntitySettings Settings;

	//Data relevant to the entity in all states
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Manager - Entity")
	FBMEntityData EntityData;

	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
};