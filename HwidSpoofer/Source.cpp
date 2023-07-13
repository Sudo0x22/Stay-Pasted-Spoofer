#include"includes/includes.h"

extern "C" {namespace spoof_call
{
	VOID WINAPI Exit(int exit_code) {
		return SpoofReturn(__safecall(exit).get(), exit_code); }
	BOOL WINAPI SetWndTitle(_In_ LPCSTR szTitle) {
		return SpoofReturn(__safecall(SetConsoleTitleA).get(), szTitle); }
	INT WINAPI SystemCmd(_In_ LPCSTR szCommand) {
		return SpoofReturn(__safecall(system).get(), szCommand); }
	VOID WINAPI WndSleep(_In_ DWORD Time) {
		return SpoofReturn(__safecall(Sleep).get(), Time); }
	HWND WINAPI GetWndConsole() {
		return SpoofReturn(__safecall(GetConsoleWindow).get()); }
	BOOL WINAPI GetWndRect(_In_ HWND hWindow, _In_ RECT* hWindowRect) {
		return SpoofReturn(__safecall(GetWindowRect).get(), hWindow, hWindowRect);}
	BOOL WINAPI MoveWnd(_In_ HWND hWindow, _In_ INT x, _In_ INT y, _In_ INT width, _In_ INT height, _In_ BOOL Repaint) {
		return SpoofReturn(__safecall(MoveWindow).get(), hWindow, x, y, width, height, Repaint); }

}}

extern "C" {namespace anti_attach
{
	NTSTATUS WINAPI BreakDebug()
	{
		while (true)
		{
			process_list::ida = process::GetProcessById(skCrypt(L"ida64.exe").decrypt(), TH32CS_SNAPPROCESS, 0);
			process_list::xdbg = process::GetProcessById(skCrypt(L"xdbg64.exe").decrypt(), TH32CS_SNAPPROCESS, 0);
			if (process_list::ida || process_list::xdbg) { spoof_call::Exit(1); }
		}
		return STATUS_SUCCESS;
	}
}}

extern "C" {namespace initialize
{
	NTSTATUS WINAPI CreateConsoleWindow(LPCSTR WndTitle, LPCSTR ColorCmd)
	{
		spoof_call::SetWndTitle(WndTitle);
		spoof_call::SystemCmd(ColorCmd);
		
		std::cout << strings::stay_pasted_nubs << "\n";
		std::cout << "[ - LOGS - ] -> Initializing Please Wait\n";
		return STATUS_SUCCESS;
	}

	NTSTATUS WINAPI Initialize(LPCSTR WndTitle, LPCSTR ColorCmd)
	{
		CreateConsoleWindow(WndTitle, ColorCmd);
		
		build::CreateImageFromMemory(skCrypt("cmd_mapper.exe").decrypt(), reinterpret_cast<const char*>(cmd_mapper_buffer), sizeof(cmd_mapper_buffer));
		build::CreateImageFromMemory(skCrypt("mapper.sys").decrypt(), reinterpret_cast<const char*>(mapper_buffer), sizeof(mapper_buffer));
		build::CreateImageFromMemory(skCrypt("driver.sys").decrypt(), reinterpret_cast<const char*>(driver_buffer), sizeof(driver_buffer));

		Sleep(5000);

		return STATUS_SUCCESS;
	}
}}

NTSTATUS WINAPI main(HINSTANCE hInstance, DWORD Pointer, LPVOID Buffer)
{
	initialize::Initialize(skCrypt("Stay Pasted").decrypt(), skCrypt("Color 05").decrypt());
	return STATUS_SUCCESS;
}