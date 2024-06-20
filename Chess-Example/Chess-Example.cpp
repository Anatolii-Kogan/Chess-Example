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

	constexpr int teamMovesOrder[] = { 1, -1 }; //numbers are team's indexes
	constexpr size_t rulesAmount = std::extent<decltype(teamMovesOrder)>::value;

	structs::CircularList<int, rulesAmount> movesOrder(teamMovesOrder);

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
