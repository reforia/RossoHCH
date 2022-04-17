// Fill out your copyright notice in the Description page of Project Settings.


#include "Services/Inventory/InventoryService.h"
#include "Components/CAC_InventoryComponent.h"
#include "Engine/Texture2D.h"
#include "Services/ServiceManager.h"

void UInventoryService::ServiceConstruction(UServiceManager* owner)
{	
	InventoriesList = TMap<UCAC_InventoryComponent*, TArray<FStruct_ItemWithCount>*>();
	
	UServiceBase::ServiceConstruction(owner);
}

void UInventoryService::ServiceShutdown()
{
	for (auto inventoryComp : GetListOfAllInventoryComps())
	{
		delete InventoriesList[inventoryComp];
		InventoriesList[inventoryComp] = nullptr;
	}
}

bool UInventoryService::AddObjectIntoInventory(const UCAC_InventoryComponent* inventoryCompRef, const FName itemID, const int32 count)
{
	if(!inventoryCompRef || !DoesServiceContainComponent(inventoryCompRef))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, "[CRITICAL ERROR] TRY ADD OBJECT TO INVENTORY BUT INVENTORY COMP NOT VALID (nullptr or Not Initialized)");
		return false;
	}

	auto item = GetInventoryItemWithCountByComponent(inventoryCompRef, itemID);
	if (!item)
	{
		// We need to add it into the array list
		if (count <= 0)
			return true;

		auto itemsList = GetInventoryItemListByComponent(inventoryCompRef);
		if (!itemsList)
			return false;
		
		FStruct_Item* itemQueryData = ItemDatabase->FindRow<FStruct_Item>(itemID, "");
		if (!itemQueryData)
			return false;

		const int unstackableCount = FMath::Clamp(count, 0, 1);
		const int stackableCount = FMath::Max(count, 0);
		const int finalCount = itemQueryData->Stackable ? stackableCount : unstackableCount;
		FStruct_ItemWithCount tmpItemWithCount(itemQueryData, finalCount);

		itemsList->Add(tmpItemWithCount);
		return true;
	}
	else
	{
		// We need to add the count up
		int targetCount = item->Count + count;
		int unstackableCount = FMath::Clamp(targetCount, 0, 1);
		int stackableCount = FMath::Max(targetCount, 0);
		int finalCount = item->ItemRef.Stackable ? stackableCount : unstackableCount;
		if (finalCount > 0)
		{
			// We are adding stuff to existing item
			item->Count = finalCount;
			return true;
		}
		else 
		{
			// We are clearing the array
			auto currentItemsList = GetInventoryItemListByComponent(inventoryCompRef);
			int32 index = 0;
			for (auto &items : *currentItemsList)
			{
				if (items.ItemRef.ID == item->ItemRef.ID)
					break;
				
				index++;
			}
			
			if (!currentItemsList->IsValidIndex(index))
				return false;

			currentItemsList->RemoveAt(index);
			return true;
		}
	}
	return false;
}

void UInventoryService::RegisterInventoryComponent(UCAC_InventoryComponent* inventoryCompRef)
{
	if (DoesServiceContainComponent(inventoryCompRef))
		return; // Already Registered before

	InventoriesList.Add(inventoryCompRef, new TArray<FStruct_ItemWithCount>());
}

FString UInventoryService::GetDebugLogInfo()
{
	FString result;
	result = "-----INVENTORY Debug Log-----\n";
	for (UCAC_InventoryComponent* compRef : GetListOfAllInventoryComps())
	{
		result = result + "Comp Owner: " + compRef->GetOwner()->GetName() + "\n";
		for (FStruct_ItemWithCount& itemsList : *GetInventoryItemListByComponent(compRef))
		{
			result += "-----------------------\n";
			result = result + "Name: " + itemsList.ItemRef.Name.ToString();
			result = result + "Count: ";
			result.AppendInt(itemsList.Count);
			result += "\n";
		}
	}

	return result;
}

TArray<UCAC_InventoryComponent*> UInventoryService::GetListOfAllInventoryComps()
{
	TArray<UCAC_InventoryComponent*> result;

	int32 a = InventoriesList.Num();
	if (a == 0)
		return result;

	InventoriesList.GetKeys(result);
	return result;
}

bool UInventoryService::DoesServiceContainComponent(const UCAC_InventoryComponent* inventoryCompRef)
{
	return GetListOfAllInventoryComps().Contains(inventoryCompRef);
}

TArray<FStruct_ItemWithCount>* UInventoryService::GetInventoryItemListByComponent(const UCAC_InventoryComponent* inventoryCompRef)
{
	if (!DoesServiceContainComponent(inventoryCompRef))
		return nullptr;

	return InventoriesList[inventoryCompRef];
}

FStruct_ItemWithCount* UInventoryService::GetInventoryItemWithCountByComponent(const UCAC_InventoryComponent* inventoryCompRef, FName ItemID)
{
	if (!inventoryCompRef)
		return nullptr;

	if (!ItemDatabase)
		return nullptr;

	FStruct_Item* queryItemResult = ItemDatabase->FindRow<FStruct_Item>(ItemID, "");

	if (!queryItemResult)
		return nullptr;

	auto inventoryItemsList = GetInventoryItemListByComponent(inventoryCompRef);
	if (!inventoryItemsList)
		return nullptr;

	for (auto& items : *inventoryItemsList)
	{
		if (items.ItemRef.ID == queryItemResult->ID)
			return &items;
	}

	return nullptr;
}

FStruct_Item* UInventoryService::GetInventoryItemByComponent(const UCAC_InventoryComponent* inventoryCompRef, FName ItemID)
{
	auto items = GetInventoryItemWithCountByComponent(inventoryCompRef, ItemID);

	if (!items)
		return nullptr;

	return &items->ItemRef;
}


