#include "..//Chess-Example/Behaviors/PawnBehavior.h"
#include "..//Chess-Example/Behaviors/KnightBehavior.h"
#include "..//Chess-Example/Behaviors/BishopBehavior.h"
#include "..//Chess-Example/Behaviors/RookBehavior.h"
#include "..//Chess-Example/Behaviors/QueenBehavior.h"
#include "..//Chess-Example/Behaviors/KingBehavior.h"
#include "..//Chess-Example/Field-Module/Chessman.h"
#include "ClassicFieldFiller.h"
#include "..//Chess-Example/Field-Module/IChessmanBehavior.h"

using namespace chessmans;

namespace fillers
{
    void ClassicFieldFiller::CalculateChessmansAmount()
    {
        int baseChessmenFromOneSide = (DEFAULT_SIZE - 2) / 2;
        int chessmenFromOneSide = (SIZE - 2) / 2;

        int extraChessmans = chessmenFromOneSide / baseChessmenFromOneSide;

        _rookIndex = extraChessmans + (chessmenFromOneSide % baseChessmenFromOneSide >= 1 ? 1 : 0);
        _knightIndex = _rookIndex + extraChessmans + (chessmenFromOneSide % baseChessmenFromOneSide > 1 ? 1 : 0);
        _bishopIndex = _knightIndex + extraChessmans + (chessmenFromOneSide % baseChessmenFromOneSide > 2 ? 1 : 0);
    }

    ChessmanForConsole* ClassicFieldFiller::GetChessmanByIndex() const
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

        auto chessman = new ChessmanForConsole(teamIndex, attackDirX, attackDirY);

        //Set behavior:
        IChessmanBehavior* behavior = nullptr;
        if (row == 1 || row == SIZE - 2)
        {
            behavior = _behaviors->GetOrCreate<PawnBehavior>();
        }
        else if(row == 0 || row == SIZE - 1)
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
}
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