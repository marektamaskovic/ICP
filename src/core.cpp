/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */


#include <iostream>

#include "core.h"
#include "classes.h"
#include "color.h"
#include "save.h"

extern session_t currentSession;
int	count_cards_end_game = 0;


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
	else if(cmdBuffer == "help()"){
		cmd->type = help_CMD;
	}
	// FIXME 2 variants of moveC()?!? - definitely yes, when we got enough
	// time do 2 variatnts - decknum, Cardfrom, Cardto, Cardfrom; just parser
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

	int num;
	Move *storeMove = nullptr;
	switch(cmd->type){
		case(createG_CMD):
			createGame(session);
			break;
		case(show_CMD):
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
			load_game(cmd->args.front(), session);
			break;
		case(quit_CMD):
			quitGameDeco(session);
			delete(cmd);
			exit(0);
			break;
		case(popQueueDeck_CMD):
			session->slot[session->currentGame]->decks[12]->dequeue(session->slot[session->currentGame]->decks[11]);
			break;
		case(moveCard_CMD):
            moveCardDeco(cmd);
			break;
		case(undo_CMD):
			session->slot[session->currentGame]->history = undo(session->slot[session->currentGame]->history);
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
		case(help_CMD):
			printHelpMsg();
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
        delete newGame;
		return -1;
	}

	count_cards_end_game = 0;
	Color clr;
	for (int i =0; i < 4; i++){
		clr = static_cast<Color> (i);
		for (int j = 1; j < 14; j++){
			Card card (Card(j, clr));
			newGame->mainDeck.push_back(card);
		}
	}
	/* Game will create all decks at first not filled with cards */
	std::srand ( unsigned ( std::time(0) ) );
#define SHUFFLE
#ifdef SHUFFLE
	std::random_shuffle(mainDeck.begin(), mainDeck.end(), myrandom);
#endif

	newGame->decks[12] = new Deck (insert, waste, 12);
	newGame->decks[11] = new Deck (get, stack, 11);

	for(int i = 4; i < 11; i++){
		newGame->decks[i] = new Deck(insert_get,pileau, i);
	}
	for(int i = 0; i < 4; i++){
		newGame->decks[i] = new Deck(insert_get,foundation, i);
	}

	for (int j = 4; j < 11; j++){

		for (int i = 4; i <= j; i++){
			if (i == j){
				newGame->mainDeck.front().changeVisibility();
			}

			newGame->decks[j]->insertCard(newGame->mainDeck.front());
			newGame->mainDeck.erase(newGame->mainDeck.begin());
		}
	}
	for (unsigned i = 0; i != newGame->mainDeck.size();){
		newGame->decks[12]->insertCard(newGame->mainDeck.back());
		newGame->mainDeck.erase(newGame->mainDeck.end());
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

void moveCardDeco(command_t *cmd){
	std::vector<Card> vectCard;
	int num, deckNumber , historyNumber;
	Card *pushCard = nullptr;
	Deck *tmpDeck = nullptr;

	if (cmd->args.size() > 1 && currentSession.currentGame != -1){
		vectCard = parseCard(cmd->args[1], &deckNumber);
		if (vectCard.size() == 0)
			return;
		tmpDeck = parseDeck(cmd->args[0]);
		historyNumber = tmpDeck->deck;
		num = tmpDeck->moveCards(vectCard);
		/* Remove all cards that was swapped */
		if (num != -1){
			tmpDeck=currentSession.slot[currentSession.currentGame]->decks[deckNumber];
			for (unsigned j = 0; j < tmpDeck->cards.size();++j){
				if (tmpDeck->cards[j] == vectCard.back()){
					for (unsigned i = j; i < (j + vectCard.size());++i){
						tmpDeck->cards.erase(tmpDeck->cards.begin()+i);
					}
				}
			}
			pushCard = new Card(vectCard.front());
			if (tmpDeck->cards.size() != 0){

				if (tmpDeck->cards.back().visible == false){
					currentSession.slot[currentSession.currentGame]->history.push_back({deckNumber,historyNumber,pushCard,tmpDeck->cards.back().visible});
					tmpDeck->cards.back().changeVisibility();
				}
				else
					currentSession.slot[currentSession.currentGame]->history.push_back({deckNumber,historyNumber,pushCard,tmpDeck->cards.back().visible});
			}else {
				currentSession.slot[currentSession.currentGame]->history.push_back({deckNumber,historyNumber,pushCard,true});
			}
		}
	}
}

void quitGameDeco(session_t *session){
	for(int i = 0; i < 4; ++i){
		if (session->openSlot[i] == true){
			clearHistory(session->slot[session->currentGame]->history);
			delete session->slot[i];
		}
	}
}

void printHelpMsg(){
	std::cout << "Possible commands you can use in this CLI version are: " << std::endl;

	std::cout <<  "'createGame()'" << std::setw(38) << "- no parameter. Create new game." << std::endl;
	std::cout <<  "'switchGame(num)'" << std::setw(59) << "- 1 parameter - number. To which game should CLI switch." << std::endl;
	std::cout <<  "'quitGame()'" << std::setw(42) << "- no parameter. Quits current game" << std::endl;
	std::cout <<  "'saveGame(fileName)'" << std::setw(49) << "- 1 parameter - string. Saves game in JSON format" << std::endl;
	std::cout <<  "'loadGame(fileName)'" << std::setw(51) << "- 1 parameter - string. Loads game from JSON format" << std::endl;
	std::cout <<  "'show()'" << std::setw(81) << "- no parameter. Shows current game status, prints all decks and cards" << std::endl;
	std::cout <<  "'quit()'" << std::setw(46) << "- no parameter. Quits application." << std::endl;
	std::cout <<  "'popQD()'" << std::setw(57) << "- no parameter. Pops card from stack to waste." << std::endl;
	std::cout <<  "'moveC(num,card)'" << std::setw(65) << "- 2 parameters - number and card. Card is - number and colour." << std::endl;
	std::cout << std::setw(138) <<"- colour should be - S,D,H,C. Number  is from 1 to 13 (for 1 could be also given char 'A', for 11 to 13 - 'J','Q','K')" << std::endl;
	std::cout << std::setw(56) << "- example of cards: 'AS', '9D', 'KH'" << std::endl;
	std::cout << std::setw(83) <<"- moveC moves card to deck number - deck number is from 0 to 12" << std::endl;
	std::cout << std::setw(84) << "- deck numbers - 0-3 foundation, 4-10 pileau, 11 stack, 12 waste" << std::endl;
	std::cout <<  "'undo()'" << std::setw(62) << "- no parameter - Turn back game state 1 state back" << std::endl;
	std::cout <<  "'hint()'" << std::setw(102) << "- no parameter - Prints to standard output, where you should put card if you have no clue." << std::endl;
	std::cout <<  "'help()'" << std::setw(53) << "- no parameter - Prints this long message" << std::endl;

}
