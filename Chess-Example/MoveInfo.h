#pragma once
#include "ChessmanType.h"

namespace info
{
	struct MoveInfo
	{
	private:
		const int DEFAULT_VALUE = -1;
	public:
		int SelectedIndex;
		int MoveToIndex;
		chessmans::ChessmanType	Taken = chessmans::None;

		MoveInfo() : SelectedIndex(DEFAULT_VALUE), MoveToIndex(DEFAULT_VALUE) {}
		MoveInfo(int startValue) : DEFAULT_VALUE(startValue), SelectedIndex(startValue), MoveToIndex(startValue){}

		void Reset()
		{
			SelectedIndex = DEFAULT_VALUE;
			MoveToIndex = DEFAULT_VALUE;
		}

		bool FirstCellSelected() const { return SelectedIndex != DEFAULT_VALUE; }
		bool SecondCellSelected() const { return MoveToIndex != DEFAULT_VALUE; }
		bool IsReadyToMove() const { return FirstCellSelected() && SecondCellSelected(); }
	};
}