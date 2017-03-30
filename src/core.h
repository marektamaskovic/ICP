#ifndef CORE
#define CORE

#include <string>

#include "classes.h"

typedef class Game* session_t[4];
/*
 *  TODO
 *	should be struct with flag for each gameslot.
 */

typedef enum{
	noCMD = -1,
	createG,
	switchG,
	quitG,
	save,
	load,
	show,
	quit,
	popQueueDeck,
	moveCard,
	moveDeck
} command_n;

typedef struct{
	command_n type = noCMD;
	std::vector<std::string> args {""};
} command_t;


static int position[] = {0, 0, 0, 0};

inline int getPosition(void){
	for (int i = 0; i < 4; i++)
	{
		if (position[i] == 0)
			return i;
	}

	return -1;
}

inline std::string getCommandName(command_n a){
	switch(a){
		case(noCMD):
			return "noCMD";
			break;
		case(createG):
			return "createGame";
			break;
		case(switchG):
			return "switchGame";
			break;
		case(quitG):
			return "quitGame";
			break;
		case(save):
			return "save";
			break;
		case(load):
			return "load";
			break;
		case(show):
			return "show";
			break;
		case(quit):
			return "quit";
			break;
		case(popQueueDeck):
			return "popQueueDeck";
			break;
		case(moveCard):
			return "moveCard";
			break;
		case(moveDeck):
			return "moveDeck";
			break;
		default:
			return "";
	}
}

int createGame(session_t);
command_t *parseCMD(std::string&);
int resolveCmd(session_t, std::string&);

#endif