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
	UE_LOG(LogTemp, Warning, TEXT("SelectTargetNum 호출 - 입력값: %d"), SelectTargetNum);

	if (!BattleManager)
	{
		UE_LOG(LogTemp, Error, TEXT("SelectTargetNum 실패 - BattleManager가 nullptr"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("현재 TargetNum: %d, 적 수: %d"),
		TargetNum, BattleManager->GetEnemyCount());

	if (SelectTargetNum < 0)
	{
		TargetNum = 0;
		UE_LOG(LogTemp, Warning, TEXT("TargetNum 범위 초과 - 최소값 0으로 설정"));
		return;
	}

	if (SelectTargetNum >= BattleManager->GetEnemyCount())
	{
		TargetNum = BattleManager->GetEnemyCount() - 1;
		UE_LOG(LogTemp, Warning, TEXT("TargetNum 범위 초과 - 최대값 %d로 설정"), TargetNum);
		return;
	}

	TargetNum = SelectTargetNum;

	UE_LOG(LogTemp, Warning, TEXT("타겟 변경 완료 - TargetNum: %d"), TargetNum);
}

void USkillManager::ConfirmSkill()
{
	UseAPSkill();
}

int32 USkillManager::GetSkillNum()
{
	return SkillNum;
}

int32 USkillManager::GetTargetNum()
{
	return TargetNum;
}

void USkillManager::UseAPSkill()
{
	UE_LOG(LogTemp, Warning, TEXT("UseAPSkill 호출"));

	if (!BattleManager)
	{
		UE_LOG(LogTemp, Error, TEXT("스킬 사용 실패 - BattleManager가 nullptr"));
		return;
	}

	if (!CurrentSkills.IsValidIndex(SkillNum))
	{
		UE_LOG(LogTemp, Warning, TEXT("스킬 사용 실패 - 잘못된 SkillNum: %d, 스킬 개수: %d"),
			SkillNum, CurrentSkills.Num());
		return;
	}

	if (!CurrentTurnCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("스킬 사용 실패 - CurrentTurnCharacter가 nullptr"));
		return;
	}

	if (CurrentTurnCharacter->GetAP() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("스킬 사용 실패 - AP가 0 이하"));
		return;
	}

	USkillBase* SelectSkill = CurrentSkills[SkillNum].Get();

	if (!SelectSkill)
	{
		UE_LOG(LogTemp, Error, TEXT("스킬 사용 실패 - 선택한 스킬이 nullptr"));
		return;
	}

	const int32 APCost = SelectSkill->GetAPCost();
	const int32 SkillValue = SelectSkill->GetSkillValue();

	UE_LOG(LogTemp, Warning, TEXT("선택 스킬 정보 - AP 소모량: %d, 스킬 효과값: %d"),
		APCost, SkillValue);

	if (CurrentTurnCharacter->GetAP() < APCost)
	{
		return;
	}

	if (TargetNum < 0 || TargetNum >= BattleManager->GetEnemyCount())
	{
		UE_LOG(LogTemp, Warning, TEXT("스킬 사용 실패 - 잘못된 TargetNum: %d, 적 수: %d"),
			TargetNum, BattleManager->GetEnemyCount());
		return;
	}

	AGRJCharacterBase* Target = BattleManager->EnemyCharacter(TargetNum);

	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("스킬 사용 실패 - 타겟이 nullptr (TargetNum: %d)"),
			TargetNum);
		return;
	}
	

	Target->ApplyDamage(SkillValue);

	CurrentTurnCharacter->UseAP(APCost);

	if (CurrentTurnCharacter->GetAP() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AP 소진 - 다음 턴으로 이동"));
		BattleManager->NextTurn();
	}
}