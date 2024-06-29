#pragma once
#include <iostream>
#include <Windows.h>
#include <consoleapi2.h>
#include <processenv.h>
#include "IDrawer.h"

using namespace std;

namespace drawers
{
	class FieldDrawer
	{
	public:
		template<int sizeX, int sizeY>
		static void DrawCell(const drawers::IDrawer* cell, int row, int column )
		{
			if ((row + column) % 2 == 0)
				SetConsoleColor<15, 1>(); // White-blue

			cell->Draw();

			SetConsoleColor<15, 0>(); // white-black

			if (column == sizeX - 1)
			{
				wcout << " #" << sizeY - row << endl;
			}
		}

		template<int sizeX>
		static void DrawFieldBasement()
		{
			for (int k = 1; k <= sizeX; ++k)
			{
				wcout << " # ";
			}

			wcout << endl;

			for (int l = 0; l < sizeX; ++l)
			{
				char columnLetter = 'A' + l;
				wcout << ' ' << columnLetter << ' ';
			}

			wcout << endl << endl;
		}

	private:
		template<int textColor, int bgColor>
		static void SetConsoleColor()
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
		}
	};
}