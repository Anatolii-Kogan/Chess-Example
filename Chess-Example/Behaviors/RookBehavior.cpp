#include "RookBehavior.h"

namespace chessmans
{
	bool RookBehavior::ValidateMove(int directionX, int directionY) const
	{
		return directionX == 0 || directionY == 0;
	}
	bool RookBehavior::ValidateAttack(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool RookBehavior::ValidateSpecialMove(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool RookBehavior::CanIgnoreObstacles() const
	{
		return false;
	}
	bool RookBehavior::LockAttackMovement() const
	{
		return false;
	}
}