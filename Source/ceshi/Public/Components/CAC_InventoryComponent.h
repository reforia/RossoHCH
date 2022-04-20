// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAC_InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class CESHI_API UCAC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCAC_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Inventory")
	void InitializeInventoryComponent(FName inventoryID, UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	FName GetInventoryID() const { return myInventoryID; }

private:
	UFUNCTION()
	void SetInventoryID(FName newID);

private:
	UPROPERTY()
	FName myInventoryID;
};
