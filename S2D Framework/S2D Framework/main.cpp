#include "Game.h"

//Entry Point for Application
int main(int argc, char* argv[]) {
	auto game = new TheGame(argc, argv);

	delete game;
	return EXIT_SUCCESS;
}