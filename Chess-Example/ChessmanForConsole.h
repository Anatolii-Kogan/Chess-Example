#pragma once
#include "../Chess-Example/Field-Module/Chessman.h"
#include "ChassmansCharacters.h"
#include "ChessmanType.h"

namespace chessmans
{
	class ChessmanForConsole
		: public Chessman
	{
	private:
		int _teamIndex;

		//info:
		wchar_t _chassmanCharacter = L' ';
		ChessmanType _type = None;

	public:
		ChessmanForConsole(int teamIndex, int forwardX, int forwardY) 
			: Chessman::Chessman(forwardX, forwardY), _teamIndex(teamIndex)
		{}

		ChessmanForConsole(int teamIndex, int forwardX, int forwardY, IChessmanBehavior* behavior)
			: Chessman::Chessman(forwardX, forwardY, behavior), _teamIndex(teamIndex)
		{}

		void OnBehaviorSet() override
		{
			_chassmanCharacter = ChassmansCharacters::GetCharacter(_behavior, _teamIndex);
			_type = ConvertToType(_behavior);
		}

		int GetTeamIndex() const { return _teamIndex; }
		bool IsFriendly(const ChessmanForConsole* cellOccupant) const { return _teamIndex == (*cellOccupant)._teamIndex; }

		bool ValidateAttack(int directionX, int directionY, const ChessmanForConsole* competitiveChessman) const
		{
			return !this->IsFriendly(competitiveChessman) && ValidateAttack(directionX, directionY, competitiveChessman);
		}

		ChessmanType GetType() const { return _type; }
		int GetCost() const override { return _type; }

		wchar_t GetDraw() const { return _chassmanCharacter; }
	};
}