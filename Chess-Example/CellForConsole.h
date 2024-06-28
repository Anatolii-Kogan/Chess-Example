#pragma once
#include "../Chess-Example/Field-Module/Cell.h"
#include "IDrawer.h"
#include "ChessmanForConsole.h"
#include <iostream>

namespace cells
{
	class CellForConsole 
		:  public Cell<chessmans::ChessmanForConsole>, public drawers::IDrawer

	{
	public:
		int OccupiedByTeam() const { return _chessman->GetTeamIndex(); }
		//int OccupiedBy() const { return !IsEmpty() ? _chessman->GetType() : 0; }

		void Draw() const override
		{
			if (IsEmpty())
			{
				std::wcout << "   ";
			}
			else
			{
				std::wcout << ' ' << _chessman->GetDraw() << ' ';
			}
		}
	};
}