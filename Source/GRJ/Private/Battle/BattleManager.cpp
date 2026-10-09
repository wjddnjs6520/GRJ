// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleManager.h"

#include "TempActor.h"
#include "Character/GRJCharacterBase.h"

UBattleManager::UBattleManager()
{
	
}

void UBattleManager::BattleStart()
{
	if (!TempActor) return;
	
	PlayerCharacters = TempActor->PlayerTeam;
	EnemyCharacters = TempActor->EnemyTeam;
	
	if (CheckEndBattle())
	{
		BattleEnd();
		return;
	}
	
	MakeTurnOder();

	StartTurn();
}

void UBattleManager::StartTurn()
{
	if (CheckEndBattle())
	{
		BattleEnd();
		return;
	}

	if (CurrentTurnIndex >= TurnOrder.Num())
	{
		MakeTurnOder();
	}

	AGRJCharacterBase* Character = CurrentTurnCharacter();

	if (!Character)
	{
		return;
	}

	Character->SetCurrentBattleManager(this);
	Character->StartCharacterTurn();
	
}


void UBattleManager::NextTurn()
{
	CurrentTurnIndex++;
	StartTurn();
}

AGRJCharacterBase* UBattleManager::CurrentTurnCharacter()
{
	if (CurrentTurnIndex >= TurnOrder.Num())
	{
		return nullptr;	
	}

	return TurnOrder[CurrentTurnIndex];
}

AGRJCharacterBase* UBattleManager::EnemyCharacter(int32 TargetNum)
{
	if (TargetNum < 0 || TargetNum >= EnemyCharacters.Num())
	{
		return nullptr;
	}
	return EnemyCharacters[TargetNum];
}

int32 UBattleManager::GetEnemyCount() const
{
	return EnemyCharacters.Num();
}

int32 UBattleManager::GetPlayerCount() const
{
	return PlayerCharacters.Num();
}

void UBattleManager::MakeTurnOder()
{
	TurnOrder.Empty();

	TurnOrder.Append(PlayerCharacters);
	TurnOrder.Append(EnemyCharacters);

	TurnOrder.Sort([](const AGRJCharacterBase& A, const AGRJCharacterBase& B)
	{
		return A.GetSpeed() > B.GetSpeed();
	});

	CurrentTurnIndex = 0;
}

bool UBattleManager::CheckEndBattle()
{
	if (PlayerCharacters.Num() == 0 || EnemyCharacters.Num() == 0)
	{
		return true;
	}

	return false;
}

void UBattleManager::BattleEnd()
{
	PlayerCharacters.Empty();
	EnemyCharacters.Empty();
	TurnOrder.Empty();
	CurrentTurnIndex = 0;
}

