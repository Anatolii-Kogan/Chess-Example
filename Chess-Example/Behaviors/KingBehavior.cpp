#include "KingBehavior.h"

namespace chessmans
{
	bool KingBehavior::ValidateMove(int directionX, int directionY) const
	{
		if (directionX * directionX > MAX_MOVE_DELTA || directionY * directionY > MAX_MOVE_DELTA)
		{
			return false;
		}

		return directionX == 0 || directionY == 0
			|| directionX / directionY == 1 || directionX / directionY == -1;
	}
	bool KingBehavior::ValidateAttack(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool KingBehavior::ValidateSpecialMove(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool KingBehavior::CanIgnoreObstacles() const
	{
		return false;
	}
	bool KingBehavior::LockAttackMovement() const
	{
		return false;
	}
	ChessmanType KingBehavior::GetType() const
	{
		return ChessmanType::King;
	}
}