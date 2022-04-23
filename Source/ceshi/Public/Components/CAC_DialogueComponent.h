// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Services/Dialogue/DialogueService.h"
#include "CAC_DialogueComponent.generated.h"

struct FStruct_DialogueActorData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class CESHI_API UCAC_DialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCAC_DialogueComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = "Dialogue")
	void InitializeDialogueComponent(FName DialogueActorID, UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Dialogue")
	FName GetDialogueActorID() const { return myDialogueActorID; }

private:
	UFUNCTION()
	void SetDialogueActorID(FName newID);

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FStruct_DialogueActorData myDialogueActorData;

private:
	UPROPERTY()
	FName myDialogueActorID;
};
