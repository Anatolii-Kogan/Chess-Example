#pragma once
#include "../Chess-Example/CellForConsole.h"
#include "../Chess-Example/ChessmanForConsole.h"
#include "../Chess-Example/Field-Module/BehaviorContainer.h"
#include "../Chess-Example/Structs/IIterator.h"
#include "CastlingResolver.h"
#include "ChessGameController.h"
#include "ClassicFieldFiller.h"
#include "InputManager.h"
#include "SelectInfo.h"
#include <stdexcept>

using namespace chessmans;
using namespace board;

namespace chessControllers
{
	ChessGameController::ChessGameController(structs::IIterator<int>* movesOrder) : _field(FieldForConsole()),
		_movesOrder(movesOrder), _selectFirst(Info()), _selectSecond(Info())
	{
		_behaviors = new BehaviorContainer();

		int teamIndex_1 = *(movesOrder->GetFirst());
		int teamIndex_2 = *(movesOrder->GetLast());

		fillers::ClassicFieldFiller<ChessmanForConsole> filler(_behaviors, FIELD_SIZE, teamIndex_1, teamIndex_2);
		_field.FillField(&filler);

		LetNextTeamMove();
	}

	bool ChessGameController::Execute()
	{
		SelectCells();
		auto* movable = _selectFirst.cell->GetChessman();
		auto* validated = _selectSecond.cell->GetChessman();

		bool result = false;
		if (IsCastling(movable, validated))
		{
			MakeCastling(_selectFirst, _selectSecond, _field);
			result = true;
		}
		else
		{
			bool tryAttackKing = validated != nullptr && validated->GetType() == chessmans::King;
			if (ValidateMovement(movable, validated))
			{
				CellForConsole::ReplaceChessman(_selectFirst.cell, _selectSecond.cell);
				_isGameFinished = tryAttackKing;
				result = true;
			}
		}

		if (result == true)
		{
			if (movable->GetType() == chessmans::Pawn && (_selectFirst.row == 1 || _selectFirst.row == FIELD_SIZE))
			{
				//TODO: reset pawn on queen/knight/bishop
			}
		}

		return result;
	}

	void ChessGameController::SelectCells()
	{
		while (!ReadyToMove())
		{
			int row, column;
			input::InputManager::GetChessNotationInput<FIELD_SIZE, FIELD_SIZE>(row, column);

			CellForConsole* cell = _field.GetCell(row, column);
			if (ValidateSelection(cell))
			{
				if (_selectFirst.cell == nullptr)
				{
					_selectFirst.Set(cell, row, column);
					wcout << "Move to..." << endl;
				}
				else
				{
					_selectSecond.Set(cell, row, column);
				}
			}
		}
	}
	bool ChessGameController::ValidateSelection(CellForConsole* cell)
	{
		if (ReadyToMove())
		{
			_selectFirst.Reset();
			_selectSecond.Reset();
		}

		if (_selectFirst.cell == nullptr)
		{
			if (cell->IsEmpty())
			{
				wcout << "Cell is empty" << endl;
				return false;
			}

			if (cell->OccupiedByTeam() != _currentTeam)
			{
				wcout << "Now move team with index " << _currentTeam << endl;
				return false;
			}
		}

		return true;
	}
	bool ChessGameController::ValidateMovement(const chessmans::ChessmanForConsole* movable, const chessmans::ChessmanForConsole* validated)
	{
		int directionX = _selectSecond.column - _selectFirst.column;
		int directionY = _selectSecond.row - _selectFirst.row;

		if (!_selectFirst.cell->GetChessman()->CanIgnoreObstacles()
			&& directionX / 2 == 0 && directionY / 2 == 0) //is direction value from -1 to 1
		{
			int currentRow = _selectFirst.row + directionY;
			int currentColumn = _selectFirst.column + directionX;

			CellForConsole* currentCell = _field.GetCell(currentRow, currentColumn);
			while (currentCell != _selectSecond.cell)
			{
				if (!currentCell->IsEmpty())
				{
					wcout << "There is obstacle(s) on this way" << endl;
					return false;
				}

				currentRow += directionY;
				currentColumn += directionX;

				currentCell = _field.GetCell(currentRow, currentColumn);
			}
		}

		if (validated == nullptr)
		{
			return movable->ValidateMove(directionX, directionY);
		}
		else
		{
			return movable->ValidateAttack(directionX, directionY, validated);
		}
	}
}