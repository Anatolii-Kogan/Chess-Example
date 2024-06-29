#pragma once
#include "Chessman.h"
#include <type_traits>
#include <stdexcept>

namespace board
{
	template<typename TChessman>
	class Cell
	{
		static_assert(std::is_convertible_v<TChessman*, chessmans::Chessman*>, "TChessman* must be convertible to Chessman*");

	protected:
		TChessman* _chessman = nullptr;
	public:
		~Cell() { DeleteChessman(); }

		const auto* GetChessman() { return _chessman; }
		void SetChessman(chessmans::Chessman* chessman)
		{
			if (_chessman != nullptr)
			{
				throw std::logic_error("You can't use this method to reassign chessman. Clean this Cell first!");
			}

			_chessman = static_cast<TChessman*>(chessman);
		}

		/// <returns>if there is chessman on that cell, return ptr on it; if not - return nullprt</returns>
		auto* RemoveChessman() 
		{  
			auto* chessman = _chessman;
			_chessman = nullptr;
			return chessman;
		}

		static void ReplaceChessman(Cell<TChessman>* moveFrom, Cell<TChessman>* moveTo) { moveTo->SetChessman(moveFrom->RemoveChessman()); }

		void DeleteChessman()
		{
			if (_chessman != nullptr)
			{
				delete _chessman;
				_chessman = nullptr;
			}
		}

		bool IsEmpty() const { return _chessman == nullptr; }
	};
}