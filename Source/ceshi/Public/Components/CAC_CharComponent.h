// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAC_CharComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class CESHI_API UCAC_CharComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCAC_CharComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Char")
	void InitializeCharComponent(FName charID, UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Char")
	FName GetCharID() const {return myCharID;}

private:
	UFUNCTION()
	void SetCharID(FName newID);

private:
	UPROPERTY()
	FName myCharID;

};
