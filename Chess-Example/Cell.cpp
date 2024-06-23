#pragma once
#include "Cell.h"
#include <iostream>
#include "Chessman.h"
#include "IIterator.h"
#include "ChessGameController.h"

using namespace chessmans;

namespace cells
{
	bool Cell::TryMoveTo(const structs::IIterator<Cell>& line, int directionX, int directionY)
	{
		if (!Cell::CanIgnoreObstacles(line))
		{
			return false;
		}

		line.ResetIterator();
		auto selectedCell = line.GetFirst();
		auto moveToCell = line.GetLast();

		if (chessControllers::ChessGameController::IsCastling(selectedCell->_chessman, moveToCell->_chessman))
		{
			chessControllers::ChessGameController::MakeCastling(line);
			return true;
		}

		return selectedCell->TryMoveTo(moveToCell, directionX, directionY);
	}

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

	bool Cell::CanIgnoreObstacles(const structs::IIterator<Cell>& line)
	{
		line.ResetIterator();
		Cell* firstCell = line.GetFirst();
		Cell* lastCell = line.GetLast();

		Cell* cell;
		while (line.TryGetNext(cell))
		{
			if (!cell->IsEmpty()
				&& cell != firstCell && cell != lastCell
				&& !firstCell->_chessman->CanIgnoreObstacles())
			{
				return false;
			}
		}

		return true;
	}
}