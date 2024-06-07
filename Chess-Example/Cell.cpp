#pragma once
#include "Cell.h"
#include <iostream>
#include "Chessman.h"

using namespace chessmans;

namespace cells
{
	bool Cell::TryMoveTo(Cell* moveToCell, bool haveObstacle)
	{
		if (haveObstacle && !_chessman->CanIgnoreObstacles())
		{
			return false;
		}

		int directionX = moveToCell->_column - _column;
		int directionY = moveToCell->_row - _row;

		bool result = false;
		if (!moveToCell->IsEmpty())
		{
			result = _chessman->ValidateAttack(directionX, directionY, moveToCell->_chessman);
		}
		else
		{
			result = _chessman->ValidateMove(directionX, directionY);
		}

		if (result == true)
		{
			MoveTo(moveToCell);
			return true;
		}
		return false;
	}

	void Cell::MoveTo(Cell* cell)
	{
		if (cell->_chessman != nullptr)
		{
			//TODO: add points
			delete cell->_chessman;
		}
		cell->_chessman = _chessman;
		_chessman->MarkAsDirty();

		_chessman = nullptr;
	}

	void Cell::SetChessman(Chessman* chessman)
	{
		if (_chessman != nullptr)
		{
			throw std::logic_error("You can't use this method to reassign chessman. Clean this Cell first!");
		}

		_chessman = chessman;
	}

	void Cell::Clean()
	{
		if (_chessman != nullptr)
		{
			delete _chessman;
		}
		_chessman = nullptr;
	}

	void Cell::Draw() const
	{
		if (_chessman != nullptr)
		{
			std::wcout << ' ' << _chessman->GetDraw() << ' ';
		}
		else
		{
			std::wcout << "   ";
		}
	}
}