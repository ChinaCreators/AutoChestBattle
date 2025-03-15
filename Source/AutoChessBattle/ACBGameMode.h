// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoChessBattleCore.hpp"
#include "GameFramework/GameModeBase.h"
#include "ACBGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AUTOCHESSBATTLE_API AACBGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AACBGameMode();

	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

private:
	using GetImplementationFunctionType = AutoChessBattleCore::AutoChessBattleCoreInterface*(*)();
	using ReleaseImplementationFunctionType = void(*)(AutoChessBattleCore::AutoChessBattleCoreInterface*);

	void* m_DllHandle = nullptr;
	GetImplementationFunctionType m_GetImplementationFunction = nullptr;
	ReleaseImplementationFunctionType m_ReleaseImplementationFunction = nullptr;
	AutoChessBattleCore::AutoChessBattleCoreInterface* m_Implementation = nullptr;
};
