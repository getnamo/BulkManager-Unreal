// Copyright 2022-current Getnamo. All Rights Reserved.

#include "BulkManagerBPLibrary.h"
#include "BulkManagerCore.h"

void UBulkManagerBPLibrary::SetBulkViewComponent(USceneComponent* ViewComponent, const FString& ForManager /*= TEXT("Default")*/)
{
	TSharedPtr<FBulkManagerCore> Manager = FBulkManagerCore::GetManager(ForManager);

	Manager->SetViewComponent(ViewComponent);
}
