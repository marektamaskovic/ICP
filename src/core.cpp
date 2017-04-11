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

#define searchWRegex(rn, r, e)								\
do{															\
	std::regex rn ##_regex(r, std::regex::grep);			\
	if(std::regex_match(cmdBuffer, rn ##_regex) > 0){		\
		cmd->type = e;										\
		return cmd;											\
	}														\
}while(0)													\


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

	std::string::size_type n,l;
	std::string arg_buff = "";

	n = cmdBuffer.find_first_of("(");
	l = cmdBuffer.find_first_of(")");

	n++;

	if( (n-l) > 1){
		arg_buff = cmdBuffer.substr(n, l-n);

		std::regex words_regex("[^,\\ ]+");
		auto words_begin =
			std::sregex_iterator(arg_buff.begin(), arg_buff.end(), words_regex);
		auto words_end = std::sregex_iterator();

		std::cout << "Found "
			  << std::distance(words_begin, words_end)
			  << " words:\n";

		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			std::string match_str = match.str();
			cmd->args.push_back(match_str);
			std::cout << match_str << '\n';
		}

	}
	std::regex search_regex;

	searchWRegex(show,"show([A-z,\\ ]*)", show_CMD);
	searchWRegex(moveC,"moveC([A-z,\\ ]*)", moveCard_CMD);
	searchWRegex(popQD,"popQD([A-z,\\ ]*)",popQueueDeck_CMD);
	searchWRegex(switchG,"switchGame([A-z,\\ ]*)", switchG_CMD);
	searchWRegex(undo,"undo([A-z,\\ ]*)", undo_CMD);
	searchWRegex(save,"save([A-z,\\ ]*)", save_CMD);
	searchWRegex(load,"load([A-z,\\ ]*)", load_CMD);
	searchWRegex(createGame,"createGame([A-z,\\ ]*)", createG_CMD);
	searchWRegex(quit,"quit([A-z,\\ ]*)", quit_CMD);
	searchWRegex(quitGame,"quitGame([A-z,\\ ]*)", quitG_CMD);

	// This part of code is used only as reference for macro debugging!

	// std::regex show_regex("show([A-z,\\ ]*)", std::regex::grep);
	// if(std::regex_match(cmdBuffer, show_regex) > 0){
	// 	cmd->type = show_CMD;
	// 	return cmd;
	// }

	cmd->type = no_CMD;

	return cmd;
}

int resolveCmd(session_t *session, std::string &cmdBuffer){

	(void) session;

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
			exit(0);
			break;
		case(popQueueDeck_CMD):
			session->slot[session->currentGame]->flip->dequeue(session->slot
												[session->currentGame]->flop);
			break;
		case(moveCard_CMD):
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