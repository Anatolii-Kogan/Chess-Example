#pragma once
#include "Chessman.h"
#include "IDrawer.h"
#include "IIterator.h"

namespace cells
{
	class Cell 
		: public drawers::IDrawer
	{
	private:
		chessmans::Chessman* _chessman = nullptr;
	public:
		~Cell()
		{
			if (_chessman != nullptr)
			{
				delete _chessman;
			}
		}

		/// <summary>
		/// Try move chessman with chessman's move abilities validation
		/// </summary>
		/// <param name="moveToCell">: try move chessman from this cell to moveToCell cell</param>
		/// <returns>true - move was success; false - can't move like that</returns>
		bool TryMoveTo(Cell* moveTo, int directionX, int directionY);

		/// <summary>
		/// Move chessman without chessman's move abilities validation
		/// </summary>
		/// <param name="cell">move chessman from this cell to cell</param>
		void MoveTo(Cell* cell);

		void SetChessman(chessmans::Chessman* chessman);
		const chessmans::Chessman* GetChessman() { return _chessman; }

		void Clean();

		void Draw() const override;

		int OccupiedByTeam() const { return _chessman->GetTeamIndex(); }
		int OccupiedBy() const { return !IsEmpty() ? _chessman->GetType() : 0; }
		bool IsEmpty() const { return _chessman == nullptr; }
	};
}