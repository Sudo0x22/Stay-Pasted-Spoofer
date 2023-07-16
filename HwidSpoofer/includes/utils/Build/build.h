#pragma once
#include"../../modules/modules.h"
#include"../Image/mapper.h"
#include"../Image/driver.h"

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
	const std::string& get_temp_path(LPCSTR szImageTitle) {
		char temp_dir[MAX_PATH] = { 0 };
		const uint32_t get_temp_dir = __safecall(GetTempPathA).get()(sizeof(temp_dir), temp_dir);
		const std::string image_path = std::string(temp_dir) + skCrypt("\\").decrypt() + szImageTitle;
		return image_path;
	}

	__inline bool __stdcall create_image(const std::string& file_path, const char* file_address, size_t file_size) {
		std::ofstream file_result(file_path.c_str(), std::ios_base::out | std::ios_base::binary);
		if (!file_result.write(file_address, file_size)) { file_result.close(); return false; }
		file_result.close();
		return true;
	}

	__inline HANDLE __stdcall create_image_from_memory(const char* file_title, const char* file_address, size_t file_size) {
		if (!create_image(get_temp_path(file_title).c_str(), file_address, file_size)) { return 0; }
		return __safecall(CreateFileW).get()(skCrypt(L"").decrypt(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
}}