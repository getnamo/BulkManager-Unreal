// Copyright 2022-current Getnamo. All Rights Reserved.

#include "BulkManager.h"
#include "BulkManagerCore.h"

#define LOCTEXT_NAMESPACE "FBulkManagerModule"

void FBulkManagerModule::StartupModule()
{

}

void FBulkManagerModule::ShutdownModule()
{
	FBulkManagerCore::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBulkManagerModule, BulkManager)