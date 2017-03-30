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

	(void) argc;
	(void) argv;

	session_t session;

	session[0] = new Game();

	(void)session;

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
			resolveCmd(cmdBuffer);
		}

		std::cout << ">>> ";
		cmdBuffer = "";
	}
	if(cmdBuffer == ""){
		std::cout << std::endl;
	}

	return 0;
}