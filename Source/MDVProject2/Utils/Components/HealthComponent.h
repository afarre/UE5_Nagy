// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthDelegate, const float&, CurrentHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MDVPROJECT2_API UHealthComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitValues(float InitMaxHealth, float InitCurrentHealth);

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float CurrentHealth;

	UFUNCTION(BlueprintCallable)
	void RemoveHP(float DamageTaken);
	
	FHealthDelegate HealthDelegateBinder;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
