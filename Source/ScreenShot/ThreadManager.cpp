// Fill out your copyright notice in the Description page of Project Settings.

#include "ThreadManager.h"

#include "HAL/RunnableThread.h"
#include "Engine/Engine.h"

#include "ThreadExample.h"



UThreadManager::UThreadManager()
{
}


void UThreadManager::StartProcess(int TotalFrame, int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData)
{
	//if (!CurrentThread && FPlatformProcess::SupportsMultithreading())
	if (FPlatformProcess::SupportsMultithreading())
	{
		// Run the thread until we've found 999 random numbers
		MyThreadExample = new FThreadExample(TotalFrame, InSizeX, InSizeY, InImageData);
		CurrentThread = FRunnableThread::Create(MyThreadExample, TEXT("Any old thread name"));
	}
}