// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/BattleManager.h"

#include "TempActor.h"
#include "Character/GRJCharacterBase.h"

UBattleManager::UBattleManager()
{
	
}

void UBattleManager::BattleStart()
{
	
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
	if (CurrentTurnIndex < TurnOrder.Num())
	{
		if (CheckEndBattle())
		{
			BattleEnd();
		}
	}

	// 캐릭터에게 현재 턴인거 알려주기
	
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

void UBattleManager::MakeTurnOder()
{
	TurnOrder.Empty();

	TurnOrder.Append(PlayerCharacters);
	TurnOrder.Append(EnemyCharacters);

	TurnOrder.Sort([](const AGRJCharacterBase& A, AGRJCharacterBase& B)
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

