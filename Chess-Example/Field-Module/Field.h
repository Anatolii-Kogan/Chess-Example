#ifndef FIELD_H
#define FIELD_H

#include "Cell.h"
#include "FieldFiller.h"
#include <type_traits>

#ifdef DEBUG
#include <stdexcept>
#endif

namespace board
{
	template<int SIZE_X = 8, int SIZE_Y = 8, typename TCell = Cell<Chessman>, typename TChessman = Chessman>
	class Field
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

		TCell* GetCell(int row, int column) 
		{ 
			if (row >= SIZE_Y && column >= SIZE_X)
			{
				return nullptr;
			}

			return &_field[GetIndex(row, column)];
		}

	private:
		TCell _field[SIZE_X * SIZE_Y];

		int GetIndex(int row, int column)
		{
#ifdef DEBUG
			if (row >= SIZE_Y)
			{
				throw std::out_of_range("Row out of range");
			}
			if (column >= SIZE_X)
			{
				throw std::out_of_range("Column out of range");
			}
#endif
			return row * SIZE_X + column;
		}
	};
}

#endif // !FIELD_H