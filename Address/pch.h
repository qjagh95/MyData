#pragma once

#ifndef PCH_H
#define PCH_H
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <list>
#include <stdlib.h>
#include <conio.h>
#include <assert.h>
#include <Windows.h>
#include <fstream>
#include <ostream>
#include <atlstr.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

static void GoToxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

enum SCENE_INDEX
{
	SI_MENU,
	SI_INSERT,
	SI_DELETE,
	SI_ALLVIEW,
	SI_SERCH,
	SI_MIDIFY,
};

using namespace std;
#endif //PCH_H
