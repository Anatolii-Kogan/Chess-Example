#pragma once
#include "Cell.h"

namespace info
{
	struct SelectInfo
	{
		int row;
		int column;
		cells::Cell* cell;

		SelectInfo() = default;
		SelectInfo(cells::Cell* cell, int row, int column) : row(row), column(column), cell(cell) {}

		void Set(cells::Cell* cell, int row, int column)
		{
			this->cell = cell;
			this->row = row;
			this->column = column;
		}

		void Reset()
		{
			cell = nullptr;
			row = NULL;
			column = NULL;
		}
	};
}