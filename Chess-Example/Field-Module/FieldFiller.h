#pragma once
#include "../Field-Module/BehaviorContainer.h"
#include "../Field-Module/Chessman.h"
#include <type_traits>
using namespace chessmans;

namespace fillers
{
	template<typename TChessman>
	class FieldFiller 
	{
		static_assert(std::is_base_of_v<chessmans::Chessman, TChessman>, "TChessman must inherit from Chessman");

	private:
		mutable int index = 0;
	public:
		FieldFiller(const BehaviorContainer* behaviors) : _behaviors(behaviors) {}

		TChessman* MoveNext() const
		{
			auto chessman = GetChessmanByIndex();
			++index;
			return chessman;
		}

		void Reset() { index = 0; }

	protected:
		const BehaviorContainer* _behaviors;

		int GetIndex() const { return index; }
		virtual TChessman* GetChessmanByIndex() const = 0;
	};
}
