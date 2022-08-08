// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ThreadManager.generated.h"

/**
 * 
 */
UCLASS()
class SCREENSHOT_API UThreadManager : public UObject
{
	GENERATED_BODY()

public:
	UThreadManager();

	// Call this to create the thread and start it going
	void StartProcess(int TotalFrame, int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData);

protected:

	class FThreadExample* MyThreadExample = nullptr;
	FRunnableThread* CurrentThread = nullptr;
	
	
};
