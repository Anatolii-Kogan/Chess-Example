#pragma once
#include "IFieldFiller.h"
#include "CircularList.h"

namespace fillers
{
	class ClassicFieldFiller : public IFieldFiller
	{
	public:
		ClassicFieldFiller(const BehaviorContainer* behaviors, int fieldSize, int teamIndex_1, int teamIndex_2)
			: IFieldFiller::IFieldFiller(behaviors), SIZE(fieldSize), TEAM_1(teamIndex_1), TEAM_2(teamIndex_2)
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
		chessmans::Chessman* GetChessmanByIndex() const override;
	};
}
