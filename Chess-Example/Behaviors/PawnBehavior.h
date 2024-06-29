#pragma once
#include "../Field-Module/IChessmanBehavior.h"
#include <cstdlib>

namespace chessmans
{
	const class PawnBehavior : public IChessmanBehavior
	{
	public:
		bool ValidateMove(int directionX, int directionY) const override
		{
			return std::abs(directionY) == MAX_MOVE_DELTA && directionX == 0;
		}

		bool ValidateAttack(int directionX, int directionY) const override
		{
			return std::abs(directionX) == MAX_MOVE_DELTA && std::abs(directionY) == MAX_MOVE_DELTA;
		}

		bool ValidateSpecialMove(int directionX, int directionY) const override
		{
			return std::abs(directionY) == 2 * MAX_MOVE_DELTA && directionX == 0
				|| ValidateMove(directionX, directionY);
		}

		bool CanIgnoreObstacles() const override { return false; }
		bool LockAttackMovement() const override { return true; }

	private:
		const int MAX_MOVE_DELTA = 1;
	};
}
