#pragma once
#include "../Field-Module/IChessmanBehavior.h"

namespace chessmans
{
    const class KingBehavior : public IChessmanBehavior
    {
    public:
        bool ValidateMove(int directionX, int directionY) const override
        {
            if (directionX * directionX > MAX_MOVE_DELTA || directionY * directionY > MAX_MOVE_DELTA)
            {
                return false;
            }

            return directionX == 0 || directionY == 0
                || directionX / directionY == 1 || directionX / directionY == -1; 
        }

        bool ValidateAttack(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }
        bool ValidateSpecialMove(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }

        bool CanIgnoreObstacles() const override { return false; }
        bool LockAttackMovement() const override { return false; }

    private:
        const int MAX_MOVE_DELTA = 1;
    };
}
