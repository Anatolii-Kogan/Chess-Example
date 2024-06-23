#ifndef FIELD_H
#define FIELD_H

#include "Cell.h"
#include "FieldDrawer.h"
#include "IFieldFiller.h"

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
	public:
		explicit constexpr Field()
		{
			if (SIZE_X <= 0 || SIZE_Y <= 0) {
				throw std::invalid_argument("Field size have to be >0");
			}

			int* value;
			_movesOrder->TryGetNext(value);
			_currentTeam = *value;
		}

		void FillField(const fillers::IFieldFiller* iFiller)
		{
			auto filler = *iFiller;
			for (int i = SIZE_X * SIZE_Y - 1; i >= 0; --i)
			{
				(_field + i)->SetChessman(filler.MoveNext());
			}
		}

		Cell& GetCell(int row, int column) { return _field[ GetIndex(row, column) ]; }

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

	private:
		Cell _field[SIZE_X * SIZE_Y];

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
	};
}

#endif // !FIELD_H