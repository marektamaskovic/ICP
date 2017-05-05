/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */

#ifndef CORE_H
#define CORE_H

#include <string>
#include <iostream>
#include <fstream>
#include "classes.h"

typedef struct{
	// public attributes
	class Game* slot[4];
	bool openSlot[4] = {false,};
	int currentGame = -1;

	// public methods
	int isSpace(void); // return position of first open slot or -1 when error
	int addGame(class Game*);
	int removeGame(int noSlot);

}session_t;

typedef enum{
	no_CMD = -1,
	createG_CMD,
	switchG_CMD,
	quitG_CMD,
	save_CMD,
	load_CMD,
	show_CMD,
	quit_CMD,
	popQueueDeck_CMD,
	moveCard_CMD,
	undo_CMD,
	hint_CMD
} command_n;

typedef struct{
	command_n type = no_CMD;
	std::vector<std::string> args {};
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
	case(no_CMD):
		return "noCMD";
		break;
	case(createG_CMD):
		return "createGame";
		break;
	case(switchG_CMD):
		return "switchGame";
		break;
	case(quitG_CMD):
		return "quitGame";
		break;
	case(save_CMD):
		return "save";
		break;
	case(load_CMD):
		return "load";
		break;
	case(show_CMD):
		return "show";
		break;
	case(quit_CMD):
		return "quit";
		break;
	case(popQueueDeck_CMD):
		return "popQueueDeck";
		break;
	case(moveCard_CMD):
		return "moveCard";
		break;
	case(hint_CMD):
		return "hint";
		break;
	case(undo_CMD):
		return "undo";
		break;
	default:
		return "";
	}
}

int createGame(session_t *);
command_t *parseCMD(std::string&);
int resolveCmd(session_t *, std::string&);
void moveCardDeco(command_t *, session_t *);
void quitGameDeco(session_t *);


#endif