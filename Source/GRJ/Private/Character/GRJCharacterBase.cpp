// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRJCharacterBase.h"

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

// Called when the game starts or when spawned
void AGRJCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("등록된 스킬 개수: %d"), Skills.Num());

	for (int32 i = 0; i < Skills.Num(); i++)
	{
		if (Skills[i])
		{
			UE_LOG(LogTemp, Log, TEXT("스킬 [%d]: %s"),
				i, *Skills[i]->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("스킬 [%d]가 nullptr입니다."), i);
		}
	}
	
}

void AGRJCharacterBase::CharacterDead()
{
	OnCharacterEliminated.Broadcast(this);
}

void AGRJCharacterBase::ApplyDamage(float Damage)
{
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0.0f, MaxHP);

	if (CurrentHP <= 0.0f)
	{
		CharacterDead();
	}	
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
	AP = NewAP;
}

void AGRJCharacterBase::UseAP(int32 UseNum)
{
	AP = AP - UseNum;

	if (AP < 0)
	{
		AP = 0;
	}
}

TArray<TObjectPtr<USkillBase>> AGRJCharacterBase::GetSkills() const
{
	return Skills;
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

