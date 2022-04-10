// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryService.generated.h"


class UCAC_InventoryComponent;
class UImage;

// UCAC_InventoryComponent : TArray(ItemsList) ItemsList => Dict(Struct Item: count)
//USTRUCT(BlueprintType)
//struct FStruct_Item
//{
//	GENERATED_BODY()
//
//public:
//	FStruct_Item() = default;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FString ID = "Default";
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Name = FText::FromString(TEXT(""));
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	FText Description = FText::FromString(TEXT(""));
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	bool Stackable = true;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	UImage* UIImage = nullptr;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//	UStaticMesh* StaticMesh = nullptr;
//};
//
//USTRUCT(BlueprintType)
//struct FStruct_ItemWithCount
//{
//	GENERATED_BODY()
//
//public:
//	FStruct_Item& ItemRef;
//	int32 Count;
//};
//
//USTRUCT(BlueprintType)
//struct FStruct_InventoryObject
//{
//	GENERATED_BODY()
//
//public:
//	UCAC_InventoryComponent* InventoryCompRef;
//	TArray<FStruct_ItemWithCount&> ItemsList;
//};

/**
 * 
 */
UCLASS()
class CESHI_API UInventoryService : public UObject
{
	GENERATED_BODY()
//	
//public:
//	UFUNCTION(BlueprintCallable, Category = "ItemOperation")
//	void AddObjectIntoInventory(const UCAC_InventoryComponent* inventoryCompRef, const FName itemID, const int32 count);
//
//	UFUNCTION(BlueprintCallable, Category = "Construction")
//	void RegisterInventoryComponent(const UCAC_InventoryComponent* inventoryCompRef);
//
//	UFUNCTION(BlueprintPure, Category = "InventoryHelper")
//	bool DoesServiceContainComponent(const UCAC_InventoryComponent* inventoryCompRef);
//
//	UFUNCTION(BlueprintPure, Category = "InventoryHelper")
//	bool GetInventoryItemListByComponent(const UCAC_InventoryComponent* inventoryCompRef, TArray<FStruct_ItemCount&> OutInventoryItemList);
//
//	UFUNCTION(BlueprintPure, Category = "InventoryHelper")
//	bool GetInventoryItemByComponent(const UCAC_InventoryComponent* inventoryCompRef, FName ItemID, struct FStruct_Item& OutItem);
//
//public:
//	TArray<FStruct_InventoryObject&> InventoriesList;

};
