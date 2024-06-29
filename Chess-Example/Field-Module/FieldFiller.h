#pragma once
#include "BehaviorContainer.h"
#include "Chessman.h"
using namespace chessmans;

namespace fillers
{
	class FieldFiller 
	{
	private:
		mutable int index = 0;
	public:
		FieldFiller(const BehaviorContainer* behaviors) : _behaviors(behaviors) {}

		Chessman* MoveNext() const
		{
			auto chessman = GetChessmanByIndex();
			++index;
			return chessman;
		}

		void Reset() { index = 0; }

	protected:
		const BehaviorContainer* _behaviors;

		int GetIndex() const { return index; }
		virtual Chessman* GetChessmanByIndex() const = 0;
	};
}
