#pragma once
#include "ChessmanForConsole.h"
#include "CellForConsole.h"
#include "SelectInfo.h"
#include "../Chess-Example/Field-Module/Field.h"

namespace board
{
	bool IsCastling(const chessmans::ChessmanForConsole* chessman1, const chessmans::ChessmanForConsole* chessman2)
	{
		if (chessman1 == nullptr || chessman2 == nullptr ||
			chessman1->IsDirty() || chessman2->IsDirty())
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
		return false;
	}

	template<int FIELD_SIZE_X, int FIELD_SIZE_Y>
	void MakeCastling(info::SelectInfo<CellForConsole> selectFirst, info::SelectInfo<CellForConsole> selectSecond, Field<FIELD_SIZE_X, FIELD_SIZE_Y, CellForConsole, ChessmanForConsole>& field)
	{
		CellForConsole* kingCell;
		CellForConsole* rookCell;

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

		CellForConsole::ReplaceChessman(kingCell, field.GetCell(selectFirst.row, selectFirst.column + 2 * kingMoveDirection));
		CellForConsole::ReplaceChessman(rookCell, field.GetCell(selectFirst.row, selectFirst.column + kingMoveDirection));
	}
}