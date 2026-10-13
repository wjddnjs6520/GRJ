// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BattleManager.generated.h"

class USkillManager;
class AGRJCharacterBase;
class ATempActor;
/**
 * 
 */
UCLASS(BlueprintType)
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

	UFUNCTION(BlueprintCallable)
	USkillManager* GetSkillManager();
	
	AGRJCharacterBase* EnemyCharacter(int32 TargetNum);

	int32 GetEnemyCount() const;

	int32 GetPlayerCount() const;	

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<USkillManager> CurrentSkillManager;
	
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

	UPROPERTY()
	int32 CurrentRoundNum = 1;
};
