// Copyright 2022-current Getnamo. All Rights Reserved.

#include "BulkEntityComponent.h"
#include "BulkManagerCore.h"

FBMEntityData::FBMEntityData()
{
	Clear();
}

void FBMEntityData::Clear()
{
	Component = nullptr;
	ObjectData = nullptr;
}

FBulkEntitySettings::FBulkEntitySettings()
{
	ManagerId = TEXT("Default");
}

UBulkEntityComponent::UBulkEntityComponent(const FObjectInitializer &Init) : UActorComponent(Init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
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

	Manager->AddEntity(this);
}

void UBulkEntityComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	TSharedPtr<FBulkManagerCore> Manager = FBulkManagerCore::GetManager(Settings.ManagerId);

	Manager->RemoveEntity(this);

	EntityData.Clear();
}
