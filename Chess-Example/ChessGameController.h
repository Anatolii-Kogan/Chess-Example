#pragma once
#include "../Chess-Example/CellForConsole.h"
#include "../Chess-Example/ChessmanForConsole.h"
#include "../Chess-Example/Field-Module/BehaviorContainer.h"
#include "../Chess-Example/Field-Module/Field.h"
#include "../Chess-Example/Structs/IIterator.h"
#include "../Chess-Example/Drawers/FieldDrawer.h"
#include "SelectInfo.h"

using namespace chessmans;
using namespace board;

namespace chessControllers
{
	class ChessGameController
	{
		static constexpr int FIELD_SIZE = 8;
		using FieldForConsole = Field<FIELD_SIZE, FIELD_SIZE, CellForConsole, ChessmanForConsole>;
		using Info = info::SelectInfo<CellForConsole>;

	public:
		ChessGameController(structs::IIterator<int>* movesOrder);
		~ChessGameController() { delete _behaviors; }

		void MoveNext()
		{
			bool result = Execute();
			if (result == false)
			{
				wcout << "You can't move like that. Try again." << endl;
				MoveNext();
				return;
			}

			LetNextTeamMove();

			_selectFirst.Reset();
			_selectSecond.Reset();
		}

		void PrintState() 
		{ 
			for (int row = 0; row < FIELD_SIZE; ++row)
			{
				for (int column = 0; column < FIELD_SIZE; ++column)
				{
					drawers::FieldDrawer::DrawCell<FIELD_SIZE, FIELD_SIZE>(_field.GetCell(row, column), row, column);
				}
			}

			drawers::FieldDrawer::DrawFieldBasement<FIELD_SIZE>();
		}

		bool IsGameFinished() { return _isGameFinished; }
	private:
		bool _isGameFinished = false;

		FieldForConsole _field;
		chessmans::BehaviorContainer* _behaviors;

		structs::IIterator<int>* _movesOrder;
		int _currentTeam;

		Info _selectFirst;
		Info _selectSecond;

		void LetNextTeamMove()
		{
			int* value;
			_movesOrder->TryGetNext(value);
			_currentTeam = *value;
		}

		bool Execute();
		void SelectCells();

		bool ValidateSelection(CellForConsole* cell);
		bool ValidateMovement(const ChessmanForConsole* movable, const ChessmanForConsole* validated);

		bool ReadyToMove() { return _selectFirst.cell != nullptr && _selectSecond.cell != nullptr; }
	};
}
