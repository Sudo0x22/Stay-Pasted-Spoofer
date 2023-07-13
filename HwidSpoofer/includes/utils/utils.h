#pragma once
#include"Process/process.h"
#include"Build/build.h"

extern "C" {namespace thread
{
	NTSTATUS WINAPI InitThread(_In_ PSYSTEM_MEMORY pMemory)
	{
		if (pMemory != NULL && pMemory->dwEP != NULL)
		{
			INIT_MEM CALL_MEM = (INIT_MEM)pMemory->dwEP;
			CALL_MEM(pMemory->dwParam);
		}
		return STATUS_SUCCESS;
	}

	NTSTATUS WINAPI MakeThread(_In_ LPTHREAD_START_ROUTINE EntryPoint, _In_ LPVOID Buffer, _In_ LPDWORD ThreadId)
	{
		return STATUS_SUCCESS;
	}
}}

extern "C" {namespace globals
{
	HWND hWindow = 0;
	RECT hWindowRect = {};
	INT Width = 500;
	INT Height = 500;
}}

extern "C" {namespace strings
{
	std::string stay_pasted_nubs = R"(
  _________ __                 __________                  __             .___
 /   _____//  |______  ___.__. \______   \_____    _______/  |_  ____   __| _/
 \_____  \\   __\__  \<   |  |  |     ___/\__  \  /  ___/\   __\/ __ \ / __ | 
 /        \|  |  / __ \\___  |  |    |     / __ \_\___ \  |  | \  ___// /_/ | 
/_______  /|__| (____  / ____|  |____|    (____  /____  > |__|  \___  >____ | 
        \/           \/\/                      \/     \/            \/     \/ 
)";
}}