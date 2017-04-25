/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */


#include <iostream>

#include "core.h"
#include "color.h"
#include "save.h"

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

	char argument[42];
	int ret;
	if(cmdBuffer == "show()"){
		cmd->type = show_CMD;
	}
	else if(cmdBuffer == "popQD()"){
		cmd->type = popQueueDeck_CMD;
	}
	else if(cmdBuffer == "undo()"){
		cmd->type = undo_CMD;
	}
	else if (cmdBuffer == "hint()"){
		cmd->type = hint_CMD;
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
	// FIXME 2 variants of moveC()?!?
	else if((ret = (sscanf(cmdBuffer.c_str(),"moveC(%10s)",argument))) == 1){
		std::string tmp = argument;
		std::size_t found = tmp.find(",");

		if (found!=std::string::npos){
			strncpy(argument, tmp.substr(found+1, 3).c_str(), 6);
			argument[3] = '\0';
			tmp.erase(found);
		}

		cmd->args.push_back(tmp);
		cmd->args.push_back(argument);
		cmd->type = moveCard_CMD;
	}
	else if(sscanf(cmdBuffer.c_str(),"switchGame(%s)",argument) == 1){
		argument[std::strlen(argument)-1] = '\0';
		cmd->args.push_back(argument);
		cmd->type = switchG_CMD;
	}
	else if(sscanf(cmdBuffer.c_str(),"save(%s)",argument) == 1){
		argument[std::strlen(argument)-1] = '\0';
		cmd->args.push_back(argument);
		cmd->type = save_CMD;
	}
	else if(sscanf(cmdBuffer.c_str(),"load(%s)",argument) == 1){
		argument[std::strlen(argument)-1] = '\0';
		cmd->args.push_back(argument);
		cmd->type = load_CMD;
	}
	else
		cmd->type = no_CMD;

	return cmd;
}

int resolveCmd(session_t *session, std::string &cmdBuffer){

	command_t *cmd = parseCMD(cmdBuffer);

	std::cout << "Cmd: '"
			  << getCommandName(cmd->type)
			  << "'"
			  << std::endl;

	int num, deckNumber, historyNumber;
	std::vector<Card> vectCard;
	Card *pushCard = nullptr;
	Deck *tmpDeck = nullptr;
	Move *storeMove = nullptr;
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
			if(session->currentGame >= 0){
				save(cmd->args.front(), *session->slot[session->currentGame]);
			}
			else{
				std::cerr << "Game not selected!" << std::endl;
			}
			break;
		case(load_CMD):
			std::cout << ">" << cmd->args.front() << "<" << std::endl;
			std::cout << ">" << cmd->args.back() << "<" << std::endl;
			load_game(cmd->args.front(), session);
			// if( != 0)
				// err_msg("load failed!");
			break;
		case(quit_CMD):
			for(int i = 0; i < 4; ++i){
				if (session->openSlot[i] == true){
					clearHistory(session->slot[session->currentGame]->history);
					delete session->slot[i];
				}
			}
			delete(cmd);
			exit(0);
			break;
		case(popQueueDeck_CMD):
			session->slot[session->currentGame]->decks[12]->dequeue(session->slot[session->currentGame]->decks[11]);
			break;
		case(moveCard_CMD):
			if (cmd->args.size() > 1 && session->currentGame != -1){
				vectCard = parseCard(cmd->args[2], &deckNumber);
				if (vectCard.size() == 0)
					break;
				tmpDeck = parseDeck(cmd->args[1]);
				/* FIXME Ask for type ? Card or Deck, kinda does not matter
				 *wether we place card at card or Card to Deck.
				 */
				historyNumber = tmpDeck->deck;
				num = tmpDeck->moveCards(vectCard);
				/* Remove all cards that was swapped */
				if (num != -1){
					tmpDeck=session->slot[session->currentGame]->decks[deckNumber];
					for (unsigned j = 0; j < tmpDeck->cards.size();++j){
						if (tmpDeck->cards[j] == vectCard.back()){
							for (unsigned i = j; i < (j + vectCard.size());++i){
								tmpDeck->cards.erase(tmpDeck->cards.begin()+i);
							}
						}
					}
					// flip card
					if (tmpDeck->cards.size() != 0)
						if (tmpDeck->cards.back().visible == false)
							tmpDeck->cards.back().changeVisibility();
					pushCard = new Card(vectCard.back());
					session->slot[session->currentGame]->history.push_back({deckNumber,historyNumber,pushCard});
				}
			}
			break;
		case(undo_CMD):
			undo(session->slot[session->currentGame]->history);
			break;
		case(hint_CMD):
			storeMove = session->slot[session->currentGame]->hint();
			if (storeMove != nullptr){
				std::cout << "From: " << storeMove->from << "\n";
				std::cout << "To: " << storeMove->to << "\n";
				storeMove->card->printCard();
				delete(storeMove->card);
				delete(storeMove);
			}
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