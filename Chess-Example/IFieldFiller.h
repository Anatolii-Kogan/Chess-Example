#pragma once
#include "../Chess-Example/Behaviors/BehaviorContainer.h"
#include "Chessman.h"

using namespace chessmans;

namespace fillers
{
	class IFieldFiller
	{
	private:
		mutable int index = 0;
	public:
		IFieldFiller(const BehaviorContainer* behaviors) : _behaviors(behaviors) {}

		chessmans::Chessman* MoveNext() const
		{
			auto chessman = GetChessmanByIndex();
			++index;
			return chessman;
		}

		void Reset() { index = 0; }

	protected:
		const BehaviorContainer* _behaviors;

		int GetIndex() const { return index; }
		virtual chessmans::Chessman* GetChessmanByIndex() const = 0;
	};
}
