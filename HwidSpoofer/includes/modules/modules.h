#pragma once
#include"security/global.h"
#include"spoofer/spoofer.hpp"

#define STATUS_SUCCESS 1
#define STATUS_ERROR 0

typedef struct _SYSTEM_MEMORY
{
	DWORD64 dwEP;
	LPVOID dwParam;
	DWORD dwProtect;
	HINSTANCE dwModule;
	DWORD64 dwModuleSize;
	PBYTE dwModuleBytes;
} SYSTEM_MEMORY, * PSYSTEM_MEMORY;
typedef DWORD(*INIT_MEM)(LPVOID P);

extern "C" {namespace modules
{
	DWORD64 WINAPI GetModuleSize(_In_ DWORD64 hModuleImage)
	{
		PIMAGE_NT_HEADERS nt_headers = (PIMAGE_NT_HEADERS)(hModuleImage + ((PIMAGE_DOS_HEADER)hModuleImage)->e_lfanew);
		return (DWORD64)nt_headers->OptionalHeader.SizeOfImage;
	}

	PBYTE WINAPI GetModuleBytes(_In_ HINSTANCE hInstance, _In_ DWORD64 InstSize, _In_ DWORD64 Byte)
	{
		return (PBYTE)hInstance + InstSize - Byte;
	}
}}