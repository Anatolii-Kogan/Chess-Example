#pragma once

namespace chessmans
{
	class IChessmanBehavior
	{
	public:
		virtual bool ValidateMove(int directionX, int directionY) const = 0;
		virtual bool ValidateAttack(int directionX, int directionY) const = 0;
		virtual bool ValidateSpecialMove(int directionX, int directionY) const = 0;

		virtual bool CanIgnoreObstacles() const = 0;
		virtual bool LockAttackMovement() const = 0;
	};
}