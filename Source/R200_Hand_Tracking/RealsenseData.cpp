// Fill out your copyright notice in the Description page of Project Settings.

#include "R200_Hand_Tracking.h"
#include "RealsenseData.h"
#include "rs.hpp"
#include <vector>

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
	std::vector<uint16_t> divByFourVec;

	for (int y = 0; y < 480; y+=2)
	{
		for (int x = 0; x < 640; x+=2) {
			int currentIndex = y * 640 + x,
				rightIndex = currentIndex + 1,
				downIndex = currentIndex + 640,
				rightDownIndex = downIndex + 1;

			divByFourVec.push_back((depth_frame[currentIndex] + depth_frame[rightIndex] + depth_frame[downIndex] + depth_frame[rightDownIndex]) / 4);
		}
	}

	for (int y = 0; y < 240; y++)
	{
		for (int x = 0; x < 320; x++) {
			if (y == 0 || y == 239 || x == 0 || x == 319 || divByFourVec[y * 320 + x] == 0) {
				depth_data.Add(0);
			} else {
				int currentIndex = y * 320 + x,
					leftIndex = currentIndex - 1,
					rightIndex = currentIndex + 1,
					upIndex = currentIndex - 320,
					upLeftIndex = upIndex - 1,
					upRightIndex = upIndex + 1,
					downIndex = currentIndex + 320,
					downLeftIndex = downIndex - 1,
					downRightIndex = downIndex + 1,
					count = 0;

				if (divByFourVec[upLeftIndex]) count++;
				if (divByFourVec[upIndex]) count++;
				if (divByFourVec[upRightIndex]) count++;
				if (divByFourVec[leftIndex]) count++;
				if (divByFourVec[rightIndex]) count++;
				if (divByFourVec[downLeftIndex]) count++;
				if (divByFourVec[downIndex]) count++;
				if (divByFourVec[downRightIndex]) count++;

				if (count < 8) {
					depth_data.Add(0);
				} else {
					depth_data.Add(divByFourVec[currentIndex]);
				}
			}
		}
	}
}

void ARealsenseData::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	rs::device *dev = ctx.get_device(0);
	dev->stop();
	Super::EndPlay(EndPlayReason);
}