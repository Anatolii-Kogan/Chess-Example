#include "Chessman.h"

namespace chessmans
{
	Chessman::Chessman(int teamIndex, int forwardX, int forwardY)
		:
		_teamIndex(teamIndex),
		_isDirty(false),
		_forwardX(forwardX),
		_forwardY(forwardY),
		_behavior(nullptr)
	{}

	Chessman::Chessman(int teamIndex, int forwardX, int forwardY, IChessmanBehavior* behavior)
		: Chessman::Chessman(teamIndex, forwardX, forwardY)
	{
		SetBehavior(behavior);
	}

	void Chessman::MarkAsDirty()
	{
		if (!_isDirty)
		{
			_isDirty = true;
		}
	}

	void Chessman::SetBehavior(IChessmanBehavior* behavior)
	{
		_behavior = behavior;
	}

	bool Chessman::IsDirty() const
	{
		return _isDirty;
	}

	bool Chessman::IsFriendly(const Chessman* cellOccupant) const
	{
		return _teamIndex == (*cellOccupant)._teamIndex;
	}

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