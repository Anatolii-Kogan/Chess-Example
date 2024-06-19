#pragma once
#include <type_traits>
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include "GameController.h"
#include "CircularList.h"

using namespace std;

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	constexpr int teamIndexes[] = { 1, -1 };
	constexpr size_t indexesAmount = std::extent<decltype(teamIndexes)>::value;

	structs::CircularList<int, indexesAmount> movesOrder(teamIndexes);

	auto gameController = new chessControllers::GameController(&movesOrder);
	gameController->PrintState();

	bool gameFinished = false;
	do
	{
		auto result = gameController->MoveNext();
		gameController->PrintState();

		gameFinished = result.Taken == chessmans::King;
	} while (!gameFinished);

	delete gameController;

	return 0;
}
