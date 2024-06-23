#pragma once
#include "Field.h"
#include "BehaviorContainer.h"
#include "MoveInfo.h"
#include "IIterator.h"
#include "ClassicFieldFiller.h"
#include "Cell.h"
#include "Chessman.h"

namespace chessControllers
{
	class ChessGameController
	{
	public:
		ChessGameController(structs::IIterator<int>* movesOrder) : _field(Field<FIELD_SIZE, FIELD_SIZE>(movesOrder))
		{
			_behaviors = new BehaviorContainer();

			int teamIndex_1 = *(movesOrder->GetFirst());
			int teamIndex_2 = *(movesOrder->GetLast());

			fillers::ClassicFieldFiller filler(_behaviors, FIELD_SIZE, teamIndex_1, teamIndex_2);
			_field.FillField(&filler);
		}

		~ChessGameController() { delete _behaviors; }

		info::MoveInfo MoveNext()
		{
			info::MoveInfo moveInfo;
			bool result = _field.Execute(moveInfo);
			if (result == false)
			{
				wcout << "You can't move like that. Try again." << endl;
				MoveNext();
			}

			return moveInfo;
		}

		static bool IsCastling(chessmans::Chessman* chessman1, chessmans::Chessman* chessman2)
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

		static void MakeCastling(const structs::IIterator<Cell>& line)
		{
			line.ResetIterator();
			auto selectedCell = line.GetFirst();
			auto moveToCell = line.GetLast();

			Cell* cellForKing = nullptr;
			Cell* cellForRook = nullptr;

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
		}


		void PrintState() { _field.Draw(); }
	private:
		static constexpr int FIELD_SIZE = 8;

		Field<FIELD_SIZE, FIELD_SIZE> _field;
		chessmans::BehaviorContainer* _behaviors;
	};
}
