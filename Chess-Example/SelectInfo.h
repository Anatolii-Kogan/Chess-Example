#pragma once

namespace info
{
	template<typename TCell>
	struct SelectInfo
	{
		int row;
		int column;
		TCell* cell;

		SelectInfo() = default;
		SelectInfo(TCell* cell, int row, int column) : row(row), column(column), cell(cell) {}

		void Set(TCell* cell, int row, int column)
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