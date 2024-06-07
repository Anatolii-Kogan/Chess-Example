#pragma once
#include <iostream>
#include "Cell.h"
#include <Windows.h>
#include <consoleapi2.h>
#include <processenv.h>
using namespace std;

namespace drawers
{
	class FieldDrawer
	{
	public:
		static void DrawField(const cells::Cell* cells, int sizeX, int sizeY)
		{
			for (int row = 0; row < sizeY; ++row)
			{
				for (int column = 0; column < sizeX; ++column)
				{
					if ((row + column) % 2 == 0)
						SetConsoleColor(15, 1); // White-blue

					cells[row* sizeX + column].Draw();

					SetConsoleColor(15, 0); // white-black
				}

				wcout << " #" << sizeY - row << endl;
			}

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
		static void SetConsoleColor(int textColor, int bgColor)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
		}
	};
}