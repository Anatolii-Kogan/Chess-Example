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
	class ChassmansCharacters
	{
	public:
		static const wchar_t BLACK_PAWN = L'♙';
		static const wchar_t WHITE_PAWN = L'♟';

		static const wchar_t BLACK_KNIGHT = L'♘';
		static const wchar_t WHITE_KNIGHT = L'♞';

		static const wchar_t BLACK_BISHOP = L'♗';
		static const wchar_t WHITE_BISHOP = L'♝';

		static const wchar_t BLACK_ROOK = L'♖';
		static const wchar_t WHITE_ROOK = L'♜';

		static const wchar_t BLACK_QUEEN = L'♕';
		static const wchar_t WHITE_QUEEN = L'♛';

		static const wchar_t BLACK_KING = L'♔';
		static const wchar_t WHITE_KING = L'♚';

		static wchar_t GetCharacter(const IChessmanBehavior* behavior, int teamIndex) noexcept
		{
			if (dynamic_cast<const PawnBehavior*>(behavior))
			{
				return teamIndex > 0 ? WHITE_PAWN : BLACK_PAWN;
			}
			if (dynamic_cast<const KnightBehavior*>(behavior))
			{
				return teamIndex > 0 ? WHITE_KNIGHT : BLACK_KNIGHT;
			}
			if (dynamic_cast<const BishopBehavior*>(behavior))
			{
				return teamIndex > 0 ? WHITE_BISHOP : BLACK_BISHOP;
			}
			if (dynamic_cast<const RookBehavior*>(behavior))
			{
				return teamIndex > 0 ? WHITE_ROOK : BLACK_ROOK;
			}
			if (dynamic_cast<const QueenBehavior*>(behavior))
			{
				return teamIndex > 0 ? WHITE_QUEEN : BLACK_QUEEN;
			}
			if (dynamic_cast<const KingBehavior*>(behavior))
			{
				return teamIndex > 0 ? WHITE_KING : BLACK_KING;
			}

			return L' ';
		}
	};
}
