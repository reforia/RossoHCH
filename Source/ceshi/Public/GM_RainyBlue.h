// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_RainyBlue.generated.h"

UENUM(BlueprintType)
enum class EGameplayState : uint8 {
	EV_InGameplayIdle UMETA(DisplayName="InGameplayIdle"),
	EV_InCinematic UMETA(DisplayName = "InCinematic"),
	EV_InDialogue UMETA(DisplayName = "InDialogue"),
	EV_InMiniGame UMETA(DisplayName = "InMiniGame"),
	EV_UNDEFINED UMETA(DisplayName = "UNDEFINED")
};

/**
 * 
 */
UCLASS()
class CESHI_API AGM_RainyBlue : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE EGameplayState GetCurrentGameplayState() { return myGameplayState; }

	UFUNCTION(BlueprintCallable, Category="Rainy Blue Game Mode")
	void SwitchGameplayState(EGameplayState newState);

	UFUNCTION(BlueprintNativeEvent, Category = "Rainy Blue Game Mode")
	bool OnGameplayStateChanged(EGameplayState newState);
	
	UFUNCTION(BlueprintNativeEvent, Category = "Rainy Blue Game Mode")
	bool OnGameplayStateDeconstructed(EGameplayState oldState);

private:
	FORCEINLINE void SetGameplayState(EGameplayState newState) { myGameplayState = newState; }
	//UFUNCTION(BlueprintCallable)
	//FString GetVictoryEnumAsString(EGameplayState EnumValue);
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGameplayState myGameplayState = EGameplayState::EV_UNDEFINED;

};