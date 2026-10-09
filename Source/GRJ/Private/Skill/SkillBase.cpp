// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillBase.h"

int32 USkillBase::GetMPCost() const
{
	return MPCost;
}

int32 USkillBase::GetAPCost() const
{
	return APCost;
}

float USkillBase::GetSkillValue() const
{
	return SkillValue;
}

ESkillTargetType USkillBase::GetSkillTargetType() const
{
	return TargetType;
}
