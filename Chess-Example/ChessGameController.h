#pragma once
#include "Field.h"
#include "BehaviorContainer.h"
#include "SelectInfo.h"
#include "IIterator.h"
#include "ClassicFieldFiller.h"
#include "Cell.h"
#include "Chessman.h"
#include "InputManager.h"
#include <stdexcept>

namespace chessControllers
{
	class ChessGameController
	{
	public:
		ChessGameController(structs::IIterator<int>* movesOrder) : _field(Field<FIELD_SIZE, FIELD_SIZE>()), _movesOrder(movesOrder), _selectFirst(info::SelectInfo()), _selectSecond(info::SelectInfo())
		{
			_behaviors = new BehaviorContainer();

			int teamIndex_1 = *(movesOrder->GetFirst());
			int teamIndex_2 = *(movesOrder->GetLast());

			fillers::ClassicFieldFiller filler(_behaviors, FIELD_SIZE, teamIndex_1, teamIndex_2);
			_field.FillField(&filler);

			int* value;
			_movesOrder->TryGetNext(value);
			_currentTeam = *value;
		}

		~ChessGameController() { delete _behaviors; }

		void MoveNext()
		{
			//info::MoveInfo moveInfo;
			bool result = Execute();
			if (result == false)
			{
				wcout << "You can't move like that. Try again." << endl;
				MoveNext();
			}
		}

		static bool IsCastling(const chessmans::Chessman* chessman1, const chessmans::Chessman* chessman2)
		{
			if (chessman1->IsDirty() || chessman2->IsDirty())
			{
				return false;
			}

			switch (chessman1->GetType())
			{
			case chessmans::King:
				return chessman2->GetType() == chessmans::Rook;

			case chessmans::Rook:
				return chessman1->GetType() == chessmans::King;

			default:
				return false;
			}
		}

		void MakeCastling()
		{
			Cell* kingCell;
			Cell* rookCell;

			int kingMoveDirection;
			switch (_selectFirst.cell->OccupiedBy())
			{
			case chessmans::King:
				kingMoveDirection = _selectSecond.column - _selectFirst.column;

				kingCell = _selectFirst.cell;
				rookCell = _selectSecond.cell;
				break;

			case chessmans::Rook:
				kingMoveDirection = _selectFirst.column - _selectSecond.column;

				kingCell = _selectSecond.cell;
				rookCell = _selectFirst.cell;
				break;

			default:
				throw std::logic_error("Call this method only after IsCastling validation");
			}

			kingMoveDirection = kingMoveDirection > 0 ? 1 : -1;

			kingCell->MoveTo(&_field.GetCell(_selectFirst.row, _selectFirst.column + 2 * kingMoveDirection));
			rookCell->MoveTo(&_field.GetCell(_selectFirst.row, _selectFirst.column + kingMoveDirection));
		}

		bool IsGameFinished() { return _isGameFinished; }
		void PrintState() { _field.Draw(); }
	private:
		static constexpr int FIELD_SIZE = 8;

		Field<FIELD_SIZE, FIELD_SIZE> _field;
		chessmans::BehaviorContainer* _behaviors;

		structs::IIterator<int>* _movesOrder;
		int _currentTeam;

		info::SelectInfo _selectFirst;
		info::SelectInfo _selectSecond;

		bool _isGameFinished = false;

		void SelectCells()
		{
			while (!ReadyToMove())
			{
				int row, column;
				input::InputManager::GetChessNotationInput<FIELD_SIZE, FIELD_SIZE>(row, column);

				Cell& cell = _field.GetCell(row, column);
				if (ValidateSelection(cell))
				{
					if (_selectFirst.cell == nullptr)
					{
						_selectFirst.Set(&cell, row, column);
						wcout << "Move to..." << endl;
					}
					else
					{
						_selectSecond.Set(&cell, row, column);
					}
				}
			}
		}

		bool ValidateSelection(Cell& cell)
		{
			if (ReadyToMove())
			{
				_selectFirst.Reset();
				_selectSecond.Reset();
			}

			if (_selectFirst.cell == nullptr)
			{
				if (cell.IsEmpty())
				{
					wcout << "Cell is empty" << endl;
					return false;
				}

				if (cell.OccupiedByTeam() != _currentTeam)
				{
					wcout << "Now move team with index " << _currentTeam << endl;
					return false;
				}
			}

			return true;
		}

		bool ReleaseSelection()
		{
			int directionX = _selectSecond.column - _selectFirst.column;
			int directionY = _selectSecond.row - _selectFirst.row;

			if (!_selectFirst.cell->GetChessman()->CanIgnoreObstacles()
				&& directionX / 2 == 0 && directionY / 2 == 0) //is direction value from -1 to 1
			{
				int currentRow = _selectFirst.row + directionY;
				int currentColumn = _selectFirst.column + directionX;

				Cell* currentCell = &_field.GetCell(currentRow, currentColumn);
				while (currentCell != _selectSecond.cell)
				{
					if (!currentCell->IsEmpty())
					{
						wcout << "There is obstacle(s) on this way" << endl;
						return false;
					}

					currentRow += directionY;
					currentColumn += directionX;

					currentCell = &_field.GetCell(currentRow, currentColumn);
				}
			}

			if (IsCastling(_selectFirst.cell->GetChessman(), _selectSecond.cell->GetChessman()))
			{
				MakeCastling();
				return true;
			}

			auto chessmanUnderAttack = _selectSecond.cell->GetChessman();
			bool tryAttackKing = chessmanUnderAttack != nullptr && chessmanUnderAttack->GetType() == chessmans::King;
			bool result = _selectFirst.cell->TryMoveTo(_selectSecond.cell, directionX, directionY);
			_isGameFinished = tryAttackKing && result;
			return result;
		}

		bool Execute()
		{
			SelectCells();
			bool result = ReleaseSelection();
			if (result == true)
			{
				int* value;
				_movesOrder->TryGetNext(value);
				_currentTeam = *value;
			}

			_selectFirst.Reset();
			_selectSecond.Reset();

			return result;
		}

		bool ReadyToMove() { return _selectFirst.cell != nullptr && _selectSecond.cell != nullptr; }
	};
}
