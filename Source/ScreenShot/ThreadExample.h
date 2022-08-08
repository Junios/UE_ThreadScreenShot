#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"


// Note that we do not have to mark our class as UCLASS() if we don't want to
class FThreadExample : public FRunnable
{
public:
	// Custom constructor for setting up our thread with its target
	FThreadExample(int TotalFrame, int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData);

	// FRunnable functions
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;
	// FRunnable

	TArray<int32> ProcessedNumbers;
	TArray<FColor> RawBitmap;

	int32 SizeX;
	int32 SizeY;

	bool IsComplete() const;

protected:
	int32 TotalFrame = -1;
	int32 FoundCount = -1;

	bool bStopThread = false;
};