#pragma once
#include "../Chess-Example/Field-Module/FieldFiller.h"
#include "../Chess-Example/Field-Module/BehaviorContainer.h"
#include "ChessmanForConsole.h"
#include "CircularList.h"

namespace fillers
{
	class ClassicFieldFiller : public FieldFiller<chessmans::ChessmanForConsole>
	{
	public:
		ClassicFieldFiller(const BehaviorContainer* behaviors, int fieldSize, int teamIndex_1, int teamIndex_2)
			: FieldFiller::FieldFiller(behaviors), SIZE(fieldSize), TEAM_1(teamIndex_1), TEAM_2(teamIndex_2)
		{
			CalculateChessmansAmount();
		}
	private:
		const int SIZE = 8;
		const int DEFAULT_SIZE = 8;

		const int TEAM_1;
		const int TEAM_2;

		int _rookIndex;
		int _knightIndex;
		int _bishopIndex;

		void CalculateChessmansAmount();

	protected:
		chessmans::ChessmanForConsole* GetChessmanByIndex() const override;
	};
}
