// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Disaster.h"
#include "Volcano.generated.h"

/**
 * 
 */
UCLASS()
class ISLANDOFDISASTER_API AVolcano : public ADisaster
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Effect1() override;
	virtual void Effect2() override;
	virtual void Effect3() override;

	UPROPERTY(EditAnywhere, Category = Spawn)
	TArray<FVector> SmokeSpawnPos;

private:
	bool IsSpawned[22];

	int SpawnCnt;
	int PosCnt;

	int tree[89];

	int Init(int s, int e, int node) {
		if (s == e) return tree[node] = 1;
		int m = (s + e) >> 1;
		return tree[node] = Init(s, m, node << 1) + Init(m + 1, e, node << 1 | 1);
	};

	void Update(int s, int e, int node, int idx) {
		if (idx < s || e < idx) return;
		if (s == e) {
			tree[node] = 0;
			return;
		}
		int m = (s + e) >> 1;
		Update(s, m, node << 1, idx);
		Update(m + 1, e, node << 1 | 1, idx);
		tree[node] = tree[node << 1] + tree[node << 1 | 1];
	};

	int Query(int s, int e, int node, int idx) {
		if (s == e) return s;
		int m = (s + e) >> 1;
		int l = tree[node << 1];
		if (l >= idx) return Query(s, m, node << 1, idx);
		else return Query(m + 1, e, node << 1 | 1, idx - l);
	};

};
