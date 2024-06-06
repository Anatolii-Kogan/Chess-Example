#include "QueenBehavior.h"

namespace chessmans
{
	bool QueenBehavior::ValidateMove(int directionX, int directionY) const
	{
		return directionX == 0 || directionY == 0
			|| directionX / directionY == 1 || directionX / directionY == -1;
	}
	bool QueenBehavior::ValidateAttack(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool QueenBehavior::ValidateSpecialMove(int directionX, int directionY) const
	{
		return ValidateMove(directionX, directionY);
	}
	bool QueenBehavior::CanIgnoreObstacles() const
	{
		return false;
	}
	bool QueenBehavior::LockAttackMovement() const
	{
		return false;
	}
	ChessmanType QueenBehavior::GetType() const
	{
		return ChessmanType::Queen;
	}
}