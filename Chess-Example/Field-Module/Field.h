#ifndef FIELD_H
#define FIELD_H

#include "Cell.h"
#include "FieldDrawer.h"
#include "FieldFiller.h"
#include <type_traits>

#ifdef DEBUG
#include <stdexcept>
#endif

namespace board
{
	template<int SIZE_X = 8, int SIZE_Y = 8, typename TCell = Cell<Chessman>, typename TChessman = Chessman>
	class Field
		: public drawers::IDrawer
	{
		static_assert(SIZE_X > 0 && SIZE_Y > 0, "Field size must be greater than 0");
		static_assert(std::is_convertible_v<TCell, Cell<TChessman>>, "TCell must be convertible to Cell<TChessman>");

	public:
		constexpr Field() noexcept = default;

		void FillField(const fillers::FieldFiller* filler)
		{

			for (int i = SIZE_X * SIZE_Y - 1; i >= 0; --i)
			{
				(_field + i)->SetChessman(filler->MoveNext());
			}
		}

		TCell& GetCell(int row, int column) { return _field[GetIndex(row, column)]; }

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
		TCell _field[SIZE_X * SIZE_Y];

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