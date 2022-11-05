#pragma once

#include "BulkInstanceManagerBase.generated.h"

USTRUCT(BlueprintType)
struct BULKMANAGER_API FBulkInstanceData
{
	GENERATED_USTRUCT_BODY();

	/** Index in ISM array */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Instance Data")
	int32 Index;

	/** Hashed Id on creation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Instance Data")
	FString UniqueId;

	/** World transform*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Instance Data")
	FTransform Transform;

	/** Data Option 1. Equivalent to CustomData float for Material use*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Instance Data")
	float DataFloat;

	/** Data Option 2. Usually moved pointer passed from real actor type*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Instance Data")
	UObject* DataObject;

	/** Data Option 3. Serialized data */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bulk Instance Data")
	FString DataSerializedString;
};

/**
* Base management type
*/

UCLASS(BlueprintType, Blueprintable)
class BULKMANAGER_API UBulkInstanceManagerBase : public UObject
{
	GENERATED_UCLASS_BODY()
public:

	//Convert object to instance
	UFUNCTION(BlueprintPure, Category = "Bulk Instance Manager")
	void OnBulkFromReal(AActor* Entity, const FBulkInstanceData& Data);

	//Spawn object from ISM
	UFUNCTION(BlueprintPure, Category = "Bulk Instance Manager")
	AActor* OnRealFromBulk(UClass* RealType, UObject* Data);

	//Conceptual
	//UFUNCTION(BlueprintPure, Category = "Bulk Instance Manager")
	//void OnVirtual(const FTransform& LastTransform, UObject* Data);

	UPROPERTY(BlueprintReadOnly, Category = "Bulk Instance Manager")
	TArray<FBulkInstanceData> DataArray;
};