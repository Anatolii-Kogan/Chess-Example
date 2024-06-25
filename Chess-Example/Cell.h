#pragma once
#include "Chessman.h"
#include <iostream>
#include "IDrawer.h"

namespace cells
{
	class Cell 
		: public drawers::IDrawer
	{
	private:
		chessmans::Chessman* _chessman = nullptr;
	public:
		~Cell() { DeleteChessman(); }

		const auto* GetChessman() { return _chessman; }
		void SetChessman(chessmans::Chessman* chessman)
		{
			if (_chessman != nullptr)
			{
				throw std::logic_error("You can't use this method to reassign chessman. Clean this Cell first!");
			}

			_chessman = chessman;
		}

		/// <returns>if there is chessman on that cell, return ptr on it; if not - return nullprt</returns>
		auto* RemoveChessman() 
		{  
			auto* chessman = _chessman;
			_chessman = nullptr;
			return chessman;
		}

		static void ReplaceChessman(Cell* moveFrom, Cell* moveTo) { moveTo->SetChessman(moveFrom->RemoveChessman()); }

		void DeleteChessman()
		{
			if (_chessman != nullptr)
			{
				delete _chessman;
				_chessman = nullptr;
			}
		}

		void Draw() const override
		{
			if (_chessman != nullptr)
			{
				std::wcout << ' ' << _chessman->GetDraw() << ' ';
			}
			else
			{
				std::wcout << "   ";
			}
		}

		int OccupiedByTeam() const { return _chessman->GetTeamIndex(); }
		int OccupiedBy() const { return !IsEmpty() ? _chessman->GetType() : 0; }
		bool IsEmpty() const { return _chessman == nullptr; }
	};
}