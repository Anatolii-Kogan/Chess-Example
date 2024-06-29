#pragma once
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
}