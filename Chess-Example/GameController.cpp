#pragma once
#include "ClassicFieldFiller.h"
#include "GameController.h"
#include "CircularList.h"
#include <iostream>

using namespace cells;

namespace chessControllers
{
	using namespace std;

	GameController::GameController()
	{
		_behaviors = new BehaviorContainer();
		auto movesOrder = structs::CircularList<int>({1, -1});
		_filler = new fillers::ClassicFieldFiller(_behaviors, FIELD_SIZE, movesOrder);

		_field = new Field(FIELD_SIZE, FIELD_SIZE, movesOrder);
		_field->FillField(_filler);
	}

	GameController::~GameController()
	{
		delete _field;
		delete _filler;
		delete _behaviors;
	}

	info::MoveInfo GameController::MoveNext()
	{
		info::MoveInfo moveInfo;
		bool result = _field->Execute(moveInfo);
		if (result == false)
		{
			wcout << "You can't move like that. Try again." << endl;
			MoveNext();
		}

		return moveInfo;
	}

	void GameController::PrintState()
	{
		_field->Draw();
	}
}