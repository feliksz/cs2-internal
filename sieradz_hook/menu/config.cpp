#include <algorithm>
#include "config.hpp"

#include <fstream>
#include <direct.h>
#include <iostream>
#include <shlobj.h>
#include <Windows.h>
#pragma comment(lib, "shell32.lib")

const char* get_path() {
	char my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	strcat_s(my_documents, "\\cs2hack");
	_mkdir(my_documents);

	strcat_s(my_documents, "\\");
	strcat_s(my_documents, "config.cfg");

	return my_documents;
}
void config::initialize() {
	BOOL_GET("misc.autojump") = true;
	BOOL_GET("misc.autostrafe") = false;
	CONFIG_GET(i32, "misc.strafespeed") = 250;
}

void config::save() {
	using namespace detail;
	printf("%s\n", get_path());
	std::vector<char> buf;
	std::for_each(items.begin(), items.end(), [&](std::pair<u64, item_t> element) {
		for (int i = 0; i < 8; i++)
			buf.push_back(*(u8*)((u64)&element.first + i));

		for (int i = 0; i < 32; i++)
			buf.push_back(*(u8*)((u64)element.second.data + i));

		printf("%u->%s\n", element.first, element.second.data);
	});

	std::ofstream file("nigga.cfg");
	file.write(buf.data(), buf.size());
	file.close();
}

void config::load() {
	std::vector<char> buf;
	std::ifstream file("nigga.cfg", std::ios::binary);

	buf.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
	file.close();

	using namespace detail;
	for (auto i = 0; i < buf.size(); i += 40)
	{
		auto bf = (const char*)((uintptr_t)buf.data() + i);

		const size_t hash = *(uint64_t*)bf;
		bf += 8;

		items[hash] = *(item_t*)bf;
	}
}
