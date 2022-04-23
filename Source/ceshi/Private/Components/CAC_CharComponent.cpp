// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CAC_CharComponent.h"
#include "GameplayUtil/FuncLib_GameplayUtil.h"
#include "Services/Char/CharService.h"

// Sets default values for this component's properties
UCAC_CharComponent::UCAC_CharComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCAC_CharComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCAC_CharComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCAC_CharComponent::InitializeCharComponent(FName charID, UObject* WorldContextObject)
{
	SetCharID(charID);
	UCharService* charService = UFuncLib_GameplayUtil::GetCharService(WorldContextObject);

	if (charService)
		charService->RegisterCharData(charID);
}

void UCAC_CharComponent::SetCharID(FName newID)
{
	if (myCharID == newID)
		return;

	myCharID = newID;
}

