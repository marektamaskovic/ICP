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

	#pragma message "session_t must be reimplemented to a structure!"
	session_t session;

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
			resolveCmd(session, cmdBuffer);
		}

		std::cout << ">>> ";
		cmdBuffer = "";
	}
	if(cmdBuffer == ""){
		std::cout << std::endl;
	}

	return 0;
}