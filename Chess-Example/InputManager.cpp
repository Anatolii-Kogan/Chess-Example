#pragma once
#include "InputManager.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace input
{
	bool TryParseInput(const char* input, char& letter, int& number)
	{
		if (input == nullptr || !isalpha(input[0]))
		{
			return false;
		}

		number = atoi(input + 1);
		for (size_t i = 1; i < strlen(input); ++i)
		{
			if (!isdigit(input[i]))
			{
				return false;
			}
		}

		letter = toupper(input[0]);
		return true;
	}

	int InputManager::GetChessNotationInput(const int FIELD_SIZE_X, const int FIELD_SIZE_Y)
	{
		const char startAlpha = 'A';
		const char startDigit = '0';
		const char maxAlpha = startAlpha + FIELD_SIZE_X - 1;

		int row, column;

		int inputSize = 3; //base input is format "A1" + '\0'
		for (int i = FIELD_SIZE_Y; i >= 10 ; i = i / 10)
		{
			++inputSize;
		}

		char* input = new char[inputSize];

		bool inputSuccess = false;
		while (!inputSuccess)
		{
			row = 0;
			column = 0;

			wcout << "Expected format 'A1', then A.." << maxAlpha << " and 1.." << FIELD_SIZE_Y << endl;
			cin >> input;

			char letter;
			int number;

			if (!TryParseInput(input, letter, number))
			{
				wcout << "Wrong input.\nTry again" << endl;
				continue;
			}
			
			column = letter - startAlpha;
			row = FIELD_SIZE_Y - number;


			if (row < 0 || row >= FIELD_SIZE_Y || column < 0 || column >= FIELD_SIZE_X)
			{
				wcout << "Row or columns is out of field.\nTry again:" << endl;
				continue;
			}

			inputSuccess = true;
		}

		delete[] input;
		return row * FIELD_SIZE_Y + column;
	}
}