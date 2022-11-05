// Copyright 2022-current Getnamo. All Rights Reserved.

#include "BulkEntityComponent.h"
#include "BulkInstanceManagerBase.h"
#include "BulkManagerCore.h"

FBMEntityData::FBMEntityData()
{
	Reset();
}

void FBMEntityData::Reset()
{
	BulkComponent = nullptr;
	ObjectData = nullptr;
	
	BulkState = EBMBulkState::UNKNOWN;
}

FBMEntitySettings::FBMEntitySettings()
{
	ManagerId = TEXT("Default");
	BulkRadius = 1000.f;	//default 10m
	VirtualRadius = 100000.f;	//default 1000m
	LODSRadius.Empty();			//default no lod support
	bUseInstanceManagerOnBulk = true;
	BulkInstanceManager = UBulkInstanceManagerBase::StaticClass();
}

UBulkEntityComponent::UBulkEntityComponent(const FObjectInitializer &Init) : UActorComponent(Init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = false;
}


//Overrides
void UBulkEntityComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UBulkEntityComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
}

void UBulkEntityComponent::BeginPlay()
{
	Super::BeginPlay();

	TSharedPtr<FBulkManagerCore> Manager = FBulkManagerCore::GetManager(Settings.ManagerId);

	//Have we set our bulk origin component? if not pick root of parent
	if (!EntityData.OriginSceneComponent)
	{
		EntityData.OriginSceneComponent = GetOwner()->GetRootComponent();
	}

	Manager->AddEntity(this);
}

void UBulkEntityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	TSharedPtr<FBulkManagerCore> Manager = FBulkManagerCore::GetManager(Settings.ManagerId);

	Manager->RemoveEntity(this);
	EntityData.Reset();

	Super::EndPlay(EndPlayReason);
}
