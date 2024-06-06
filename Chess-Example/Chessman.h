#pragma once
#include "ChassmansCharacters.h"
#include "IChessmanBehavior.h"

namespace chessmans
{
	class Chessman
	{
	private:
		bool _isDirty;
		int _teamIndex;

		int _forwardX;
		int _forwardY;

		IChessmanBehavior* _behavior;

	public:
		Chessman(int teamIndex, int attackDirX, int attackDirY);
		Chessman(int teamIndex, int attackDirX, int attackDirY, IChessmanBehavior* behavior);

		void MarkAsDirty();
		bool IsDirty() const;

		void SetBehavior(IChessmanBehavior* behavior);

		bool IsFriendly(const Chessman* cellOccupant) const;

		bool ValidateMove(int directionX, int directionY) const;

		bool ValidateAttack(int directionX, int directionY, const Chessman* competitiveChessman) const;

		bool CanIgnoreObstacles() const { return _behavior->CanIgnoreObstacles(); }
		ChessmanType GetType() { return _behavior->GetType(); }
		int GetCost() { return _behavior->GetType(); }

		int GetTeamIndex() { return _teamIndex; }
		wchar_t GetDraw() { return ChassmansCharacters::GetCharacter(_behavior->GetType(), _teamIndex); }
	};
}