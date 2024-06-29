#pragma once
#include "../Chess-Example/Field-Module/FieldFiller.h"
#include "../Chess-Example/Field-Module/Chessman.h"
#include "../Chess-Example/Field-Module/BehaviorContainer.h"
#include "..//Chess-Example/Behaviors/PawnBehavior.h"
#include "..//Chess-Example/Behaviors/KnightBehavior.h"
#include "..//Chess-Example/Behaviors/BishopBehavior.h"
#include "..//Chess-Example/Behaviors/RookBehavior.h"
#include "..//Chess-Example/Behaviors/QueenBehavior.h"
#include "..//Chess-Example/Behaviors/KingBehavior.h"
#include <type_traits>

namespace fillers
{
    /*
    * 4 2 3 0 8 3 2 4 :: 8
    * 1 1 1 1 1 1 1 1 :: 7
    * _ _ _ _ _ _ _ _ :: 6
    * _ _ _ _ _ _ _ _ :: 5
    * _ _ _ _ _ _ _ _ :: 4
    * _ _ _ _ _ _ _ _ :: 3
    * 1 1 1 1 1 1 1 1 :: 2
    * 4 2 3 0 8 3 2 4 :: 1
    * = = = = = = = =
    * A B C D I F G H
    */
	template<typename TChessman = chessmans::Chessman>
	class ClassicFieldFiller : public FieldFiller
	{
		static_assert(std::is_convertible_v<TChessman*, Chessman*>, "TChessman* must inherit from Chessman*");

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

        void CalculateChessmansAmount()
        {
            int baseChessmenFromOneSide = (DEFAULT_SIZE - 2) / 2;
            int chessmenFromOneSide = (SIZE - 2) / 2;

            int extraChessmans = chessmenFromOneSide / baseChessmenFromOneSide;

            _rookIndex = extraChessmans + (chessmenFromOneSide % baseChessmenFromOneSide >= 1 ? 1 : 0);
            _knightIndex = _rookIndex + extraChessmans + (chessmenFromOneSide % baseChessmenFromOneSide > 1 ? 1 : 0);
            _bishopIndex = _knightIndex + extraChessmans + (chessmenFromOneSide % baseChessmenFromOneSide > 2 ? 1 : 0);
        }

	protected:
		chessmans::Chessman* GetChessmanByIndex() const override
		{
            //Setup:
            int index = GetIndex();

            int row = index / SIZE;
            if (row > 1 && row < 6)
            {
                return nullptr;
            }
            int column = index % SIZE + 1;

            //Create chessman:
            int attackDirX = row > (SIZE / 2) ? 1 : -1;
            int attackDirY = 0;

            int teamIndex = row > (SIZE / 2) ? TEAM_1 : TEAM_2;

            auto chessman = static_cast<TChessman*>(new TChessman(teamIndex, attackDirX, attackDirY));

            //Set behavior:
            IChessmanBehavior* behavior = nullptr;
            if (row == 1 || row == SIZE - 2)
            {
                behavior = _behaviors->GetOrCreate<PawnBehavior>();
            }
            else if (row == 0 || row == SIZE - 1)
            {
                if (column <= _rookIndex || column > SIZE - _rookIndex)
                {
                    behavior = _behaviors->GetOrCreate<RookBehavior>();
                }
                else if (column <= _knightIndex || column > SIZE - _knightIndex)
                {
                    behavior = _behaviors->GetOrCreate<KnightBehavior>();
                }
                else if (column <= _bishopIndex || column > SIZE - _bishopIndex)
                {
                    behavior = _behaviors->GetOrCreate<BishopBehavior>();
                }
                else
                {
                    if (column % 2 == 0)
                    {
                        behavior = _behaviors->GetOrCreate<KingBehavior>();
                    }
                    else
                    {
                        behavior = _behaviors->GetOrCreate<QueenBehavior>();
                    }
                }
            }

            if (behavior != nullptr)
            {
                chessman->SetBehavior(behavior);
                return chessman;
            }

            return nullptr;
		}
	};
}
