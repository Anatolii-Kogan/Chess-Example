#pragma once
#include "IChessmanBehavior.h"

namespace chessmans
{
	class Chessman
	{
	private:
		bool _isDirty{ false };

		int _forwardX;
		int _forwardY;

	protected:
		IChessmanBehavior* _behavior{ nullptr };

	public:
		Chessman(int forwardX, int forwardY) :
			_forwardX(forwardX), _forwardY(forwardY)
		{}

		Chessman(int forwardX, int forwardY, IChessmanBehavior* behavior)
			: Chessman::Chessman(forwardX, forwardY)
		{
			SetBehavior(behavior);
		}

		void MarkAsDirty()
		{
			if (!_isDirty)
			{
				_isDirty = true;
			}
		}
		bool IsDirty() const { return _isDirty; }

		bool CanIgnoreObstacles() const { return _behavior->CanIgnoreObstacles(); }

		void SetBehavior(IChessmanBehavior* behavior) 
		{ 
			_behavior = behavior;
			OnBehaviorSet();
		}
		virtual void OnBehaviorSet() {};

		virtual bool ValidateMove(int directionX, int directionY) const
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

		bool ValidateAttack(int directionX, int directionY, const Chessman* competitiveChessman) const
		{
			if ((_forwardY * directionY < 0 && _behavior->LockAttackMovement())
				|| competitiveChessman == nullptr)
			{
				return false;
			}

			return _behavior->ValidateAttack(directionX, directionY);
		}

		virtual int GetCost() const { return 0; }
	};
}