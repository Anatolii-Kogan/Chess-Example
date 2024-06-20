#pragma once
#include "Field.h"
#include "BehaviorContainer.h"
#include "MoveInfo.h"
#include "IIterator.h"
#include "ClassicFieldFiller.h"

namespace chessControllers
{
	class ChessGameController
	{
	public:
		ChessGameController(structs::IIterator<int>* movesOrder) : _field(Field<FIELD_SIZE, FIELD_SIZE>(movesOrder))
		{
			_behaviors = new BehaviorContainer();

			int teamIndex_1 = *(movesOrder->GetFirst());
			int teamIndex_2 = *(movesOrder->GetLast());

			fillers::ClassicFieldFiller filler(_behaviors, FIELD_SIZE, teamIndex_1, teamIndex_2);
			_field.FillField(&filler);
		}

		~ChessGameController() { delete _behaviors; }

		info::MoveInfo MoveNext()
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



		void PrintState() { _field.Draw(); }
	private:
		static constexpr int FIELD_SIZE = 8;

		Field<FIELD_SIZE, FIELD_SIZE> _field;
		chessmans::BehaviorContainer* _behaviors;
	};
}
