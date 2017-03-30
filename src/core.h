#ifndef CORE
#define CORE

#include <string>

typedef enum{
	noCMD = -1,
	createGame,
	switchGame,
	quitGame,
	save,
	load,
	show,
	quit,
	popQueueDeck,
	moveCard,
	moveDeck
} command_n;

typedef struct{
	command_n type;
	std::vector<std::string> args;
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

command_t *parseCMD(std::string&);
int resolveCmd(std::string&);

#endif