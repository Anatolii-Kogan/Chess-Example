#pragma once
#include "../Chess-Example/CellForConsole.h"
#include "../Chess-Example/ChessmanForConsole.h"
#include "../Chess-Example/Field-Module/BehaviorContainer.h"
#include "../Chess-Example/Field-Module/Field.h"
#include "ClassicFieldFiller.h"
#include "IIterator.h"
#include "InputManager.h"
#include "SelectInfo.h"
#include <stdexcept>

using namespace chessmans;
using namespace cells;

namespace chessControllers
{
	class ChessGameController
	{
		static constexpr int FIELD_SIZE = 8;
		using FieldForConsole = Field<FIELD_SIZE, FIELD_SIZE, CellForConsole, ChessmanForConsole>;
	public:
		ChessGameController(structs::IIterator<int>* movesOrder) : _field(FieldForConsole()),
			_movesOrder(movesOrder), _selectFirst(info::SelectInfo<CellForConsole>()), _selectSecond(info::SelectInfo<CellForConsole>())
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
			bool result = Execute();
			if (result == false)
			{
				wcout << "You can't move like that. Try again." << endl;
				MoveNext();
			}
		}

		bool IsGameFinished() { return _isGameFinished; }
		void PrintState() { _field.Draw(); }
	private:
		FieldForConsole _field;
		chessmans::BehaviorContainer* _behaviors;

		structs::IIterator<int>* _movesOrder;
		int _currentTeam;

		info::SelectInfo<CellForConsole> _selectFirst;
		info::SelectInfo<CellForConsole> _selectSecond;

		bool _isGameFinished = false;

		void SelectCells()
		{
			while (!ReadyToMove())
			{
				int row, column;
				input::InputManager::GetChessNotationInput<FIELD_SIZE, FIELD_SIZE>(row, column);

				CellForConsole& cell = _field.GetCell(row, column);
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

		bool ValidateSelection(CellForConsole& cell)
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

		bool Execute()
		{
			SelectCells();
			auto* movable = _selectFirst.cell->GetChessman();
			auto* validated = _selectSecond.cell->GetChessman();

			bool result = false;
			if (IsCastling(movable, validated))
			{
				MakeCastling<FIELD_SIZE, FIELD_SIZE>(_selectFirst, _selectSecond, _field);
				result = true;
			}
			else
			{
				//bool tryAttackKing = validated != nullptr && validated->GetType() == chessmans::King;
				bool tryAttackKing = validated != nullptr;
				if (ValidateMovement(movable, validated))
				{
					CellForConsole::ReplaceChessman(_selectFirst.cell, _selectSecond.cell);
					_isGameFinished = tryAttackKing;
					result = true;
				}
			}

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

		bool ValidateMovement(const chessmans::ChessmanForConsole* movable, const chessmans::ChessmanForConsole* validated)
		{
			int directionX = _selectSecond.column - _selectFirst.column;
			int directionY = _selectSecond.row - _selectFirst.row;

			if (!_selectFirst.cell->GetChessman()->CanIgnoreObstacles()
				&& directionX / 2 == 0 && directionY / 2 == 0) //is direction value from -1 to 1
			{
				int currentRow = _selectFirst.row + directionY;
				int currentColumn = _selectFirst.column + directionX;

				CellForConsole* currentCell = &_field.GetCell(currentRow, currentColumn);
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

			if (validated == nullptr)
			{
				return movable->ValidateMove(directionX, directionY);
			}
			else
			{
				return movable->ValidateAttack(directionX, directionY, validated);
			}
		}

		static bool IsCastling(const chessmans::ChessmanForConsole* chessman1, const chessmans::ChessmanForConsole* chessman2)
		{
			if (chessman1 == nullptr || chessman2 == nullptr ||
				chessman1->IsDirty() || chessman2->IsDirty())
			{
				return false;
			}

			/*switch (chessman1->GetType())
			{
			case chessmans::King:
				return chessman2->GetType() == chessmans::Rook;

			case chessmans::Rook:
				return chessman1->GetType() == chessmans::King;

			default:
				return false;
			}*/
			return false;
		}

		template<int FIELD_SIZE_X, int FIELD_SIZE_Y>
		static void MakeCastling(info::SelectInfo<CellForConsole> selectFirst, info::SelectInfo<CellForConsole> selectSecond, FieldForConsole& field)
		{
			/*Cell* kingCell;
			Cell* rookCell;

			int kingMoveDirection;
			switch (selectFirst.cell->OccupiedBy())
			{
			case chessmans::King:
				kingMoveDirection = selectSecond.column - selectFirst.column;

				kingCell = selectFirst.cell;
				rookCell = selectSecond.cell;
				break;

			case chessmans::Rook:
				kingMoveDirection = selectFirst.column - selectSecond.column;

				kingCell = selectSecond.cell;
				rookCell = selectFirst.cell;
				break;

			default:
				throw std::logic_error("Call this method only after IsCastling validation");
			}

			kingMoveDirection = kingMoveDirection > 0 ? 1 : -1;

			Cell::ReplaceChessman(kingCell, &field.GetCell(selectFirst.row, selectFirst.column + 2 * kingMoveDirection));
			Cell::ReplaceChessman(rookCell, &field.GetCell(selectFirst.row, selectFirst.column + kingMoveDirection));*/
		}

		bool ReadyToMove() { return _selectFirst.cell != nullptr && _selectSecond.cell != nullptr; }
	};
}
