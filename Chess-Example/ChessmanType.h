#pragma once
#include "..//Chess-Example/Behaviors/PawnBehavior.h"
#include "..//Chess-Example/Behaviors/KnightBehavior.h"
#include "..//Chess-Example/Behaviors/BishopBehavior.h"
#include "..//Chess-Example/Behaviors/RookBehavior.h"
#include "..//Chess-Example/Behaviors/QueenBehavior.h"
#include "..//Chess-Example/Behaviors/KingBehavior.h"
#include "..//Chess-Example/Field-Module/IChessmanBehavior.h"

namespace chessmans
{
	/// <summary>
	/// convertation to int returns cost
	/// </summary>
	enum ChessmanType
	{
		None = 0,
		Pawn = 1,
		Knight = 2,
		Bishop = 3,
		Rook = 4,
		Queen = 8,

		/// <summary>
		/// all chessmans's costs sum
		/// </summary>
		King = 34
	};

	static ChessmanType ConvertToType(const IChessmanBehavior* behavior)
	{
		if (dynamic_cast<const PawnBehavior*>(behavior))
		{
			return Pawn;
		}
		if (dynamic_cast<const KnightBehavior*>(behavior))
		{
			return Knight;
		}
		if (dynamic_cast<const BishopBehavior*>(behavior))
		{
			return Bishop;
		}
		if (dynamic_cast<const RookBehavior*>(behavior))
		{
			return Rook;
		}
		if (dynamic_cast<const QueenBehavior*>(behavior))
		{
			return Queen;
		}
		if (dynamic_cast<const KingBehavior*>(behavior))
		{
			return King;
		}

		return None;
	}
}