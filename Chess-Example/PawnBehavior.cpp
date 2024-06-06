#pragma once
#include <cstdlib>
#include "PawnBehavior.h"

namespace chessmans
{
	bool PawnBehavior::ValidateMove(int directionX, int directionY) const
	{
		return std::abs(directionY) == MAX_MOVE_DELTA && directionX == 0;
	}

	bool PawnBehavior::ValidateAttack(int directionX, int directionY) const
	{
		return std::abs(directionX) == MAX_MOVE_DELTA && std::abs(directionY) == MAX_MOVE_DELTA;
	}

	bool PawnBehavior::ValidateSpecialMove(int directionX, int directionY) const
	{
		return std::abs(directionY) == 2 * MAX_MOVE_DELTA && directionX == 0
			|| ValidateMove(directionX, directionY);
	}

	bool PawnBehavior::CanIgnoreObstacles() const
	{
		return false;
	}

	bool PawnBehavior::LockAttackMovement() const
	{
		return true;
	}

	ChessmanType PawnBehavior::GetType() const
	{
		return ChessmanType::Pawn;
	}
}