#pragma once
#include "Cell.h"
#include "IFieldFiller.h"
#include "CircularList.h"
#include "MoveInfo.h"
#include "FieldDrawer.h"

using namespace cells;

namespace chessControllers
{
	class Field 
		: public drawers::IDrawer
	{
	public:
		const int SIZE_X = 8;
		const int SIZE_Y = 8;

		Field(int sizeX, int sizeY, structs::CircularList<int> movesOrder);
		~Field();

		void FillField(const fillers::IFieldFiller* filler)
		{
			for (int i = SIZE_X * SIZE_Y - 1; i >= 0; --i)
			{
				(_field + i)->SetChessman(filler->MoveNext());
			}
		}

		/// <returns>was move success</returns>
		bool Execute(info::MoveInfo& moveInfo);
		bool ExecutePredetermined(info::MoveInfo& moveInfo);

		void Draw() const override { drawers::FieldDrawer::DrawField(_field, SIZE_X, SIZE_Y); }

	private:
		structs::CircularList<int> _movesOrder;
		int _currentTeam;

		Cell* _field;

		int GetRowByIndex(int index) { return index / SIZE_X; }
		int GetColumnByIndex(int index) { return index % SIZE_X; }
		int GetIndex(int row, int column) { return row * SIZE_X + column; }

		void SelectCells(info::MoveInfo& moveInfo);
		bool ReleaseSelection(int selectedIndex, int moveToIndex, chessmans::ChessmanType& taken);

		bool TrySelectCell(const int index, info::MoveInfo& moveInfo);
		bool CheckObstacles(int index1, int index2);
		bool IsCastling(Cell* selected, Cell* moveTo, bool haveObstacles);
	};
}
