// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Engine/GameViewportClient.h"
#include "ImageUtils.h"
#include "Engine/Engine.h"
#include "Misc/FileHelper.h"

#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "ThreadExample.h"
#include "ThreadManager.h"
//#include "Http.h"

//#include "Async/AsyncWork.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//UGameViewportClient::OnScreenshotCaptured().AddUObject(this, &AMyCharacter::OnScreenShotCaptured);


}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Manager = NewObject<UThreadManager>(this);

	

	//GIsHighResScreenshot = true;
	GScreenshotResolutionX = 1920;
	GScreenshotResolutionY = 1080;
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TotalTime += DeltaTime;

	if (TotalTime >= (1.0f / 22.0f))
	{
		//TakeScreenshot();
		RequestScreenshot();
		TotalTime = 0;
		TotalFrame++;
	}

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::TakeScreenshot()
{
	//GIsHighResScreenshot = true;

	//UGameViewportClient* gameViewport = GEngine->GameViewport;
	//FViewport* InViewport = gameViewport->Viewport;
	//TArray<FColor> Bitmap;

	//bool bScreenshotSuccessful = GetViewportScreenShot(InViewport, Bitmap);
	//if (bScreenshotSuccessful)
	//{
	//	FIntVector Size(InViewport->GetSizeXY().X, InViewport->GetSizeXY().Y, 0);
	//	TArray<uint8> CompressedBitmap;
	//	FString ScreenShotName = TEXT("out.png");
	//	FImageUtils::CompressImageArray(Size.X, Size.Y, Bitmap, CompressedBitmap);
	//	FFileHelper::SaveArrayToFile(CompressedBitmap, *ScreenShotName);
	//}

//	FScreenshotRequest::RequestScreenshot(true);

	//FScreenshotRequest SR = FScreenshotRequest();
	//FString savelocation = FPaths::ConvertRelativePathToFull(FPaths::GameDir());
	//FString filename = savelocation + FString(TEXT("/Saved/Screenshots/")) + TEXT("Sample") + FString(TEXT(".png"));
	//SR.RequestScreenshot(filename, true, false);

	//UE_LOG(LogClass, Warning, TEXT("%s"), *filename);

	if (GEngine == nullptr || GEngine->GameViewport == nullptr || bIsScreenshotRequested)
	{
		return;
	}

	//bIsScreenshotRequested = true;

	FScreenshotRequest::RequestScreenshot(false);
}



void AMyCharacter::RequestScreenshot()
{
	if (GEngine == nullptr || GEngine->GameViewport == nullptr || bIsScreenshotRequested)
	{
		return;
	}

	GEngine->GameViewport->OnScreenshotCaptured().AddUObject(this, &AMyCharacter::AcceptScreenshot);

	FScreenshotRequest::RequestScreenshot(false);
	//bIsScreenshotRequested = true;

	UE_LOG(LogClass, Warning, TEXT("Request Screenshot."));
}

void AMyCharacter::AcceptScreenshot(int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData)
{
	UE_LOG(LogClass, Warning, TEXT("ScreenShot"));
	//UGameViewportClient* gameViewport = GEngine->GameViewport;
	//FViewport* InViewport = gameViewport->Viewport;
	//TArray<FColor> Bitmap;

	//bool bScreenshotSuccessful = GetViewportScreenShot(InViewport, Bitmap);   
	//if (bScreenshotSuccessful)
	//{
	//	FIntVector Size(InViewport->GetSizeXY().X, InViewport->GetSizeXY().Y, 0);
	//	UE_LOG(LogClass, Warning, TEXT("화면 캡쳐 size: %d %d X %d"), Bitmap.Num(), Size.X, Size.Y);

	//	TArray<uint8> CompressedBitmap;
	//	FString savelocation = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	//	FString filename = savelocation + FString(TEXT("/Saved/Screenshots/")) + FString::Printf(TEXT("%d"), TotalFrame) + FString(TEXT(".bmp"));
	//	FImageUtils::CompressImageArray(Size.X, Size.Y, Bitmap, CompressedBitmap);
	//	Manager->StartProcess(TotalFrame, CompressedBitmap);
	//	//FFileHelper::SaveArrayToFile(CompressedBitmap, *filename);
	//}

	TArray<uint8> CompressedBitmap;
	//FImageUtils::CompressImageArray(InSizeX, InSizeY, InImageData, CompressedBitmap);




	//JPEG, PNG
	//UE_LOG(LogClass, Warning, TEXT("화면 캡쳐 size: %d %d X %d"), InImageData.Num(), InSizeX, InSizeY);
	//IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	//TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

	//if (!ImageWrapper.IsValid())
	//{
	//	bIsScreenshotRequested = false;
	//	return;
	//}

	//if (!ImageWrapper->SetRaw(&InImageData[0], InImageData.Num() * sizeof(FColor), InSizeX, InSizeY, ERGBFormat::BGRA, 8))
	//{
	//	bIsScreenshotRequested = false;
	//	return;
	//}

	//
	//const TArray<uint8>& CompressedImage = ImageWrapper->GetCompressed(100);

	//OnScreenshotJpeg.Broadcast(CompressedImage);


	////파일저장
	FString savelocation = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
	FString filename = savelocation + FString(TEXT("/Saved/Screenshots/")) + FString::Printf(TEXT("%d"), TotalFrame) + FString(TEXT(".jpg"));
	Manager->StartProcess(TotalFrame, InSizeX, InSizeY, InImageData);
	//Manager->StartProcess(TotalFrame, CompressedBitmap);

	//FFileHelper::SaveArrayToFile(CompressedImage, *filename);


	//HTTP 전송
	//TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	//HttpRequest->SetVerb("POST");
	//HttpRequest->SetHeader("Content-Type", "image/jpeg");
	//HttpRequest->SetContent(CompressedImage); // TArray<uint8>
	//HttpRequest->SetURL(FString("http://example.com/v1/screenshots"));
	//// Optionally assign HttpRequest->OnProcessRequestComplete() to get a callback when complete
	//HttpRequest->ProcessRequest();


	GEngine->GameViewport->OnScreenshotCaptured().RemoveAll(this);
	bIsScreenshotRequested = false;
}
