// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Http.h"


// Reztly Classes
#include "G2SnapshotResponse.h"
#include "Region.h"
#include "Site.h"
#include "Location.h"
#include "Rack.h"
#include "NetboxSiteResponse.h"
#include "NetboxLocationResponse.h"
#include "NetboxRackResponse.h"
#include "NetboxDeviceResponse.h"
#include "TimeStampIDPair.h"
#include "UE4Response.h"

#include "G2Snapshot.h"

#include "NetBoxVisualizationController.generated.h"

UCLASS(Abstract)
class CESIUMNETBOXVISUALIZATION_API ANetBoxVisualizationController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANetBoxVisualizationController();
	~ANetBoxVisualizationController();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "REST Request")
		bool G2Enabled;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "REST Request")
		FString G2Username;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "REST Request")
		FString G2Password;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "REST Request")
		FString G2APIURL;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "REST Request")
		FString UE4NautilusDataUtilsURL;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "REST Request")
		FString NetboxURL;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "REST Request")
		FString NetboxToken;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float KansasLatitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float KansasLongitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float KansasThreshold;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UG2Snapshot* Snapshot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, USite*> NameToSiteMap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, URegion*> NameToRegionMap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, ULocation*> NameToLocationMap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, URack*> NameToRackMap;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<FString, UDevice*> NameToDeviceMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int MaxEntriesPerRequest = 10;

private:
	static const int MAX_DEVICE_NAME_LEN = 64;

	FHttpModule* Http;

	FString G2Token;

	TArray<FTimeStampIDPair> AvailableSnapshots;

	TArray<UDevice*> NewDevices;
	TArray<UDevice*> DevicesToUpdate;

	int NumNewBatches;
	int CurrentNewBatch;

	int NumUpdateBatches;
	int CurrentUpdateDevice;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnSnapshotUpdate();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		UG2Snapshot* GetSnapshot();

	UFUNCTION(BlueprintCallable)
		void RequestBearerToken();
	UFUNCTION(BlueprintCallable)
		void OnBearerTokenResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestSnapshotRange();
	UFUNCTION(BlueprintCallable)
		void OnSnapshotRangeResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestLatestSnapshot();
	UFUNCTION(BlueprintCallable)
		void RequestSnapshot(int SnapshotID);
	UFUNCTION(BlueprintCallable)
		void OnSnapshotResponse(FString ResponseContentString,
								bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestUE4DataUtilsData();
	UFUNCTION(BlueprintCallable)
		void OnUE4DataUtilsResponse(
			FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void ParseG2Snapshot(FG2SnapshotResponse SnapshotIn);
	UFUNCTION(BlueprintCallable)
		void ParseRegionData(TArray<FRegionStruct> NetboxRegions);
	UFUNCTION(BlueprintCallable)
		void ParseSiteData(TArray<FSiteStruct> NetboxSites);
	UFUNCTION(BlueprintCallable)
		void ParseLocationData(TArray<FLocationStruct> NetboxLocations);
	UFUNCTION(BlueprintCallable)
		void ParseRackData(TArray<FRackStruct> NetboxRacks);
	UFUNCTION(BlueprintCallable)
		void ParseNodeData(TArray<FG2NodeStruct> SnapshotNodes);
	UFUNCTION(BlueprintCallable)
		void ParseLinkData(TArray<FLink> SnapshotLinks);
	UFUNCTION(BlueprintCallable)
		void ParseFlowData(TArray<FFlow> SnapshotFlows);
	UFUNCTION(BlueprintCallable)
		void ParseUE4Data(FUE4Response UE4Response);


	UFUNCTION(BlueprintCallable)
		void ParseNodeInfo(FString Info, FString& IPAddress, float& MTU);
	UFUNCTION(BlueprintCallable)
		void ReplaceFlowLinkNodeIDs(TArray<FFlowLink>& FlowLinks,
			UG2Node* StartNode, UG2Node* EndNode);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxRegionsGet();
	UFUNCTION(BlueprintCallable)
		void OnNetboxRegionsGetResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxRegionPatch(FRegionStruct Region);
	UFUNCTION(BlueprintCallable)
		void OnNetboxRegionPatchResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxSitesGet();
	UFUNCTION(BlueprintCallable)
		void OnNetboxSitesGetResponse(FString ResponseContentString,
									  bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxSitePatch(FSiteStruct Site);
	UFUNCTION(BlueprintCallable)
		void OnNetboxSitePatchResponse(FString ResponseContentString,
									   bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxLocationsGet();
	UFUNCTION(BlueprintCallable)
		void OnNetboxLocationsGetResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxLocationPatch(FLocationStruct Rack);
	UFUNCTION(BlueprintCallable)
		void OnNetboxLocationPatchResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxRacksGet();
	UFUNCTION(BlueprintCallable)
		void OnNetboxRacksGetResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxRackPatch(FRackStruct Rack);
	UFUNCTION(BlueprintCallable)
		void OnNetboxRackPatchResponse(FString ResponseContentString,
			bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxDevicesGet();
	UFUNCTION(BlueprintCallable)
		void OnNetboxDevicesResponse(FString ResponseContentString,
									 bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void ParseNetboxDeviceData(FNetboxDeviceResponse NetboxResponse);
	UFUNCTION(BlueprintCallable)
		void CrossReferenceNodeData();
	UFUNCTION(BlueprintCallable)
		bool CompareNodeToNetboxDeviceData(UG2Node* Node);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxDevicesPost();
	UFUNCTION(BlueprintCallable)
		void OnNetboxPostDeviceResponse(FString ResponseContentString,
										bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		void RequestNetboxDevicesPatch();
	UFUNCTION(BlueprintCallable)
		void RequestNetboxDevicePatch(UDevice* Device);
	UFUNCTION(BlueprintCallable)
		void OnNetboxPatchDeviceResponse(FString ResponseContentString,
										 bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
		bool IsValidLatLong(float Latitude, float Longitude);
	UFUNCTION(BlueprintCallable)
		static bool IsHop(FString Name);

};