// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GRJCharacterBase.h"

// Sets default values
AGRJCharacterBase::AGRJCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGRJCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
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

