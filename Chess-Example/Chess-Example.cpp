#pragma once
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include "GameController.h"
#include "CircularList.h"

using namespace std;

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	auto gameController = new chessControllers::GameController(structs::CircularList<int>({ 1, -1 }));

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
