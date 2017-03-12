// Fill out your copyright notice in the Description page of Project Settings.

#include "R200_Hand_Tracking.h"
#include "RealsenseData.h"
#include "rs.hpp"
#include <string>

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

// Sets default values
ARealsenseData::ARealsenseData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARealsenseData::BeginPlay()
{
	Super::BeginPlay();
	if (ctx.get_device_count() == 0) print("No device detected. Is it plugged in?");

	// Enumerate all devices
	//TArray<rs::device *> devices;

	devices.Add(ctx.get_device(0));
	//for (int i = 0; i<ctx.get_device_count(); ++i)
	//{
	//	devices.Add(ctx.get_device(i));
	//}

	// Configure and start our devices
	for (auto dev : devices)
	{
		//dev->enable_stream(rs::stream::depth, rs::preset::best_quality);
		dev->enable_stream(rs::stream::depth, 640, 480, rs::format::z16, 30);
		dev->start();
	}
}

// Called every frame
void ARealsenseData::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	depth_data.Empty();
	rs::device *dev = ctx.get_device(0);
	dev->wait_for_frames();

	const uint16_t * depth_frame = reinterpret_cast<const uint16_t *>(dev->get_frame_data(rs::stream::depth));

	for (int y = 0; y < 480; y+=2)
	{
		for (int x = 0; x < 640; x+=2) {
			int currentIndex = y * 640 + x,
				rightIndex = currentIndex + 1,
				downIndex = currentIndex + 640,
				rightDownIndex = downIndex + 1;

			//depth_data.Add(*depth_frame++);
			depth_data.Add((depth_frame[currentIndex] + depth_frame[rightIndex] + depth_frame[downIndex] + depth_frame[rightDownIndex]) / 4);
		}
	}
}

void ARealsenseData::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	rs::device *dev = ctx.get_device(0);
	dev->stop();
	Super::EndPlay(EndPlayReason);
}