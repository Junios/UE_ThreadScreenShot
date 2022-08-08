// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScreenshotJpeg, const TArray<uint8>&, Jpeg);


UCLASS()
class SCREENSHOT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Test")
	void TakeScreenshot();

	//static FOnScreenshotCaptured & OnScreenshotCaptured();

	float TotalTime = 0;
	int TotalFrame = 0;


public:
	UFUNCTION(BlueprintCallable, Category = Screenshot)
	virtual void RequestScreenshot();

	UPROPERTY(BlueprintAssignable, Category = Screenshot)
	FOnScreenshotJpeg OnScreenshotJpeg;

protected:
	virtual void AcceptScreenshot(int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData);

	bool bIsScreenshotRequested;

	class UThreadManager* Manager;
};
