// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#define DLL extern "C" __declspec(dllexport)

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		// Add the process with the dll
	case DLL_PROCESS_ATTACH:
		// the dll is placed on a thread
	case DLL_THREAD_ATTACH:
		// the dll is remove from the thread
	case DLL_THREAD_DETACH:
		// the process unloads the dll
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

