#include "KnightBehavior.h"

namespace chessmans
{
	bool KnightBehavior::ValidateMove(int directionX, int directionY) const
	{
		return (directionX * directionX == 4 && directionY * directionY == 1) 
			|| (directionX * directionX == 1 && directionY * directionY == 4);
	}
	bool KnightBehavior::ValidateAttack(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool KnightBehavior::ValidateSpecialMove(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool KnightBehavior::CanIgnoreObstacles() const
	{
		return true;
	}
	bool KnightBehavior::LockAttackMovement() const
	{
		return false;
	}
}
