#pragma once

#include "Engine/DataTable.h"
#include "DataStructures.generated.h"


USTRUCT(BlueprintType)
struct FWeaponData : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;
	
	FWeaponData() {
		Name = "";
		Damage = 0;
		SocketName = "";
	}
};

UENUM()
enum EMovementType {
	Walking = 0,
	Sprinting = 1,
	Dashing = 2
};
