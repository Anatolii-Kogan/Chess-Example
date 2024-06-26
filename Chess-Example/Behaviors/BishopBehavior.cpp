#include "BishopBehavior.h"

namespace chessmans
{
	bool BishopBehavior::ValidateMove(int directionX, int directionY) const
	{
		if (directionX == 0 || directionY == 0)
		{
			return false;
		}

		int absEquals = directionX / directionY;
		return absEquals == 1 || absEquals == -1;
	}
	bool BishopBehavior::ValidateAttack(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool BishopBehavior::ValidateSpecialMove(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}

	bool BishopBehavior::CanIgnoreObstacles() const
	{
		return false;
	}
	bool BishopBehavior::LockAttackMovement() const
	{
		return false;
	}

	ChessmanType BishopBehavior::GetType() const
	{
		return ChessmanType::Bishop;
	}
}