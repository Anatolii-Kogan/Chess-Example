#pragma once
#include "Cell.h"
#include <iostream>
#include "Chessman.h"
#include "IIterator.h"

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

		if (directionY == 0 && Cell::IsCastling(selectedCell, moveToCell))
		{
			Cell* cellForKing = nullptr;
			Cell* cellForRook = nullptr;

			line.ResetIterator();
			if (selectedCell->OccupiedBy() == chessmans::King)
			{
				int iterations = 2;
				while (line.TryGetNext(cellForKing) && iterations != 0)
				{
					cellForRook = cellForKing;
					--iterations;
				}
			}
			else if (selectedCell->OccupiedBy() == chessmans::Rook)
			{
				Cell* cell;

				while (line.TryGetNext(cell))
				{
					if (cell != moveToCell)
					{
						cellForKing = cellForRook;
						cellForRook = cell;
					}
				}
			}

			selectedCell->MoveTo(cellForKing);
			moveToCell->MoveTo(cellForRook);

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

	bool Cell::IsCastling(Cell* selected, Cell* moveTo)
	{
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

	bool Cell::CanIgnoreObstacles(const structs::IIterator<Cell>& line)
	{
		Cell* firstCell = line.GetFirst();
		Cell* lastCell = line.GetLast();

		line.ResetIterator();
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