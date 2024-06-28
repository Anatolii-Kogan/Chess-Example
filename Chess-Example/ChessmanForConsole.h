#pragma once
#include "../Chess-Example/Field-Module/Chessman.h"
#include "ChassmansCharacters.h"

namespace chessmans
{
	class ChessmanForConsole
		: public Chessman
	{
	private:
		int _teamIndex;

	public:
		ChessmanForConsole(int teamIndex, int forwardX, int forwardY) 
			: Chessman::Chessman(forwardX, forwardY), _teamIndex(teamIndex)
		{}

		ChessmanForConsole(int teamIndex, int forwardX, int forwardY, IChessmanBehavior* behavior)
			: Chessman::Chessman(forwardX, forwardY, behavior), _teamIndex(teamIndex)
		{}

		wchar_t GetDraw() { return ChassmansCharacters::GetCharacter(_behavior, _teamIndex); }
		int GetTeamIndex() const { return _teamIndex; }
		bool IsFriendly(const ChessmanForConsole* cellOccupant) const { return _teamIndex == (*cellOccupant)._teamIndex; }


		bool ValidateAttack(int directionX, int directionY, const ChessmanForConsole* competitiveChessman) const
		{
			return !this->IsFriendly(competitiveChessman) && ValidateAttack(directionX, directionY, competitiveChessman);
		}

		int GetCost() const override { return 0; }
	};
}