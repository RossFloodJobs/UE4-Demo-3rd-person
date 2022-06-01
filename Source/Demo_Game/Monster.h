// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "Monster.generated.h"

UCLASS()
class DEMO_GAME_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster();
	// Sets default values for this character's properties
	AMonster(const FObjectInitializer& ObjectInitializer);

	//monster speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float speed;
	
	//monster health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float hitPoints;

	//exp player gains when enemy defeated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		int32 experience;

	//blueprint of type of item dropped after defeating monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		UClass* BPLoot;

	//attack damage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float baseAttackDamage;

	//rest time between atacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float attackTimeout;

	//time since last strike, editable in BP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		float timeSinceLastStrike;

	//range of sight
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		USphereComponent* SightSphere;

	//attack range
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = MonsterProperties)
		USphereComponent* AttackRangeSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
