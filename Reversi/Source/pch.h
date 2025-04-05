#pragma once

#include <windows.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "../resource.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

enum class BoardValue {
	EMPTY,
	BLACK,
	WHITE,
};
