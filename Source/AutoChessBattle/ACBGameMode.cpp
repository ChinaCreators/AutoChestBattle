// Fill out your copyright notice in the Description page of Project Settings.


#include "ACBGameMode.h"
#include "LogACB.h"
#include "PlayerPawn.h"

AACBGameMode::AACBGameMode()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
}

void AACBGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogACB, Display, TEXT("ACB GameMode Start"));

	FString dll_path = FPaths::Combine(FPaths::ProjectDir(),
	                                   TEXT("ThirdParty/AutoChessBattleCore/bin/AutoChessBattleCore.dll"));
	if (FPaths::FileExists(dll_path))
	{
		m_DllHandle = FPlatformProcess::GetDllHandle(*dll_path);
		if (m_DllHandle)
		{
			UE_LOG(LogACB, Display, TEXT("DLL loaded successfully: %s"), *dll_path);

			// Get function pointers
			m_GetImplementationFunction = (GetImplementationFunctionType)FPlatformProcess::GetDllExport(
				m_DllHandle, TEXT("GetAutoChessBattleCoreImplementation"));
			m_ReleaseImplementationFunction = (ReleaseImplementationFunctionType)FPlatformProcess::GetDllExport(
				m_DllHandle, TEXT("ReleaseAutoChessBattleCoreImplementation"));

			if (m_GetImplementationFunction && m_ReleaseImplementationFunction)
			{
				// Get implementation
				m_Implementation = m_GetImplementationFunction();
				if (m_Implementation)
				{
					UE_LOG(LogACB, Display, TEXT("Implementation loaded successfully"));
				}
				else
				{
					UE_LOG(LogACB, Error, TEXT("Failed to get implementation"));
				}
			}
			else
			{
				UE_LOG(LogACB, Error, TEXT("Failed to get function exports"));
			}

			// Note: We don't free the DLL handle here as we need it for the lifetime of the game
		}
		else
		{
			UE_LOG(LogACB, Error, TEXT("Failed to load DLL: %s"), *dll_path);
		}
	}
	else
	{
		UE_LOG(LogACB, Error, TEXT("DLL not found: %s"), *dll_path);
	}
}

void AACBGameMode::BeginDestroy()
{
	// Release the implementation if it exists
	if (m_Implementation && m_ReleaseImplementationFunction)
	{
		m_ReleaseImplementationFunction(m_Implementation);
		m_Implementation = nullptr;
		UE_LOG(LogACB, Display, TEXT("Implementation released"));
	}

	// Free the DLL handle if needed
	if (m_DllHandle)
	{
		FPlatformProcess::FreeDllHandle(m_DllHandle);
		m_DllHandle = nullptr;
		UE_LOG(LogACB, Display, TEXT("DLL released"));
	}

	UE_LOG(LogACB, Display, TEXT("ACB GameMode End"));

	Super::BeginDestroy();
}
