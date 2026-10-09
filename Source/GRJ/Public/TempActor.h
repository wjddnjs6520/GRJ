// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TempActor.generated.h"

class UBattleManager;
class AGRJCharacterBase;

UCLASS()
class GRJ_API ATempActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATempActor();

	UPROPERTY(EditAnywhere)
	TArray<AGRJCharacterBase*> PlayerTeam;

	UPROPERTY(EditAnywhere)
	TArray<AGRJCharacterBase*> EnemyTeam;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UBattleManager> BattleManager;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
