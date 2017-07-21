//
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// Version 2, December 2004
//
// Copyright(C) 2017 One Thawt <one.thawt@protonmail.ch>
// https://github.com/onethawt
//
// Everyone is permitted to copy and distribute verbatim or modified
// copies of this license document, and changing it is allowed as long
// as the name is changed.
//
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
// 0. You just DO WHAT THE FUCK YOU WANT TO.
//

#include <Windows.h>
#include <detours.h>
#include <cstdint>

DWORD (WINAPI *dGetTickCount)(void) = GetTickCount;
DWORD (WINAPI *dtimeGetTime)(void) = timeGetTime;
BOOL(WINAPI *dQueryPerformanceCounter)(LARGE_INTEGER *lpPerformanceCount) = QueryPerformanceCounter;

DWORD BaseTickCount;
DWORD BaseGetTime;
int64_t BasePerformanceCount;
DWORD Acceleration = 5;

DWORD WINAPI GetTickCountHook()
{
	auto currentTickCount = dGetTickCount();
	return BaseTickCount + ((currentTickCount - BaseTickCount) * Acceleration);
}

DWORD WINAPI timeGetTimeHook()
{
	auto currentGetTime = dtimeGetTime();
	return BaseGetTime + ((currentGetTime - BaseGetTime) * Acceleration);
}

BOOL WINAPI QueryPerformanceCounterHook(LARGE_INTEGER *lpPerformanceCount)
{
	int64_t currentPerformanceCount;
	if (!dQueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentPerformanceCount))) return FALSE;
	auto newTime = currentPerformanceCount + ((currentPerformanceCount - BasePerformanceCount) * Acceleration);
	*lpPerformanceCount = *reinterpret_cast<LARGE_INTEGER*>(&newTime);
	return TRUE;
}

DWORD WINAPI InitializeHooks(LPVOID lpParam)
{
	BaseTickCount = GetTickCount();
	BaseGetTime = timeGetTime();
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&BasePerformanceCount));
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)dGetTickCount, GetTickCountHook);
	DetourAttach(&(PVOID&)dtimeGetTime, timeGetTimeHook);
	DetourAttach(&(PVOID&)dQueryPerformanceCounter, QueryPerformanceCounterHook);
	DetourTransactionCommit();

	return 0;
}


BOOLEAN WINAPI DllMain(IN HINSTANCE hDllHandle,
	IN DWORD     nReason,
	IN LPVOID    Reserved)
{
	HANDLE hThread = nullptr;
	switch (nReason)
	{
	case DLL_PROCESS_ATTACH:
		hThread = CreateThread(nullptr, 0, InitializeHooks, nullptr, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	if (hThread != nullptr) return TRUE;
	return FALSE;
}
