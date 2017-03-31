#ifndef CORE
#define CORE

#include <string>
#include <iostream>
#include "classes.h"

typedef struct{
	class Game* slot[4];
	bool openSlot[4] = {false,};
	int isSpace(void); // return position of first open slot or -1 when error
	int addGame(class Game*);
	int removeGame(int noSlot);

}session_t;

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

int createGame(session_t *);
command_t *parseCMD(std::string&);
int resolveCmd(session_t *, std::string&);

#endif