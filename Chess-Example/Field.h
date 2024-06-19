#ifndef FIELD_H
#define FIELD_H

#include "Cell.h"
#include "CircularList.h"
#include "FieldDrawer.h"
#include "IFieldFiller.h"
#include "MoveInfo.h"
#include "LineArray.h"

#ifdef DEBUG
#include <stdexcept>
#endif

using namespace cells;

namespace chessControllers
{
	template<int SIZE_X = 8, int SIZE_Y = 8>
	class Field 
		: public drawers::IDrawer
	{
	private:
		structs::CircularList<int> _movesOrder;
		int _currentTeam;

		Cell _field[SIZE_X * SIZE_Y];
		structs::LineArray<Cell, SIZE_X> _line;

		int GetRowByIndex(int index) { return index / SIZE_X; }
		int GetColumnByIndex(int index) { return index % SIZE_X; }

		int GetIndex(int row, int column) 
		{ 
#ifdef DEBUG
			if (row > SIZE_Y - 1)
			{
				throw std::out_of_range("Row out of range");
			}
			if (column > SIZE_X - 1)
			{
				throw std::out_of_range("Column out of range");
			}
#endif
			return row * SIZE_X + column; 
		}

		void SelectCells(info::MoveInfo& moveInfo);
		bool ReleaseSelection(int selectedIndex, int moveToIndex, chessmans::ChessmanType& taken);

		bool TrySelectCell(const int index, info::MoveInfo& moveInfo);
		bool TryGetLine(int index1, int index2);

	public:

		constexpr Field(structs::CircularList<int> movesOrder);

		void FillField(const fillers::IFieldFiller* filler, structs::CircularList<int> movesOrder)
		{
			_movesOrder = movesOrder;
			for (int i = SIZE_X * SIZE_Y - 1; i >= 0; --i)
			{
				(_field + i)->SetChessman(filler->MoveNext());
			}
		}

		/// <returns>was move success</returns>
		bool Execute(info::MoveInfo& moveInfo);
		bool ExecutePredetermined(info::MoveInfo& moveInfo);

		void Draw() const override 
		{ 
			for (int row = 0; row < SIZE_Y; ++row)
			{
				for (int column = 0; column < SIZE_X; ++column)
				{
					drawers::FieldDrawer::DrawCell<SIZE_X, SIZE_Y>(&(_field[row * SIZE_X + column]), row, column);
				}
			}

			drawers::FieldDrawer::DrawFieldBasement<SIZE_X>();
		}
	};
}

#include "Field.cpp"

#endif // !FIELD_H