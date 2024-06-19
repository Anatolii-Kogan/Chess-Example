#pragma once
#include "Field.h"
#include "IFieldFiller.h"
#include "BehaviorContainer.h"
#include "MoveInfo.h"
#include "IIterator.h"

namespace chessControllers
{
	class GameController
	{
	public:
		GameController(structs::IIterator<int>* movesOrder);
		~GameController();

		info::MoveInfo MoveNext();
		void PrintState() { _field.Draw(); }
	private:
		static constexpr int FIELD_SIZE = 8;

		Field<FIELD_SIZE, FIELD_SIZE> _field;

		fillers::IFieldFiller* _filler;
		chessmans::BehaviorContainer* _behaviors;
	};
}
