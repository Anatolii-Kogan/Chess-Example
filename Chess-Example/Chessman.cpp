#include "Chessman.h"

namespace chessmans
{

	bool Chessman::ValidateMove(int directionX, int directionY) const
	{
		if (_behavior->LockAttackMovement() && _forwardY * directionY < 0)
		{
			return false;
		}

		if (IsDirty())
		{
			return _behavior->ValidateMove(directionX, directionY);
		}

		return _behavior->ValidateSpecialMove(directionX, directionY);
	}

	bool Chessman::ValidateAttack(int directionX, int directionY, const Chessman* competitiveChessman) const
	{
		if ((_forwardY * directionY < 0 && _behavior->LockAttackMovement())
			|| competitiveChessman == nullptr || this->IsFriendly(competitiveChessman))
		{
			return false;
		}

		return _behavior->ValidateAttack(directionX, directionY);
	}
}