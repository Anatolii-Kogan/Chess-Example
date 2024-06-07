#pragma once
#include "../Chess-Example/InputManager.h"
#include "Field.h"
#include <iostream>
#include "ChessmanType.h"
#include "Cell.h"
#include "IFieldFiller.h"
#include <cmath>
#include <stdexcept>

using namespace std;

namespace chessControllers
{
	Field::Field(int sizeX, int sizeY, structs::CircularList<int> movesOrder) : SIZE_X(sizeX), SIZE_Y(sizeY), _movesOrder(movesOrder)
	{
		if (SIZE_X <= 0 || SIZE_Y <= 0) {
			throw std::invalid_argument("Field size have to be >0");
		}

		_field = new Cell[SIZE_X * SIZE_Y];

		for (int row = 0; row < SIZE_Y; ++row)
		{
			for (int column = 0; column < SIZE_X; ++column)
			{
				_field[row * SIZE_X + column] = cells::Cell(column, row);
			}
		}

		_currentTeam = _movesOrder.GetNext();
	}

	Field::~Field()
	{
		delete[] _field;
	}

	bool Field::CheckObstacles(int index1, int index2)
	{
		int column1 = GetColumnByIndex(index1);
		int row1 = GetRowByIndex(index1);

		int column2 = GetColumnByIndex(index2);
		int row2 = GetRowByIndex(index2);

		if (row1 == row2 || column1 == column2 || std::abs(row2 - row1) == std::abs(column2 - column1))
		{
			int stepRow = (row2 > row1) ? 1 : (row2 < row1) ? -1 : 0;
			int stepColumn = (column2 > column1) ? 1 : (column2 < column1) ? -1 : 0;

			int indexRow = row1 + stepRow;
			int indexColumn = column1 + stepColumn;

			while (indexRow != row2 || indexColumn != column2)
			{
				if (!_field[GetIndex(indexRow, indexColumn)].IsEmpty())
				{
					return true;
				}

				if (indexRow != row2)
				{
					indexRow += stepRow;
				}
				if (indexColumn != column2)
				{
					indexColumn += stepColumn;
				}
			}
		}

		return false;
	}

	bool Field::ExecutePredetermined(info::MoveInfo& moveInfo)
	{
		bool result = ReleaseSelection(moveInfo.SelectedIndex, moveInfo.MoveToIndex, moveInfo.Taken);
		if (result == true)
		{
			_currentTeam = _movesOrder.GetNext();
		}

		return result;
	}

	bool Field::Execute(info::MoveInfo& moveInfo)
	{
		SelectCells(moveInfo);
		bool result = ExecutePredetermined(moveInfo);

		moveInfo.Reset();

		return result;
	}

	void Field::SelectCells(info::MoveInfo& moveInfo)
	{
		int selectedIndex;

		while (!moveInfo.IsReadyToMove())
		{
			selectedIndex = input::InputManager::GetChessNotationInput(SIZE_X, SIZE_Y);

			bool result = TrySelectCell(selectedIndex, moveInfo);
		}
	}

	bool Field::TrySelectCell(const int index, info::MoveInfo& moveInfo)
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

	bool Field::ReleaseSelection(int selectedIndex, int moveToIndex, chessmans::ChessmanType& taken)
	{
		bool result;
		bool haveObstacles = CheckObstacles(selectedIndex, moveToIndex);

		if (!IsCastling(&_field[selectedIndex], &_field[moveToIndex], haveObstacles))
		{
			auto cache = _field[moveToIndex].OccupiedBy();

			result = _field[selectedIndex].TryMoveTo(&_field[moveToIndex], haveObstacles);
			taken = result ? cache : chessmans::None;
		}
		else
		{
			int kingIndex = _field[selectedIndex].OccupiedBy() == chessmans::King ?
				selectedIndex : moveToIndex;
			int rookIndex = kingIndex == selectedIndex ? moveToIndex : selectedIndex;

			int direction = (rookIndex % SIZE_X) - (kingIndex % SIZE_X);
			direction = (direction > 0) - (direction < 0); //normalized direction

			int kingMoveToIndex = kingIndex + 2 * direction;
			int rookMoveToIndex = kingMoveToIndex - direction;

			_field[kingIndex].MoveTo(&_field[kingMoveToIndex]);
			_field[rookIndex].MoveTo(&_field[rookMoveToIndex]);

			result = true;
		}

		return result;
	}

	bool Field::IsCastling(Cell* selected, Cell* moveTo, bool haveObstacles)
	{
		if (haveObstacles)
		{
			return false;
		}

		if (selected->IsEmpty() || moveTo->IsEmpty()
			|| selected->IsChessmanDirty() || moveTo->IsChessmanDirty())
		{
			return false;
		}

		switch (selected->OccupiedBy())
		{
		case chessmans::King:
			return moveTo->OccupiedBy() == chessmans::Rook;

		case chessmans::Rook:
			return moveTo->OccupiedBy() == chessmans::King;

		default:
			return false;
		}
	}
}