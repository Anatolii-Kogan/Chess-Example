#pragma once
#include "../Field-Module/IChessmanBehavior.h"

namespace chessmans
{
    const class QueenBehavior : public IChessmanBehavior
    {
    public:
        bool ValidateMove(int directionX, int directionY) const override;
        bool ValidateAttack(int directionX, int directionY) const override;
        bool ValidateSpecialMove(int directionX, int directionY) const override;

        bool CanIgnoreObstacles() const override;
        bool LockAttackMovement() const override;
    };
}
