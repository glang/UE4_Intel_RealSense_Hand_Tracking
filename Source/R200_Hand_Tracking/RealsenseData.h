// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "rs.hpp"
#include "RealsenseData.generated.h"

UCLASS()
class R200_HAND_TRACKING_API ARealsenseData : public AActor
{
	GENERATED_BODY()
	
public:	
	TArray<rs::device *> devices;
	rs::context ctx;
	// Sets default values for this actor's properties
	ARealsenseData();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Config")
	TArray<int> depth_data;
};
