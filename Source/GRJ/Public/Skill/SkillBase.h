// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SkillBase.generated.h"

UENUM(Blueprintable)
enum class ESkillTargetType : uint8
{
	SingleEnemy, // 단일 적
	MultipleEnemies, // 다중 적
	AllEnemies, // 전체 적
	SingleAlly, // 단일 팀
	MultipleAllies, // 다중 팀
	AllAllies, // 전체 팀
	Self // 자기 자신
};


/**
 * 
 */
UCLASS(BlueprintType)
class GRJ_API USkillBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	int32 GetMPCost() const;

	int32 GetAPCost() const;

	float GetSkillValue() const;

	ESkillTargetType GetSkillTargetType() const;
	
protected:

	//사용 자원
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Cost")
	int32 MPCost = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Cost")
	int32 APCost = 1;

	//적용 수치
	UPROPERTY(EditDefaultsOnly, Category = "Skill|Value")
	float SkillValue = 10.0f;

	//대상 종류
	UPROPERTY(EditDefaultsOnly, Category = "Skill|TargetType")
	ESkillTargetType TargetType = ESkillTargetType::SingleEnemy;
	
	
};
