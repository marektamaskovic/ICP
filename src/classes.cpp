/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */

#include "classes.h"
#include "core.h"
#include "color.h"

extern session_t currentSession;


Card::Card(): 	number(0),
				color(Heart),
				visible(false){}

Card::Card(int num, Color clr):	number(num),
								color(clr),
								visible(false){}

Card::Card(int num, Color clr, bool vis):	number(num),
											color(clr),
											visible(vis){}

Card::Card(const Card &c): 	number(c.number),
							color(c.color),
							visible(c.visible){}

void Card::printColor(int num){
	switch(this->color){
	case 0:
		std::cout << BOLDRED << num << " H" << RESET << ",  ";
		break;
	case 1:
		std::cout << BOLDBLACK << num << " S" << RESET << ",  ";
		break;
	case 2:
		std::cout << BOLDRED << num << " D" << RESET << ",  ";
		break;
	case 3:
		std::cout << BOLDBLACK << num << " C" << RESET << ",  ";
		break;
	}
}

void Card::printColor(std::string str){
	switch(this->color){
	case 0:
		std::cout << BOLDRED << str << " H" << RESET << ",  ";
		break;
	case 1:
		std::cout << BOLDBLACK << str << " S" << RESET << ",  ";
		break;
	case 2:
		std::cout << BOLDRED << str << " D" << RESET << ",  ";
		break;
	case 3:
		std::cout << BOLDBLACK << str << " C" << RESET << ",  ";
		break;
	}
}

void Card::printCard(){
	Symbol sym;
	std::string tmp;
	if (this->visible == true){
		switch(this->number){
		case 1:
			sym = A;
			tmp = "A";
			break;
		case 11:
			sym = J;
			tmp = "J";
			break;
		case 12:
			sym = Q;
			tmp = "Q";
			break;
		case 13:
			sym = K;
			tmp = "K";
			break;
		default:
			sym = undef;
		}
		if (sym != undef){
			this->printColor(tmp);
		}
		else
			this->printColor(this->number);
	}
	else
		std::cout << "( # ),  ";
}

void Card::changeVisibility(){
	this->visible = !this->visible;
	if (this->visible == true) {
		currentSession.slot[currentSession.currentGame]->count_cards_end_game++;
	}
	else {
		currentSession.slot[currentSession.currentGame]->count_cards_end_game--;
	}
}


bool Card::operator==(const Card &rCard){
	return this->number == rCard.number && this->color == rCard.color;
}

Deck::Deck(): 	deck(0),
				cards(),
				position(pileau),
				permissions(insert_get){}

Deck::Deck(Permissions perm, Position pos, int num): deck(num),
													 cards(),
													 position(pos),
													 permissions(perm){}

Deck::Deck(const Deck &d): 	deck(d.deck),
							cards{d.cards},
							position{d.position},
							permissions{d.permissions}{}

/* check validity between two decks */
int Deck::checkValidity(Card &card){
	if ( this->permissions == insert_get && card.visible == true){
		// moving card to this , function to compare used
		if (this->position == pileau){
			// King should be pushed if number is 13 and no card on pileau
			if (this->cards.size() == 0){
				if(card.number == 13){
					return 0;
				}
			}
			else{
				if (this->cards.back().visible == false ||
					this->cards.back() == card)
					return -1;
				if (cardCondition(this->cards.back(), card) == true){
					return 0;
				}
			}
		}
		// every final deck has exactly 1 color and numbered from 1 to 13
		else if (this->position == foundation){
			if (this->cards.empty()){
				if (card.number == 1){
					return 0;
				}
				else
					return-1;
			}
			else if ((card.number - 1) == this->cards.back().number){
				if (card.color == this->cards.back().color){
					return 0;
				}
			}
		}
	}

	return -1;
}

void Deck::pushCardVector(std::vector<Card> vect){
	for (unsigned i = 0; i != vect.size();){
		this->insertCard(vect.front());
		vect.erase(vect.begin());
	}
}

int Deck::moveCards(std::vector<Card> vect){
	int result = -1;
	if (vect.size() != 0){
		if (this->position == 4){
			if (vect.size() > 1)
				return -1;
		}
		result = this->checkValidity(vect.front());
		if (result == 0){
			this->pushCardVector(vect);
		}
	}
	return result;
}

Card &Deck::getLastCard(){
	return this->cards.back();
}

int Deck::dequeue(Deck *other){
	if (this->permissions == insert && other->permissions == get){
		/* flip to flop deck */
		if (this->cards.empty()){
			Card *c = new Card(other->cards.back());
			currentSession.slot[currentSession.currentGame]->
				history.push_back({11, 12, c, true});

			if (other->cards.size() != 0)
				other->cards.back().changeVisibility();
			for (unsigned i = 0; i != other->cards.size();){
				this->cards.push_back(other->cards.back());
				other->cards.pop_back();
			}

			return 0;
		}
		else{
			this->cards.back().changeVisibility();

			other->cards.push_back(this->cards.back());
			if (other->cards.size() > 1){
				other->cards[other->cards.size()-2].changeVisibility();
			}
			this->cards.pop_back();

			Card *c = new Card(other->cards.back());
			currentSession.slot[currentSession.currentGame]->
				history.push_back({12, 11, c, true});

			return 0;
		}
	}
	return -1;
}

void Deck::printDeck(){
	std::cout << this->deck << " ";
	if (this->permissions == insert || this->permissions == get){
		std::cout << "Deck {  ";
		if (this->cards.size() > 0)
			this->cards[this->cards.size()-1].printCard();
		std::cout << "}\n";
	}
	else{
		std::cout << "Deck {  ";
		for (unsigned i = 0; i < this->cards.size(); i++){
			this->cards[i].printCard();
		}
		std::cout << "\b\b\b}\n";
	}
}

/***************************************************/
/************ Game class implementation ************/
/***************************************************/
int Game::current_count = 0;

Game::Game(	const Game &G) : history(), mainDeck(), decks(){
	for(int i = 0; i < 13; i++){
		decks[i] = G.decks[i];
	}
}

Game& Game::operator=(const Game &G){
	if (this != &G) { // self-assignment check expected
		std::copy(G.history.begin(), G.history.end(),
			std::back_inserter(this->history));

		std::copy(G.mainDeck.begin(), G.mainDeck.end(),
			std::back_inserter(this->mainDeck));

		for(int i = 0; i < 13; i++){
			this->decks[i] = G.decks[i];
		}
	}
	return *this;
}

Game::Game() :  history(), mainDeck(), decks(){
	current_count++;
	id = current_count;
	position = getPosition();
}

Game::~Game(){
	current_count--;
	for(int i = 0; i < 13; i++){
		delete(this->decks[i]);
	}
}

void Game::showGame(){
	for (int i = 12; i != -1; --i){
		if (i == 10 || i == 3)
			std::cout << "\n";
		this->decks[i]->printDeck();
	}
}

Move* Game::hint(){
	Card cardFrom;
	int result;
	Move *hintMove = nullptr;

	for (int i = 0; i < 12; ++i){
		// is there any card?
		if (!this->decks[i]->cards.empty())
			cardFrom = this->decks[i]->cards.back();
		else
			continue;
		// is card valid? , iterate trough vector
		if (cardFrom.number == 0 || cardFrom.visible == false)
			continue;
		for (std::vector<Card>::iterator it = this->decks[i]->cards.end();
			it != this->decks[i]->cards.begin(); --it){
			if ((*it).visible == false)
				continue;
			for (int j = 0;j < 12;++j){
				result = this->decks[j]->checkValidity(*it);
				if (result == 0){
					Card *store = new Card(*it);
					hintMove = new Move({i,j,store,false});
					break;
				}
			}

		}

		if (hintMove != nullptr)
			return hintMove;
	}

	if (this->decks[12]->cards.empty()){
		if (this->decks[11]->cards.empty())
			return hintMove;
		hintMove = new Move({12,11,nullptr,false});
	}
	return hintMove;
}

/* Functions which helps to parse cards, checks conditions, working with
 *history and undo implementation */
bool cardCondition(Card &other, Card &card){
	if (card.number ==
		(other.number - 1)){

		if((other.color == Heart ||
			other.color == Diamond) &&
			(card.color == Spade ||
			card.color == Club)){
			return true;
		}
		else if ((other.color == Spade ||
				other.color == Club) &&
				(card.color == Diamond ||
				card.color == Heart)){
			return true;
		}
	}
	return false;
}

void printMove(std::vector<Move> mov){
	std::cout << "Move:\n\n";

	std::string from = "";
	std::string to = "";
	for (unsigned i = 0; i < mov.size(); ++i){
		if (mov[i].from == 12)
			from = "From - stack: ";
		if (mov[i].to == 12)
			to = "To - stack: ";
		if (mov[i].from == 11)
			from = "From - waste: ";
		if (mov[i].to == 11)
			to = "To - waste";

		if (mov[i].from < 10 && mov[i].from > 3)
			from = "From - pileau: ";
		if (mov[i].to < 10 && mov[i].to > 3)
			to = "To - pileau: ";
		if (mov[i].from < 3)
			from = "From - foundation: ";
		if (mov[i].to < 3)
			to = "To - foundation: ";

		std::cout << from << "\n";
		std::cout << to << "\n";
		mov[i].card->printCard();
		std::cout << "turnUp: " << mov[i].turnedUp;
		std::cout << "\n\n";
	}
	std::cout << "End\n";
}

void clearHistory(std::vector<Move> mv){
	for(unsigned i = 0; i < mv.size(); ++i){
		delete mv[i].card;
	}
}

std::vector<Card> parseCard(std::string str, int *deckNumber){
	int num = 0;
	int check;

	std::vector<Card> vect;
	if (str[str.length() - 1] == ')'){
		str.erase(str.length() - 1);
	}
	check = sscanf(str.c_str(),"%d",&num);
	if (check != 1){
		if (str.find("A") != std::string::npos){
			str.erase(str.begin());
			num = 1;
		}
		else if (str.find("J") != std::string::npos)
			num = 11;
		else if (str.find("Q") != std::string::npos)
			num = 12;
		else if (str.find("K") != std::string::npos)
			num = 13;
		else
			return vect;
	}
	std::string tmp = std::to_string(num);
	std::size_t pos = str.find(tmp);

	Color clr = Heart;
	str = str.substr(pos + tmp.length());
	int tmpNum = str[0];
	Card *c = nullptr;
	switch (tmpNum){
	case 'H':
		clr = Heart;
		break;
	case 'S':
		clr = Spade;
		break;
	case 'D':
		clr = Diamond;
		break;
	case 'C':
		clr = Club;
		break;
	default:
		return vect;
		break;
	}
	if (!(num >= 1 && num <= 13)){
		std::cerr << "number : " << num << "\n";
		return vect;
	}
	c = new Card(num, clr, true);
	int curr = currentSession.currentGame;
	Card tmpCard;
	bool found = false;

	for (int i = 0; i < 12; ++i){
		for (unsigned j = 0; j < currentSession.slot[curr]->decks[i]->cards.size(); ++j){
			tmpCard = currentSession.slot[curr]->decks[i]->cards[j];

			if (found == false){
				if (tmpCard.visible == true && tmpCard == *c){
					*deckNumber = i;
					found = true;
					vect.push_back(*c);
				}
			}
			else{

				if (tmpCard.visible == false){
					found = true;
					break;
				}
				if (i != 11){
					c = checkNext(tmpCard,c);
					if (c != nullptr){
						vect.push_back(*c);
					}
					else{
						vect.clear();
						return vect;
					}
				}
			}
		}
		if (found == true)
			break;
	}

	delete(c);
	return vect;
}

Deck *parseDeck(std::string str){
	int num = std::stoi(str);
	Deck *deck = nullptr;
	int curr = currentSession.currentGame;

	if(num > -1 && num < 13)
		deck = currentSession.slot[curr]->decks[num];
	return deck;
}


Card *checkNext(Card &other, Card *main){
	bool ret = false;

	if (*main == other){
		return main;
	}

	ret = cardCondition(*main,other);
	if (ret == true){
		delete(main);
		Card *newCard = new Card(other);
		return newCard;
	}
	delete(main);
	return nullptr;
}

std::vector<Move> undo(std::vector<Move> moveSession){

	if (moveSession.size() != 0){
		int curr = currentSession.currentGame;
		int from = moveSession.back().from;
		int to = moveSession.back().to;
		int deckNumber = currentSession.slot[curr]->decks[from]->deck;
		std::vector<Card>::iterator it;

		/*******************************************/
		/* PopQD command reverse from flop to flip */
		/*******************************************/
		if (deckNumber == 12){
			it = currentSession.slot[curr]->decks[from]->cards.begin();

			if (moveSession.back().turnedUp == true)
				moveSession.back().card->changeVisibility();
			currentSession.slot[curr]->decks[from]->cards.
				insert(it, *(moveSession.back().card));

			it = currentSession.slot[curr]->decks[to]->cards.end();

			currentSession.slot[curr]->decks[to]->cards.erase(it);
		}

		/******************************************************/
		// when flip was full undo whole 24 cards back to flop
		/******************************************************/
		else if (deckNumber == 11 && to == 12){
			unsigned size = currentSession.slot[curr]->decks[to]->cards.size();
			for (unsigned i = 0; i < size;++i){
				it = currentSession.slot[curr]->decks[from]->cards.end();
				currentSession.slot[curr]->decks[to]->cards[i].changeVisibility();

				currentSession.slot[curr]->decks[from]->cards.insert(it,currentSession.slot[curr]->decks[to]->cards[i]);
				currentSession.slot[curr]->decks[to]->cards.pop_back();
			}
		}

		/**************************************************/
		/* moveCmd reverse from any deck except flip deck */
		/**************************************************/
		else{
			std::vector<Card> cards;
			Card tmpCard;

			if (moveSession.back().turnedUp == false &&
			currentSession.slot[curr]->decks[from]->cards.size() != 0)
				currentSession.slot[curr]->decks[from]->cards.back().changeVisibility();

			bool found = false;
			for (unsigned i = 0; i < currentSession.slot[curr]->decks[to]->cards.size(); ++i){
				tmpCard = currentSession.slot[curr]->decks[to]->cards[i];
				if (found == false && !(tmpCard == *(moveSession.back().card)))
					continue;
				found = true;

				moveSession.back().card = checkNext(tmpCard,moveSession.back().card);
				if (moveSession.back().card != nullptr){
					cards.push_back(*(moveSession.back().card));
				}
			}
			for (unsigned i = 0; i < cards.size(); ++i){
				currentSession.slot[curr]->decks[from]->cards.push_back(cards[i]);
				currentSession.slot[curr]->decks[to]->cards.pop_back();
			}
		}
		/* erase history card and go 1 history move back */
		delete(moveSession.back().card);
		moveSession.pop_back();

	}
	return moveSession;
}

void finishGame(){
	Card finishCard, fromCard;
	int curr = currentSession.currentGame;
	int result;
	unsigned secondSize;

	for (unsigned maximumSize = 1 ; maximumSize != 0;--maximumSize){
		for (int i = 4; i < 12; ++i){
			secondSize = currentSession.slot[curr]->decks[i]->cards.size();

			maximumSize = std::max(maximumSize, secondSize);
			if (currentSession.slot[curr]->decks[i]->cards.size() != 0){
				fromCard = currentSession.slot[curr]->decks[i]->cards.back();
			}

			for(int j = 0; j < 4; ++j){
				result = currentSession.slot[curr]->decks[j]->checkValidity(fromCard);
				if (result == 0){
					currentSession.slot[curr]->decks[j]->insertCard(fromCard);
					currentSession.slot[curr]->decks[i]->cards.pop_back();
				}
			}
		}
	}
}