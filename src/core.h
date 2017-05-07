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
#include <iomanip>
#include "classes.h"

/**
 * session structure which holds CLI and GUI games, open games and its methods
 */
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
	hint_CMD,
	help_CMD
} command_n;

/**
 * command holds type of command and arguments
 */
typedef struct{
	command_n type = no_CMD; /**< command type. */
	std::vector<std::string> args {}; /**< vector of string arguments. When command type expect argument, vector is filled with content. */
} command_t;


static int position[] = {0, 0, 0, 0};

/**
 * @return position of current game.
 * When game exists returns position else return -1 as fail.
 */
inline int getPosition(void){
	for (int i = 0; i < 4; i++)
	{
		if (position[i] == 0)
			return i;
	}

	return -1;
}
/**
 * @return string which is simillar to type of command.
 * Function to print command name.
 */
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
	case(help_CMD):
		return "help";
		break;
	default:
		return "";
	}
}

/**
 * @param session to which should be created Game added
 * @see session_t
 * @return 0 if Game was created else -1 when Game could not be added to session.
 * creates game with 52 cards and deals it on decks, add to session.
 */
int createGame(session_t *);
/**
 * @param string from standard input which should be parsed
 * @return command allocated on heap filled with parsed components.
 * @see command_t
 * Parse CMD defined by input param string. As return is filled, command could be used for various thing.
 */
command_t *parseCMD(std::string&);
/**
 * @param session to which should be resolved Command.
 * @param string which is given to parseCMD function.
 * @see parseCMD.
 * @return 0.
 * When command resolvation was successful or unsuccessful but when resolvation of command is unsuccessful error to std::cout is written.
 */
int resolveCmd(session_t *, std::string&);

/**
 * @param command where are stored arguments and type is moveCard_CMD.
 * @see moveCards.
 * Function parse arguments and create from that vector of Cards and Deck, which is processed to deck method deck->moveCards.
 */
void moveCardDeco(command_t *);
/**
 * @param session which should be closed
 * Quit games in CLI version by command name 'quit()'
 */
void quitGameDeco(session_t *);
/**
 * Prints all commands that are available to use in this application in CLI version
 */
void printHelpMsg();

#endif