#include "pch.h"
#include <Windows.h>

#include "ModUtils.h"

using namespace ModUtils;

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Log("Activating FasterRespawn...");
	std::vector<uint16_t> pattern = { 0x74, MASKED, 0xf3, 0x0f, 0x10, 0x19 };
	std::vector<uint16_t> originalBytes = { 0x74, 0x06 };
	std::vector<uint8_t> newBytes = { 0xeb, 0x06 };

	uintptr_t patchAddress = SigScan(pattern);
	if (patchAddress != 0)
	{
		Replace(patchAddress, originalBytes, newBytes);
	}
	CloseLog();
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, &MainThread, 0, 0, NULL);
	}
	return 1;
}