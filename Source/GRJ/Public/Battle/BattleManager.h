// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleManager.generated.h"

class AGRJCharacterBase;
class ATempActor;
/**
 * 
 */
UCLASS()
class GRJ_API UBattleManager : public UObject
{
	GENERATED_BODY()
	
public:
	UBattleManager();

	void BattleStart();

	UPROPERTY(EditAnywhere)
	ATempActor* TempActor;
	
	void NextTurn();

	UFUNCTION(BlueprintCallable)
	AGRJCharacterBase* CurrentTurnCharacter();

	AGRJCharacterBase* EnemyCharacter(int32 TargetNum);

	int32 GetEnemyCount() const;

	int32 GetPlayerCount() const;

	
	
private:
	void StartTurn();
	
	
	void MakeTurnOder();
	
	bool CheckEndBattle();
	void BattleEnd();

	UPROPERTY()
	TArray<AGRJCharacterBase*> PlayerCharacters;

	UPROPERTY()
	TArray<AGRJCharacterBase*> EnemyCharacters;

	UPROPERTY()
	TArray<AGRJCharacterBase*> TurnOrder;

	
	
	UPROPERTY()
	int32 CurrentTurnIndex = 0;
};
