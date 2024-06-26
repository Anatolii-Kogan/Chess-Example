#pragma once
#include "../ChessmanType.h"

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

		virtual ChessmanType GetType() const = 0;
	};
}