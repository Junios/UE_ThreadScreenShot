#include "ThreadExample.h"
#include "Engine/GameViewportClient.h"
#include "ImageUtils.h"
#include "Engine/Engine.h"
#include "Misc/FileHelper.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "ThreadExample.h"
#include "ThreadManager.h"

FThreadExample::FThreadExample(int _TotalFrame, int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData)
{
	TotalFrame = _TotalFrame;
	SizeX = InSizeX;
	SizeY = InSizeY;
	RawBitmap = InImageData;
}


uint32 FThreadExample::Run()
{
	UE_LOG(LogClass, Warning, TEXT("Thread Run"));
	bStopThread = false;
	TArray<uint8> Bitmap;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::GetModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::BMP);

	if (!ImageWrapper.IsValid())
	{
		return 0;
	}

	if (!ImageWrapper->SetRaw(&RawBitmap[0], RawBitmap.Num() * sizeof(FColor), SizeX, SizeY, ERGBFormat::BGRA, 8))
	{
		return 0;
	}

	
	//const TArray<uint8>& CompressedImage = ImageWrapper->GetCompressed(100);
	TArray<uint8> CompressedImage;
	ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, CompressedImage);


	FString savelocation = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString filename = savelocation + FString(TEXT("/Saved/Screenshots/")) + FString::Printf(TEXT("%d"), TotalFrame) + FString(TEXT(".BMP"));

	//FImageUtils::CompressImageArray(SizeX, SizeY, RawBitmap, Bitmap);
	//FFileHelper::SaveArrayToFile(Bitmap, *filename);

	FFileHelper::SaveArrayToFile(CompressedImage, *filename);

	FFileHelper::CreateBitmap(filename.GetCharArray().GetData(), SizeX, SizeY, RawBitmap.GetData());


	// Return success
	return 0;
}


void FThreadExample::Exit()
{
	// Here's where we can do any cleanup we want to 
}


void FThreadExample::Stop()
{
	// Force our thread to stop early
	bStopThread = true;
}


bool FThreadExample::IsComplete() const
{
	return FoundCount >= TotalFrame;
}