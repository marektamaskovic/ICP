#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "core.h"
#include "classes.h"
#include "json.hpp"
// #include <ncurses.h> // Link \w -lncurses

/*
 *  Used JSON library:
 *  https://github.com/nlohmann/json#license
 */

extern int position[];
session_t currentSession;

int main(int argc, char *argv[]){

	static_cast<void> (argc);
	static_cast<void> (argv);

	Game *currentGame = new Game();
	delete(currentGame);

	std::string cmdBuffer = "";

	std::cout << ">>> ";
	while(getline(std::cin, cmdBuffer)){

		if(cmdBuffer == ""){
			std::cout << std::endl;
			break;
		}

		if(cmdBuffer == "exit()" || cmdBuffer == "exit"){
			break;
		}
		else{
			resolveCmd(&currentSession, cmdBuffer);
		}

		std::cout << ">>> ";
		cmdBuffer = "";
	}
	if(cmdBuffer == ""){
		std::cout << std::endl;
	}

	return 0;
}