#pragma once
#include "../Field-Module/IChessmanBehavior.h"

namespace chessmans
{
	const class BishopBehavior : public IChessmanBehavior
	{
	public:
		bool ValidateMove(int directionX, int directionY) const override
		{
			if (directionX == 0 || directionY == 0)
			{
				return false;
			}

			int absEquals = directionX / directionY;
			return absEquals == 1 || absEquals == -1;
		}
		bool ValidateAttack(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }
		bool ValidateSpecialMove(int directionX, int directionY) const override { return ValidateMove(directionX, directionY); }

		bool CanIgnoreObstacles() const override { return false; }
		bool LockAttackMovement() const override { return false; }
	};
}