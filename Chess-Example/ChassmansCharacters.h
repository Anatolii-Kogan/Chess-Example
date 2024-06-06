#pragma once
#include "ChessmanType.h"

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

		/// <param name="teamIndex">if >0 - get white character, if <=0 - get black character</param>character
		static wchar_t GetCharacter(ChessmanType type, int teamIndex = 0)
		{
			bool whiteTeam = teamIndex > 0;

			switch (type)
			{
			case chessmans::Pawn:
				return whiteTeam ? WHITE_PAWN : BLACK_PAWN;

			case chessmans::Knight:
				return whiteTeam ? WHITE_KNIGHT : BLACK_KNIGHT;

			case chessmans::Bishop:
				return whiteTeam ? WHITE_BISHOP : BLACK_BISHOP;

			case chessmans::Rook:
				return whiteTeam ? WHITE_ROOK : BLACK_ROOK;

			case chessmans::Queen:
				return whiteTeam ? WHITE_QUEEN : BLACK_QUEEN;

			case chessmans::King:
				return whiteTeam ? WHITE_KING : BLACK_KING;

			default:
				return BLACK_PAWN;
			}
		}
	};
}
