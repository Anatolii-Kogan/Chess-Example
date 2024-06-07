#pragma once
#include "Field.h"
#include "IFieldFiller.h"
#include "BehaviorContainer.h"
#include "MoveInfo.h"

namespace chessControllers
{
	class GameController
	{
	public:
		GameController();
		~GameController();

		info::MoveInfo MoveNext();
		void PrintState() { _field->Draw(); }
	private:
		const int FIELD_SIZE = 8;

		Field* _field;
		fillers::IFieldFiller* _filler;
		chessmans::BehaviorContainer* _behaviors;
	};
}
