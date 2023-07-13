#pragma once
#include"../../modules/modules.h"

extern "C" {namespace process_modules
{
	BOOL WINAPI _Process32FirstW(_In_ HANDLE hHandle, _In_ PROCESSENTRY32W* ProcEntry) {
		return SpoofReturn(__safecall(Process32FirstW).get(), hHandle, ProcEntry); }
	BOOL WINAPI _Process32NextW(_In_ HANDLE hHandle, _In_ PROCESSENTRY32W* ProcEntry) {
		return SpoofReturn(__safecall(Process32NextW).get(), hHandle, ProcEntry); }
	LPVOID WINAPI _CreateTool32SnapShot(_In_ DWORD dwFlags, _In_ DWORD pID) {
		return SpoofReturn(__safecall(CreateToolhelp32Snapshot).get(), dwFlags, pID); }
	BOOL WINAPI _CloseHandle(_In_ HANDLE hHandle) {
		return SpoofReturn(__safecall(CloseHandle).get(), hHandle); }
	INT WINAPI _Wcscmp(_In_ LPCWSTR Offset, _In_ LPCWSTR Pointer) {
		return SpoofReturn(__safecall(wcscmp).get(), Offset, Pointer); }
}}

extern "C" {namespace process
{
	LPVOID WINAPI GetProcessById(_In_ LPCWSTR ProcImage, _In_ DWORD dwFlags, _In_ DWORD pID)
	{
		PROCESSENTRY32W ProcEntry = { 0 };
		ProcEntry.dwSize = sizeof(PROCESSENTRY32);
		LPVOID ProcSnap = process_modules::_CreateTool32SnapShot(dwFlags, pID);

		if (ProcSnap == INVALID_HANDLE_VALUE) return nullptr;
		if (process_modules::_Process32FirstW(ProcSnap, &ProcEntry) == FALSE) return nullptr;
	
		while (process_modules::_Process32NextW(ProcSnap, &ProcEntry))
		{
			if (!process_modules::_Wcscmp(ProcEntry.szExeFile, ProcImage)) 
			{
				return (LPVOID)ProcEntry.th32ProcessID;
				process_modules::_CloseHandle(ProcSnap);
			}
		}
		process_modules::_CloseHandle(ProcSnap);
		return (LPVOID)pID;
	}
}}

extern "C" {namespace process_list
{
	LPVOID ida = nullptr;
	LPVOID xdbg = nullptr;
	// u can add more here
}}