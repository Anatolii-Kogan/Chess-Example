#pragma once
#include "../Field-Module/IChessmanBehavior.h"

namespace chessmans
{
    const class KnightBehavior : public IChessmanBehavior
    {
    public:
        bool ValidateMove(int directionX, int directionY) const override
        {
            return (directionX * directionX == 4 && directionY * directionY == 1)
                || (directionX * directionX == 1 && directionY * directionY == 4);
        }

        bool ValidateAttack(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }
        bool ValidateSpecialMove(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }

        bool CanIgnoreObstacles() const override { return true; }
        bool LockAttackMovement() const override { return false; }
    };
}
