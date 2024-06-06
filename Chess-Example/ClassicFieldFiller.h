#pragma once
#include "IFieldFiller.h"
#include "CircularList.h"

namespace fillers
{
	class ClassicFieldFiller : public IFieldFiller
	{
	public:
		ClassicFieldFiller(const BehaviorContainer* behaviors, int fieldSize, const structs::CircularList<int> movesOrder)
			: IFieldFiller::IFieldFiller(behaviors), SIZE(fieldSize), TEAM_1(movesOrder.GetNext()), TEAM_2(movesOrder.GetNext())
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
