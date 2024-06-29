#pragma once
#include "../Field-Module/IChessmanBehavior.h"

namespace chessmans
{
    const class RookBehavior : public IChessmanBehavior
    {
    public:
        bool ValidateMove(int directionX, int directionY) const override 
        { 
            return directionX == 0 || directionY == 0; 
        }

        bool ValidateAttack(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }
        bool ValidateSpecialMove(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }

        bool CanIgnoreObstacles() const override { return false; }
        bool LockAttackMovement() const override { return false; }
    };
}
