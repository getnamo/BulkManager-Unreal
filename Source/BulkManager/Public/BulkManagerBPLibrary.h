// Copyright 2022-current Getnamo. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BulkManagerBPLibrary.generated.h"

/**
 * Utility functions for e.g. setting up managers
 */
UCLASS()
class BULKMANAGER_API UBulkManagerBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Bulk Manager - Relevancy")
	static void SetBulkViewComponent(USceneComponent* ViewComponent, const FString& ForManager = TEXT("Default"));
};