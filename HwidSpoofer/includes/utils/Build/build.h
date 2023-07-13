#pragma once
#include"../../modules/modules.h"
#include"../Image/Image.h"

extern "C" {namespace build_modules
{
	DWORD WINAPI FindTempPathA(_In_ DWORD First, _In_ LPSTR Second) {
		return SpoofReturn(__safecall(GetTempPathA).get(), First, Second); }
	HANDLE WINAPI MakeFileW(_In_ LPCWSTR Name, _In_ DWORD Access, _In_ DWORD Share, _In_ LPSECURITY_ATTRIBUTES Attr, _In_ DWORD Creation, _In_ DWORD Flags, _In_ HANDLE hFile) {
		return SpoofReturn(__safecall(CreateFileW).get(), Name, Access, Share, Attr, Creation, Flags, hFile);
	}

}}

extern "C" {namespace build 
{
	const std::string& GeTempDir(_In_ LPCSTR szImageTitle)
	{
		char TempDir[MAX_PATH] = { 0 };
		const uint32_t GetTempDirPath = build_modules::FindTempPathA(sizeof(TempDir), TempDir);
		const std::string ImagePath = std::string(TempDir) + skCrypt("\\").decrypt() + szImageTitle;
		return ImagePath;
	}

	bool CreateImage(const std::string& file_path, const char* file_address, size_t file_size)
	{
		std::ofstream file_result(file_path.c_str(), std::ios_base::out || std::ios_base::binary);
		if (!file_result.write(file_address, file_size)) { file_result.close(); return false; }
		file_result.close(); return true;
	}

	void* CreateImageFromMemory(const char* file_title, const char* file_address, size_t file_size)
	{
		if (!CreateImage(GeTempDir(file_title).c_str(), file_address, file_size)) { return nullptr; }
		return build_modules::MakeFileW(skCrypt(L"").decrypt(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
}}