#pragma once
#include "IChessmanBehavior.h"

namespace chessmans
{
    const class KnightBehavior : public IChessmanBehavior
    {
    public:
        bool ValidateMove(int directionX, int directionY) const override;
        bool ValidateAttack(int directionX, int directionY) const override;
        bool ValidateSpecialMove(int directionX, int directionY) const override;

        bool CanIgnoreObstacles() const override;
        bool LockAttackMovement() const override;

        ChessmanType GetType() const override;

    };
}
