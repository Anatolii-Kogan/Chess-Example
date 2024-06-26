#pragma once
#include "IChessmanBehavior.h"

namespace chessmans
{
    const class KingBehavior : public IChessmanBehavior
    {
    public:
        bool ValidateMove(int directionX, int directionY) const override;
        bool ValidateAttack(int directionX, int directionY) const override;
        bool ValidateSpecialMove(int directionX, int directionY) const override;

        bool CanIgnoreObstacles() const override;
        bool LockAttackMovement() const override;

        ChessmanType GetType() const override;

    private:
        const int MAX_MOVE_DELTA = 1;
    };
}
