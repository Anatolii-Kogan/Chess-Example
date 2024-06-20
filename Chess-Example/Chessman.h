#pragma once
#include "ChassmansCharacters.h"
#include "IChessmanBehavior.h"

namespace chessmans
{
	class Chessman
	{
	private:
		bool _isDirty{ false };
		int _teamIndex;

		int _forwardX;
		int _forwardY;

		IChessmanBehavior* _behavior{ nullptr };

	public:
		Chessman(int teamIndex, int attackDirX, int attackDirY) :
			_teamIndex(teamIndex), _forwardX(attackDirX), _forwardY(attackDirY) 
		{}

		Chessman(int teamIndex, int attackDirX, int attackDirY, IChessmanBehavior* behavior) 
			: Chessman::Chessman(teamIndex, attackDirX, attackDirY)
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

		bool IsFriendly(const Chessman* cellOccupant) const { return _teamIndex == (*cellOccupant)._teamIndex; }
		bool CanIgnoreObstacles() const { return _behavior->CanIgnoreObstacles(); }

		void SetBehavior(IChessmanBehavior* behavior) { _behavior = behavior; }

		bool ValidateMove(int directionX, int directionY) const;
		bool ValidateAttack(int directionX, int directionY, const Chessman* competitiveChessman) const;

		ChessmanType GetType() { return _behavior->GetType(); }
		int GetCost() { return _behavior->GetType(); }

		int GetTeamIndex() { return _teamIndex; }
		wchar_t GetDraw() { return ChassmansCharacters::GetCharacter(_behavior->GetType(), _teamIndex); }
	};
}