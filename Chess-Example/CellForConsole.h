#pragma once
#include "../Chess-Example/Field-Module/Cell.h"
#include "../Chess-Example/Drawers/IDrawer.h"
#include "ChessmanForConsole.h"
#include <iostream>
#include "ChessmanType.h"

namespace board
{
	class CellForConsole 
		:  public Cell<chessmans::ChessmanForConsole>, public drawers::IDrawer

	{
	public:
		int OccupiedByTeam() const { return _chessman->GetTeamIndex(); }
		chessmans::ChessmanType OccupiedBy() const { return !IsEmpty() ? _chessman->GetType() : chessmans::None; }

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