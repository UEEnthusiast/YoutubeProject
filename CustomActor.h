// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomActor.generated.h"

UCLASS()
class UEENTHUSIAST_API ACustomActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool operator==(const ACustomActor& other) const
	{
		return MyIntArray.Num() == other.MyIntArray.Num();
	}

private:
	void Adding();
	void Iterating();
	void Sorting();
	void Querying();
	void Removing();
	void Operators();
	void Heap();

	static bool CompareLength(const FString& strA, const FString& strB)
	{
		return strA.Len() > strB.Len();
	}

public:
	// Simple TArray
	UPROPERTY(EditAnywhere)
	TArray<int32> MyIntArray;

	// The only way to initialize a TArray from here.
	UPROPERTY(EditAnywhere)
	TArray<int32> MyIntArrayInitiated = { 1, 2, 3, 4 };

	// ClampMin and ClampMax are metadata tags in Unreal Engine 4 that allow you to
	// restrict the minimum and maximum values that can be set for a property.
	UPROPERTY(EditAnywhere, meta = (ClampMin = "1", ClampMax = "10"))
	TArray<int32> MyIntArrayClampped;

	// EditFixedSize is a metadata specifier that can be used with a TArray property in a class
	// declaration in Unreal Engine.It indicates that the size of the array cannot be changed in the 
	// editor once it is set, meaning that the editor will not allow the user to add or remove elements from the array.
	UPROPERTY(EditAnywhere, meta = (EditFixedSize = "10"))
	TArray<float> MyFixedIntArray;

	// ArrayClamp meta tag only works for numerical types (such as int32, float, etc.), 
	// and not for other types like FVector or FString.
	UPROPERTY(EditAnywhere, meta = (ArrayClamp = "1,10")) 
	TArray<int32> MyArray;

};
