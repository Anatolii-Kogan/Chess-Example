#pragma once
#include "ClassicFieldFiller.h"
#include "GameController.h"
#include "CircularList.h"
#include <iostream>

using namespace cells;

namespace chessControllers
{
	using namespace std;
	constexpr int GameController::FIELD_SIZE;

	GameController::GameController(structs::CircularList<int> movesOrder) : _field(Field<FIELD_SIZE, FIELD_SIZE>(movesOrder))
	{
		_behaviors = new BehaviorContainer();
		_filler = new fillers::ClassicFieldFiller(_behaviors, FIELD_SIZE, movesOrder);

		_field.FillField(_filler, movesOrder);
	}

	GameController::~GameController()
	{
		delete _filler;
		delete _behaviors;
	}

	info::MoveInfo GameController::MoveNext()
	{
		info::MoveInfo moveInfo;
		bool result = _field.Execute(moveInfo);
		if (result == false)
		{
			wcout << "You can't move like that. Try again." << endl;
			MoveNext();
		}

		return moveInfo;
	}
}