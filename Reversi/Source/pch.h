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

enum class Difficulty {
	EASY,
	MEDIUM,
	HARD
};

const int directions[8][2] = {
	{-1,  1}, { 1,  1}, { 0,  1},
	{-1,  0},           { 1,  0},
	{-1, -1}, { 0, -1}, { 1, -1},
};
