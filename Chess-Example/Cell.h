#pragma once
#include "Chessman.h"

namespace cells
{
	class Cell
	{
	public:
		Cell() : _column(0), _row(0), _chessman(nullptr) {}
		Cell(int column, int row) : _column(column), _row(row), _chessman(nullptr){}
		~Cell()
		{
			if (_chessman != nullptr)
			{
				delete _chessman;
			}
		}

		bool IsEmpty() const { return _chessman == nullptr; }

		/// <summary>
		/// Try move chessman with chessman's move abilities validation
		/// </summary>
		/// <param name="moveToCell">: try move chessman from this cell to moveToCell cell</param>
		/// <returns>true - move was success; false - can't move like that</returns>
		bool TryMoveTo(Cell* moveToCell, bool haveObstacle);

		/// <summary>
		/// Move chessman without chessman's move abilities validation
		/// </summary>
		/// <param name="cell">move chessman from this cell to cell</param>
		void MoveTo(Cell* cell);

		void SetChessman(chessmans::Chessman* chessman);
		void Clean();

		void DrawCell() const;

		chessmans::ChessmanType OccupiedBy() { return !IsEmpty() ? _chessman->GetType() : chessmans::None; }
		int OccupiedByTeam() { return _chessman->GetTeamIndex(); }
		bool IsChessmanDirty() { return _chessman->IsDirty(); }

	private:
		int _column;
		int _row;
		chessmans::Chessman* _chessman;
	};
}