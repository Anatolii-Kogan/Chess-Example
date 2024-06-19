#pragma once
#include "../Chess-Example/InputManager.h"
#include "Cell.h"
#include "ChessmanType.h"
#include "Field.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace cells;

namespace chessControllers
{
	template<int SIZE_X, int SIZE_Y>
	constexpr Field<SIZE_X, SIZE_Y>::Field(structs::IIterator<int>* movesOrder) : _movesOrder(movesOrder)
	{
		if (SIZE_X <= 0 || SIZE_Y <= 0) {
			throw std::invalid_argument("Field size have to be >0");
		}

		int* value;
		_movesOrder->TryGetNext(value);
		_currentTeam = *value;
	}

	template<int SIZE_X, int SIZE_Y>
	bool Field<SIZE_X, SIZE_Y>::TryGetLine(int index1, int index2)
	{
		_line.Reset();

		int column1 = GetColumnByIndex(index1);
		int row1 = GetRowByIndex(index1);

		int column2 = GetColumnByIndex(index2);
		int row2 = GetRowByIndex(index2);

		if (row1 == row2 || column1 == column2 || std::abs(row2 - row1) == std::abs(column2 - column1))
		{
			int stepRow = (row2 > row1) ? 1 : (row2 < row1) ? -1 : 0;
			int stepColumn = (column2 > column1) ? 1 : (column2 < column1) ? -1 : 0;

			int currentRow = row1;
			int currentColumn = column1;

			//TODO: reculcalate	index
			int index = 0;
			Cell* cell;
			while (currentRow != row2 || currentColumn != column2)
			{
				cell = &_field[GetIndex(currentRow, currentColumn)];
				_line.Set(index++, cell);

				currentRow += stepRow;
				currentColumn += stepColumn;
			}
			cell = &_field[GetIndex(currentRow, currentColumn)];
			_line.Set(index++, cell);

			return true;
		}

		return false;
	}

	template<int SIZE_X, int SIZE_Y>
	bool Field<SIZE_X, SIZE_Y>::ExecutePredetermined(info::MoveInfo& moveInfo)
	{
		bool result = ReleaseSelection(moveInfo.SelectedIndex, moveInfo.MoveToIndex, moveInfo.Taken);
		if (result == true)
		{
			int* value;
			_movesOrder->TryGetNext(value);
			_currentTeam = *value;
		}

		return result;
	}

	template<int SIZE_X, int SIZE_Y>
	bool Field<SIZE_X, SIZE_Y>::Execute(info::MoveInfo& moveInfo)
	{
		SelectCells(moveInfo);
		bool result = ExecutePredetermined(moveInfo);

		moveInfo.Reset();

		return result;
	}

	template<int SIZE_X, int SIZE_Y>
	void Field<SIZE_X, SIZE_Y>::SelectCells(info::MoveInfo& moveInfo)
	{
		int selectedIndex;

		while (!moveInfo.IsReadyToMove())
		{
			selectedIndex = input::InputManager::GetChessNotationInput(SIZE_X, SIZE_Y);

			bool result = TrySelectCell(selectedIndex, moveInfo);
		}
	}

	template<int SIZE_X, int SIZE_Y>
	bool Field<SIZE_X, SIZE_Y>::TrySelectCell(const int index, info::MoveInfo& moveInfo)
	{
		if (moveInfo.IsReadyToMove())
		{
			moveInfo.Reset();
		}

		if (!moveInfo.FirstCellSelected())
		{
			if (_field[index].IsEmpty())
			{
				wcout << "Cell is empty" << endl;
				return false;
			}

			if (_field[index].OccupiedByTeam() != _currentTeam)
			{
				wcout << "Now move team with index " << _currentTeam << endl;
				return false;
			}

			moveInfo.SelectedIndex = index;
			wcout << "Move to..." << endl;
		}
		else if (!moveInfo.SecondCellSelected())
		{
			moveInfo.MoveToIndex = index;
		}

		return true;
	}

	template<int SIZE_X, int SIZE_Y>
	bool Field<SIZE_X, SIZE_Y>::ReleaseSelection(int selectedIndex, int moveToIndex, chessmans::ChessmanType& taken)
	{
		bool result = false;

		int directionX = GetColumnByIndex(moveToIndex) - GetColumnByIndex(selectedIndex);
		int directionY = GetRowByIndex(moveToIndex) - GetRowByIndex(selectedIndex);

		if (!TryGetLine(selectedIndex, moveToIndex))
		{
			_line.Reset();
			_line.Set(0, &_field[selectedIndex]);
			_line.Set(1, &_field[moveToIndex]);
		}

		return Cell::TryMoveTo(_line, directionX, directionY);
	}
}