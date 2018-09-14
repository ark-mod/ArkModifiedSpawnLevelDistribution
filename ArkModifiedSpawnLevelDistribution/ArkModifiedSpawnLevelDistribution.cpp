#include "ArkModifiedSpawnLevelDistribution.h"

#pragma comment(lib, "ArkApi.lib")

DECLARE_HOOK(APrimalDinoCharacter_GetRandomBaseLevel, int, APrimalDinoCharacter*, float);

//int _cdecl Hook_APrimalDinoCharacter_GetRandomBaseLevel(APrimalDinoCharacter* _APrimalDinoCharacter, float ForceRand_NotUsed)

int Hook_APrimalDinoCharacter_GetRandomBaseLevel(APrimalDinoCharacter* _APrimalDinoCharacter, float ForceRand_NotUsed)
{
	//TArray<FDinoBaseLevelWeightEntry> baseLevelWeightEntries = _APrimalDinoCharacter->DinoBaseLevelWeightEntriesField();
	TArray<FDinoBaseLevelWeightEntry>& baseLevelWeightEntries = _APrimalDinoCharacter->DinoBaseLevelWeightEntriesField();

	//standard creatures
	if (baseLevelWeightEntries.Num() == 4 
		&& baseLevelWeightEntries[0].EntryWeight == 1.0 
		&& (baseLevelWeightEntries[0].BaseLevelMinRange == 1.0 || baseLevelWeightEntries[0].BaseLevelMinRange == 5.0)
		&& baseLevelWeightEntries[0].BaseLevelMaxRange == 5.0

		&& baseLevelWeightEntries[1].EntryWeight == 0.5
		&& baseLevelWeightEntries[1].BaseLevelMinRange == 6.0
		&& baseLevelWeightEntries[1].BaseLevelMaxRange == 12.0

		&& baseLevelWeightEntries[2].EntryWeight == 0.25
		&& baseLevelWeightEntries[2].BaseLevelMinRange == 13.0
		&& baseLevelWeightEntries[2].BaseLevelMaxRange == 20.0

		&& fabs(baseLevelWeightEntries[3].EntryWeight - 0.1) < 0.00001
		&& baseLevelWeightEntries[3].BaseLevelMinRange == 21.0
		&& baseLevelWeightEntries[3].BaseLevelMaxRange == 30.0)
	{
		baseLevelWeightEntries[0].EntryWeight = 1.0;
		baseLevelWeightEntries[0].BaseLevelMinRange = 3.0;
		baseLevelWeightEntries[0].BaseLevelMaxRange = 5.0;

		baseLevelWeightEntries[1].EntryWeight = 0.75;
		baseLevelWeightEntries[1].BaseLevelMinRange = 9.0;
		baseLevelWeightEntries[1].BaseLevelMaxRange = 12.0;

		baseLevelWeightEntries[2].EntryWeight = 0.625;
		baseLevelWeightEntries[2].BaseLevelMinRange = 16.5;
		baseLevelWeightEntries[2].BaseLevelMaxRange = 20.0;

		baseLevelWeightEntries[3].EntryWeight = 0.55;
		baseLevelWeightEntries[3].BaseLevelMinRange = 25.5;
		baseLevelWeightEntries[3].BaseLevelMaxRange = 30.0;
	}

	//scorched earth wyverns
	else if (baseLevelWeightEntries.Num() == 4
		&& fabs(baseLevelWeightEntries[0].EntryWeight - 0.600000023841858) < 0.00001
		&& baseLevelWeightEntries[0].BaseLevelMinRange == 1.0
		&& baseLevelWeightEntries[0].BaseLevelMaxRange == 5.0

		&& fabs(baseLevelWeightEntries[1].EntryWeight - 0.300000011920929) < 0.00001
		&& baseLevelWeightEntries[1].BaseLevelMinRange == 6.0
		&& baseLevelWeightEntries[1].BaseLevelMaxRange == 12.0

		&& fabs(baseLevelWeightEntries[2].EntryWeight - 0.300000011920929) < 0.00001
		&& baseLevelWeightEntries[2].BaseLevelMinRange == 13.0
		&& baseLevelWeightEntries[2].BaseLevelMaxRange == 20.0

		&& fabs(baseLevelWeightEntries[3].EntryWeight - 0.300000011920929) < 0.00001
		&& baseLevelWeightEntries[3].BaseLevelMinRange == 21.0
		&& baseLevelWeightEntries[3].BaseLevelMaxRange == 38.0)
	{
		baseLevelWeightEntries[0].EntryWeight = 1.0;
		baseLevelWeightEntries[0].BaseLevelMinRange = 3.0;
		baseLevelWeightEntries[0].BaseLevelMaxRange = 5.0;

		baseLevelWeightEntries[1].EntryWeight = 0.825;
		baseLevelWeightEntries[1].BaseLevelMinRange = 9.0;
		baseLevelWeightEntries[1].BaseLevelMaxRange = 12.0;

		baseLevelWeightEntries[2].EntryWeight = 0.820;
		baseLevelWeightEntries[2].BaseLevelMinRange = 16.5;
		baseLevelWeightEntries[2].BaseLevelMaxRange = 20.0;

		baseLevelWeightEntries[3].EntryWeight = 0.815;
		baseLevelWeightEntries[3].BaseLevelMinRange = 29.5;
		baseLevelWeightEntries[3].BaseLevelMaxRange = 38.0;
	}

	int randomBaseLevel = APrimalDinoCharacter_GetRandomBaseLevel_original(_APrimalDinoCharacter, ForceRand_NotUsed);

	return randomBaseLevel;
}


// Ark::SetHook("APrimalDinoCharacter", "GetRandomBaseLevel", &Hook_APrimalDinoCharacter_GetRandomBaseLevel, reinterpret_cast<LPVOID*>(&APrimalDinoCharacter_GetRandomBaseLevel_original));

void Load()
{
	ArkApi::GetHooks().SetHook("APrimalDinoCharacter.GetRandomBaseLevel", &Hook_APrimalDinoCharacter_GetRandomBaseLevel, &APrimalDinoCharacter_GetRandomBaseLevel_original);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Load();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}