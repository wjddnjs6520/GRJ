// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillManager.generated.h"

class UBattleManager;
class USkillBase;
class AGRJCharacterBase;
/**
 * 
 */
UCLASS()
class GRJ_API USkillManager : public UObject
{
	GENERATED_BODY()
public:
	USkillManager();

	void StartCharacterTurn(AGRJCharacterBase* character);

	void SettingBattleManager(UBattleManager* InitBattleManager);

	UFUNCTION(BlueprintCallable)
	void SelectSkill(int32 SelectSkillNum);

	UFUNCTION(BlueprintCallable)
	void SelectTargetNum(int32 SelectTargetNum);

	UFUNCTION(BlueprintCallable)
	void ConfirmSkill();
	
private:
	
	UFUNCTION()
	void UseAPSkill(int32 SkillNum);

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	AGRJCharacterBase* CurrentTurnCharacter = nullptr;
	
	//현재 턴의 캐릭터가 가진 스킬들
	UPROPERTY(EditDefaultsOnly, Category = "Skills")
	TArray<TObjectPtr<USkillBase>> CurrentSkills;

	UPROPERTY(EditDefaultsOnly, Category = "Skills")
	int32 SkillNum = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Skills")
	int32 TargetNum = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Manager")
	UBattleManager* BattleManager;
};
