#pragma once
#include "Chessman.h"
#include "IDrawer.h"
#include "IIterator.h"

namespace cells
{
	class Cell 
		: public drawers::IDrawer
	{
	public:
		Cell() = default;
		~Cell()
		{
			if (_chessman != nullptr)
			{
				delete _chessman;
			}
		}

		static bool CanIgnoreObstacles(const structs::IIterator<Cell>& line);

		/// <summary>
		/// Try move chessman with chessman's move abilities validation
		/// </summary>
		/// <param name="moveToCell">: try move chessman from this cell to moveToCell cell</param>
		/// <returns>true - move was success; false - can't move like that</returns>
		static bool TryMoveTo(const structs::IIterator<Cell>& line, int directionX, int directionY);

		/// <summary>
		/// Move chessman without chessman's move abilities validation
		/// </summary>
		/// <param name="cell">move chessman from this cell to cell</param>
		void MoveTo(Cell* cell);

		void SetChessman(chessmans::Chessman* chessman);
		void Clean();

		void Draw() const override;

		int OccupiedByTeam() { return _chessman->GetTeamIndex(); }
		bool IsEmpty() const { return _chessman == nullptr; }
	private:
		chessmans::Chessman* _chessman;

		bool TryMoveTo(Cell* moveTo, int directionX, int directionY);
		static bool IsCastling(Cell* selected, Cell* moveTo);

		bool IsChessmanDirty() { return _chessman->IsDirty(); }
		chessmans::ChessmanType OccupiedBy() { return !IsEmpty() ? _chessman->GetType() : chessmans::None; }
	};
}