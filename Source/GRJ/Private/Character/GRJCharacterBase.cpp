// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRJCharacterBase.h"

#include "Battle/BattleManager.h"
#include "Skill/SkillBase.h"

// Sets default values
AGRJCharacterBase::AGRJCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AGRJCharacterBase::GetSpeed() const
{
	return Speed;
}

float AGRJCharacterBase::GetCurrentHP() const
{
	return CurrentHP;
}

float AGRJCharacterBase::GetMP() const
{
	return MP;
}

float AGRJCharacterBase::GetAttack() const
{
	return Attack;
}

float AGRJCharacterBase::GetDefense() const
{
	return Defense;
}

float AGRJCharacterBase::GetAP() const
{
	return AP;
}

float AGRJCharacterBase::GetEvasion() const
{
	return Evasion;
}

float AGRJCharacterBase::GetShield() const
{
	return Shield;
}

float AGRJCharacterBase::GetCritical() const
{
	return Critical;
}

float AGRJCharacterBase::GetCriticalDamage() const
{
	return CriticalDamage;
}

void AGRJCharacterBase::SetCurrentBattleManager(UBattleManager* InitBattleManager)
{
	CurrentBattleManager = InitBattleManager;
}

// Called when the game starts or when spawned
void AGRJCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGRJCharacterBase::UseAPSkill(int32 SkillNum)
{
	if (!bIsMyTurn || !CurrentBattleManager) return;

	if (!Skills.IsValidIndex(SkillNum)) return;

	if (AP <= 0)
	{
		EndCharacterTurn();
		return;
	}

	USkillBase* SelectSkill = Skills[SkillNum].Get();

	if (!SelectSkill) return;

	const int32 APCost = SelectSkill->GetAPCost();

	if (AP < APCost)
	{
		return;
	}

	if (CurrentTargetNum < 0 || CurrentTargetNum >= CurrentBattleManager->GetEnemyCount())
	{
		return;
	}

	AGRJCharacterBase* Target = CurrentBattleManager->EnemyCharacter(CurrentTargetNum);

	if (!Target) return;

	Target->ApplyDamage(SelectSkill->GetSkillValue());

	AP -= APCost;

	if (AP <= 0)
	{
		EndCharacterTurn();
	}
	
}

void AGRJCharacterBase::StartCharacterTurn()
{
	if (CurrentHP <= 0.0f)
	{
		EndCharacterTurn();
		return;
	}
	
	bIsMyTurn = true;
	
	
}

void AGRJCharacterBase::ApplyDamage(float Damage)
{
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0.0f, MaxHP);
}


void AGRJCharacterBase::SetMP(int32 NewMP)
{
	if (MP - NewMP <= 0.0f)
	{
		MP = 0.0f;
	}
	else
	{
		MP = MP - NewMP;
	}
}

void AGRJCharacterBase::SetAP(int32 NewAP)
{
	if (AP - NewAP <= 0.0f)
	{
		AP = 0.0f;
	}
	else
	{
		AP = AP - NewAP;
	}
}

void AGRJCharacterBase::SelectSkill(int32 SkillNum)
{
	if (!bIsMyTurn) return;
	
	if (!Skills.IsValidIndex(SkillNum))
	{
		return;
	}

	CurrentSelectSkillNum = SkillNum;
}

void AGRJCharacterBase::SetTargetNum(int32 TargetNum)
{
	if (!bIsMyTurn || !CurrentBattleManager) return;

	if (TargetNum < 0 || TargetNum >= CurrentBattleManager->GetEnemyCount())
	{
		return;
	}

	CurrentTargetNum = TargetNum;
}

void AGRJCharacterBase::ConfirmSkill()
{
	if (!bIsMyTurn) return;

	UseAPSkill(CurrentSelectSkillNum);
}

void AGRJCharacterBase::EndCharacterTurn()
{
	bIsMyTurn = false;

	if (CurrentBattleManager)
	{
		CurrentBattleManager->NextTurn();
	}
}

// Called every frame
void AGRJCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGRJCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

