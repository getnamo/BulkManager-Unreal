#include "BulkInstanceManagerBase.h"

UBulkInstanceManagerBase::UBulkInstanceManagerBase(const FObjectInitializer& Init) : UObject(Init)
{

}

void UBulkInstanceManagerBase::OnBulkFromReal(AActor* Entity, const FBulkInstanceData& Data)
{

}

AActor* UBulkInstanceManagerBase::OnRealFromBulk(UClass* RealType, UObject* Data)
{
	return nullptr;
}
