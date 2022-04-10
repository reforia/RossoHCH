// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_RainyBlue.h"

void AGM_RainyBlue::SwitchGameplayState(EGameplayState newState)
{
	if (newState == GetCurrentGameplayState())
		return;

	OnGameplayStateDeconstructed(GetCurrentGameplayState());
	SetGameplayState(newState);
	OnGameplayStateChanged(GetCurrentGameplayState());
}

bool AGM_RainyBlue::OnGameplayStateChanged_Implementation(EGameplayState newState)
{
	return true;
}

bool AGM_RainyBlue::OnGameplayStateDeconstructed_Implementation(EGameplayState oldState)
{
	return true;
}

//
//FString AGM_RainyBlue::GetVictoryEnumAsString(EGameplayState EnumValue)
//{
//	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EVictoryEnum"), true);
//	if (!EnumPtr) return FString("Invalid");
//	return EnumPtr->GetNameByValue((int64)EnumValue); // for EnumValue == VE_Dance returns "VE_Dance"
//}
