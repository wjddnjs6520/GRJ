// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/SkillManager.h"

#include "Battle/BattleManager.h"
#include "Character/GRJCharacterBase.h"
#include "Skill/SkillBase.h"

USkillManager::USkillManager()
{
	
}

void USkillManager::StartCharacterTurn(AGRJCharacterBase* Character)
{
	if (!Character) return;
	CurrentTurnCharacter = Character;
	
	//행동 포인트 초기화
	CurrentTurnCharacter->SetAP(3);
		
	//기본 스킬, 기본 타겟 설정
	CurrentSkills = CurrentTurnCharacter->GetSkills();

	SelectSkill(SkillNum);
	SelectTargetNum(TargetNum);
	
	
	
}

void USkillManager::SettingBattleManager(UBattleManager* InitBattleManager)
{
	BattleManager = InitBattleManager;
}

void USkillManager::SelectSkill(int32 SelectSkillNum)
{

	if (!CurrentSkills.IsValidIndex(SelectSkillNum))
	{
		return;
	}

	SkillNum = SelectSkillNum;
}

void USkillManager::SelectTargetNum(int32 SelectTargetNum)
{

	if (!BattleManager) return;
	
	if (TargetNum < 0 || TargetNum >= BattleManager->GetEnemyCount())
	{
		return;
	}

	TargetNum = SelectTargetNum;
}

void USkillManager::ConfirmSkill()
{
	UseAPSkill(SkillNum);
}

void USkillManager::UseAPSkill(int32 SkillNum)
{
	if (!BattleManager) return;

	if (!CurrentSkills.IsValidIndex(SkillNum)) return;

	if (CurrentTurnCharacter->GetAP() <= 0)
	{
		return;
	}

	USkillBase* SelectSkill = CurrentSkills[SkillNum].Get();

	if (!SelectSkill) return;

	const int32 APCost = SelectSkill->GetAPCost();

	if (CurrentTurnCharacter->GetAP() < APCost)
	{
		return;
	}

	if (TargetNum < 0 || TargetNum >= BattleManager->GetEnemyCount())
	{
		return;
	}

	AGRJCharacterBase* Target = BattleManager->EnemyCharacter(TargetNum);

	if (!Target) return;

	Target->ApplyDamage(SelectSkill->GetSkillValue());

	CurrentTurnCharacter->SetAP(APCost);

	if (CurrentTurnCharacter->GetAP() <= 0)
	{
		//턴 종료
		BattleManager->NextTurn();
	}
}
