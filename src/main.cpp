#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "core.h"
#include "classes.h"
// #include <ncurses.h> // Link \w -lncurses

extern int position[];

int main(int argc, char *argv[]){

	static_cast<void> (argc);
	static_cast<void> (argv);

	#pragma message "session_t must be reimplemented to a structure!"
	session currentSession;

	// Game *currentGame = new Game();
	// delete(currentGame);
	// currentSession.slot();

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