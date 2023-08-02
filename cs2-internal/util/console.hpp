#pragma once
#include <iostream>
#include <Windows.h>

#ifdef _DEBUG
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)
#elif
#define LOG(fmt, ...)
#endif

namespace console {
	__forceinline void initialize() {
#ifdef _DEBUG
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif
	}

	__forceinline void shutdown() {
#ifdef _DEBUG
		fclose(stdout);
		FreeConsole();
#endif
	}
}