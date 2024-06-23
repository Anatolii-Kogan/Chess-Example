#pragma once
#include "Cell.h"
#include <iostream>
#include "Chessman.h"
#include "IIterator.h"
#include "ChessGameController.h"

using namespace chessmans;

namespace cells
{
	bool Cell::TryMoveTo(Cell* moveTo, int directionX, int directionY)
	{
		bool result = false;
		if (!moveTo->IsEmpty())
		{
			result = _chessman->ValidateAttack(directionX, directionY, moveTo->_chessman);
		}
		else
		{
			result = _chessman->ValidateMove(directionX, directionY);
		}

		if (result == true)
		{
			MoveTo(moveTo);
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