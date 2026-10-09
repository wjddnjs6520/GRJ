// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GRJCharacterBase.generated.h"

class USkillBase;
class UBattleManager;

UCLASS()
class GRJ_API AGRJCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AGRJCharacterBase();

    float GetSpeed() const;

    float GetCurrentHP() const;
    float GetMP() const;
    float GetAttack() const;
    float GetDefense() const;
    float GetAP() const;
    float GetEvasion() const;
    float GetShield() const;
    float GetCritical() const;
    float GetCriticalDamage() const;

    void SetCurrentBattleManager(UBattleManager* InitBattleManager);
    
    UFUNCTION()
    void StartCharacterTurn();

    void ApplyDamage(float Damage);
    void SetMP(int32 NewMP);
    void SetAP(int32 NewAP);

    void SelectSkill(int32 SkillNum);

    void SetTargetNum(int32 TargetNum);

    void ConfirmSkill();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Stats
    float MaxHP = 100.0f;
    float CurrentHP = 100.0f;
    int32 MP = 50;

    float Attack = 10.0f;
    float Defense = 10.0f;

    int32 AP = 3;

    float Speed = 10.0f;

    float Evasion = 0.0f;
    float Shield = 0.0f;

    float Critical = 0.0f;
    float CriticalDamage = 150.0f;

    UPROPERTY()
    UBattleManager* CurrentBattleManager = nullptr;

    
    
    UFUNCTION()
    void UseAPSkill(int32 SkillNum);
    
    UFUNCTION()
    void EndCharacterTurn();

    bool bIsMyTurn = false;

    int32 CurrentSelectSkillNum = 0;
    int32 CurrentTargetNum = 0;
    
    UPROPERTY()
    TArray<TObjectPtr<USkillBase>> Skills;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
