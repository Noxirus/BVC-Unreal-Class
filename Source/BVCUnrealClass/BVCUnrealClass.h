// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define LOG_MESSAGE(string) UE_LOG(LogTemp, Warning, string)
#define SCREEN_MESSAGE(string) GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, string)