#pragma once

#define ANDROID 1

#ifdef _WIN32
	#if defined(_WIN64)
		#include <Windows.h>
		#define FLO_PLATFORM_WINDOWS
	#elif ANDROID == 0
		#include <Windows.h>
		#define FLO_PLATFORM_WINDOWS_32
	#else
		#define FLO_PLATFORM_ANDROID
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#define FLO_PLATFORM_IPHONE_SIMULATOR
	#elif TARGET_OS_IPHONE == 1
		#define FLO_PLATFORM_IPHONE
	#elif TARGET_OS_MAC == 1
		#define FLO_PLATFORM_MACOS
	#else
		#define FLO_UNDEFINED_PLATFORM
		#error "Unknown Apple platform"
	#endif
#elif defined(__ANDROID__)
	#define FLO_PLATFORM_ANDROID
#elif defined(__linux__)
	#define FLO_PLATFORM_LINUX
#else
	#define FLO_UNDEFINED_PLATFORM
	#error "Unknown platform!"
#endif