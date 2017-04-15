/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */


#include <iostream>
#include <regex>

#include "core.h"
#include "color.h"

extern session_t currentSession;

int session_t::isSpace(void){
	for(int i = 0; i < 4; i++)
		if(this->openSlot[i] == false) return i;
	return -1;
}

int session_t::addGame(class Game *g){
	int pos;
	if( (pos = this->isSpace()) > -1 ){
		this->slot[pos] = g;
		this->openSlot[pos] = true;
		std::cout << "Game added to a slot No." << pos << std::endl;
		return pos;
	}
	else{
		std::cerr << "Error adding a new game to session. No open slot for the game\n";
		return -1;
	}
}

int session_t::removeGame(int pos){
	if(this->openSlot[pos] == true){
		this->openSlot[pos] = false;
		// FIXME only remove game or should I call a destructor???
		this->slot[pos] = nullptr;
		return 0;
	}
	return 1;
}


command_t* parseCMD(std::string &cmdBuffer){

	command_t *cmd = new command_t;

	char* argument = new char[42];

	if(cmdBuffer == "show()"){
		cmd->type = show_CMD;
	}
	else if(cmdBuffer == "popQD()"){
		cmd->type = popQueueDeck_CMD;
	}
	else if(cmdBuffer == "undo()"){
		cmd->type = undo_CMD;
	}
	else if(cmdBuffer == "createGame()"){
		cmd->type = createG_CMD;
	}
	else if(cmdBuffer == "quit()"){
		cmd->type = quit_CMD;
	}
	else if(cmdBuffer == "quitGame()"){
		cmd->type = quitG_CMD;
	}
	else if(sscanf(cmdBuffer.c_str(),"switchGame(%s)",argument) != EOF){
		cmd->args.push_back(argument);
		cmd->type = switchG_CMD;
	}
	else if(sscanf(cmdBuffer.c_str(),"save(%s)",argument) != EOF){
		cmd->args.push_back(argument);
		cmd->type = save_CMD;
	}
	else if(sscanf(cmdBuffer.c_str(),"load(%s)",argument) != EOF){
		cmd->args.push_back(argument);
		cmd->type = load_CMD;
	}
	else
		cmd->type = no_CMD;

	delete(argument);
	return cmd;
}

int resolveCmd(session_t *session, std::string &cmdBuffer){

	command_t *cmd = parseCMD(cmdBuffer);

	std::cout << "Cmd: '"
			  << getCommandName(cmd->type)
			  << "'"
			  << std::endl;

	int num;
	// Deck *flip = session->slot[session->currentGame]->flip;
	// Deck *flop = session->slot[session->currentGame]->flop;
	// Move moveTmp {flip, flop, flop->cards.back(), 1};
	Card c;
	switch(cmd->type){
		case(createG_CMD):
			createGame(session);
			break;
		case(show_CMD):
			// DEBUG
			// std::cout << "Current Game is: " << session->currentGame << "\n";
			if (session->currentGame != -1)
				session->slot[session->currentGame]->showGame();
			break;
		case(switchG_CMD):
			num = std::stoi(cmd->args.front());
			if (session->openSlot[num] != false)
				session->currentGame = num;
			break;
		case(quitG_CMD):
			session->openSlot[session->currentGame] = false;
			delete session->slot[session->currentGame];
			// TODO prvy volny slot , ak nie je volny vratis sa spat
			break;
		case(save_CMD):
			break;
		case(load_CMD):
			break;
		case(quit_CMD):
			for(int i = 0; i < 4; ++i){
				if (session->openSlot[i] == true){
					printMove(session->slot[i]->history);
					clearHistory(session->slot[session->currentGame]->history);
					delete session->slot[i];
				}
			}
			delete(cmd);
			exit(0);
			break;
		case(popQueueDeck_CMD):
			session->slot[session->currentGame]->flip->dequeue(session->slot
												[session->currentGame]->flop);
			break;
		case(moveCard_CMD):
			// TODO moveCard(where, what)
			// cislo deku a karta
			if (cmd->args.size() > 1){
				for (unsigned i = 0; i < cmd->args.size(); ++i)
					std::cout << cmd->args[i] << "\n";
				c = getCard(cmd->args[1]);
				// session->slot[session->currentGame]->args[0].moveCards(c);
			}
			break;
		case(undo_CMD):
			printMove(session->slot[session->currentGame]->history);
			break;
		default:
			std::cout << "Command '" << cmdBuffer << "' is not valid!\n";
			break;
	}

	delete(cmd);

	return 0;
}

int createGame(session_t *session){
	Game* newGame = new Game();
	int pos;
	if( (pos = session->addGame(newGame)) < 0){
		return -1;
	}
	session->currentGame = pos;
	std::cout << "createGame"
			  << std::endl
			  << "Game created and added to slot:"
			  << pos
			  << "!."
			  << std::endl;
	return 0;
}