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
/* TODO documentation */
Card::Card(): 	number(0),
				color(heart),
				visible(false),
				deck(0),
				deckPos(0){}

Card::Card(int num, Color clr, int d, int dPos): 	number(num),
													color(clr),
													visible(false),
													deck(d),
													deckPos(dPos){}

void Card::printCard(){
	// DEBUG
	// std::cout << this->deck << ": ";
	// std::cout << this->deckPos << ": ";
	if (this->visible == true){
		switch(this->color){
		case 0:
			std::cout << BOLDRED << this->number << "H" << RESET << ",\t";
			break;
		case 1:
			std::cout << BOLDBLACK << this->number << "S" << RESET << ",\t";
			break;
		case 2:
			std::cout << BOLDRED << this->number << "D" << RESET << ",\t";
			break;
		case 3:
			std::cout << BOLDBLACK << this->number << "C" << RESET << ",\t";
			break;
		}
	}
	else
		std::cout << "( # ),\t";
}

void Card::changeVisibility(){
	this->visible = !this->visible;
}

bool Card::operator==(const Card &rCard){
	return this->number == rCard.number && this->color == rCard.color;
}

Deck::Deck(): 	cards(),
				position(starterDeck),
				permissions(insert_get){}

Deck::Deck(Permissions perm, Position pos):	cards(),
											position(pos),
											permissions(perm){}

Deck::Deck(const Deck &d): 	cards{d.cards},
							position{d.position},
							permissions{d.permissions}{}

void Deck::insertCard(Card &card){
	this->cards.push_back(card);
}

/* check validity between two decks */
/* FIXME we need other deck what if not enough permissions? */
int Deck::checkValidity(Card &card){
	if ( this->permissions == insert_get && card.visible == true){
		// moving card to this , function to compare used
		if (this->position == starterDeck){
			if (cardCondition(this, card) == true){
				return 0;
			}
		}
		// every final deck has exactly 1 color and numbered from 1 to 13
		else if (this->position == finalDeck){
			if (this->cards.empty() && card.number == 1){
				this->insertCard(card);
				return 0;
			}
			else if ((card.number - 1) == this->cards.front().number){
				if (card.color == this->cards.front().color){
					this->insertCard(card);
					if(card.deck < 7){
						Deck *tmp = currentSession.slot[currentSession.currentGame]->decks[card.deck];
						tmp->cards.erase(tmp->cards.begin());
					}
					return 0;
				}
			}
		}
	}
	return -1;
}

int Deck::moveCards(Deck *other, Card &card){
	(void) other;
	card.printCard();
	// TDO refecotor!
	// if (cardCondition(this, other) == true)
		// other->insertCards( (this->cards.front()) );
	return 0;
}

Card &Deck::getLastCard(){
	return this->cards.back();
}

int Deck::dequeue(Deck *other){
	if (this->permissions == insert && other->permissions == get){
		/* flip to flop deck */
		if (this->cards.empty()){
			currentSession.slot[currentSession.currentGame]->
				history.push_back({this, other, other->cards.back(), 1});

			for (unsigned i = 0; i != other->cards.size();){
				// Again from start
				other->cards.front().changeVisibility();
				this->cards.push_back(std::move(other->cards.front()));
				other->cards.erase(other->cards.begin());
			}

			return 0;
		}
		else{

			other->cards.push_back(std::move(this->cards.front()));
			// to flop, change visibility
			other->cards.back().changeVisibility();
			this->cards.erase(this->cards.begin());
			other->cards.back().deck = 11;

			currentSession.slot[currentSession.currentGame]->
				history.push_back({this, other, other->cards.back(), 1});

			return 0;
		}
	}
	return -1;
}

void Deck::printDeck(){
	if (this->permissions == insert || this->permissions == get){
		std::cout << "Deck {\t";
		for (unsigned i = 0; i < this->cards.size(); i++)
			this->cards[i].printCard();
		// if (this->cards.size() > 0)
		// 	this->cards[this->cards.size()-1].printCard();
		std::cout << "\b\b  \b\b\t}\n";
	}
	else{
		std::cout << "Deck: ";
		for (unsigned i = 0; i < this->cards.size(); i++){
			this->cards[i].printCard();
		}
		std::cout << "\b \b\n";
	}
}

/* TODO need all decks to match in between them , maybe global Decks ?!?*/
Move* Deck::hint(Deck *other, Card &card){
	if(other != nullptr){
		Move *help = nullptr;
		if (checkValidity(card) == 0){
			help->from = this;
			help->to = other;
			help->card = this->cards.front();
			unsigned i = 0;
			while (i < this->cards.size()){ i++; }
			help->numberOfCards = i;
		}
		return help;
	}
	else{
		return nullptr;
	}
}

int Game::current_count = 0;
/* TODO documentation */
Game::Game(	const Game &G) : history(), mainDeck(), decks(), finalDecks(),
			flip(), flop(){
	for(int i = 0; i < 7; i++){
		decks[i] = G.decks[i];
	}

	for(int i = 0; i < 4; i++){
		finalDecks[i] = G.finalDecks[i];
	}
	flip = G.flip;
	flop = G.flop;
}
/* TODO documentation */
Game& Game::operator=(const Game &G){

	if (this != &G) { // self-assignment check expected


		std::copy(G.history.begin(), G.history.end(),
              std::back_inserter(this->history));

		std::copy(G.mainDeck.begin(), G.mainDeck.end(),
              std::back_inserter(this->mainDeck));

		for(int i = 0; i < 7; i++){
			this->decks[i] = G.decks[i];
		}

		for(int i = 0; i < 4; i++){
			this->finalDecks[i] = G.finalDecks[i];
		}
		this->flip = G.flip;
		this->flop = G.flop;
    }
    return *this;


}
/* TODO documentation */
Game::Game() :  history(), mainDeck(), decks(), finalDecks(), flip(), flop(){
	current_count++;
	id = current_count;
	position = getPosition();
	Color clr;
	for (int i =0; i < 4; i++){
		clr = static_cast<Color> (i);
		for (int j = 1; j < 14; j++){
			Card card (Card(j, clr, 0, 0));
			mainDeck.push_back(card);
		}
	}
	/* Game will create all decks at first not filled with cards */
	//shuffling cards
	std::srand ( unsigned ( std::time(0) ) );
	std::random_shuffle(mainDeck.begin(), mainDeck.end(), myrandom);

	flip = new Deck (insert, flipDeck);
	flop = new Deck (get, flopDeck);

	for(int i = 0; i < 7; i++){
		decks[i] = new Deck(insert_get,starterDeck);
	}

	for(int i = 0; i < 4; i++){
		finalDecks[i] = new Deck(insert_get,starterDeck);
	}

	// shuffle one more time to get more random shuffeled cards
	std::random_shuffle(mainDeck.begin(), mainDeck.end(), myrandom);
	for (int j = 0; j < 7; j++){

		for (int i = 0; i <= j; i++){
			mainDeck.front().deckPos = 6-j;
			mainDeck.front().deck = i;
			if (i == j){
				mainDeck.front().changeVisibility();
			}

			decks[i]->insertCard(mainDeck.front());
			mainDeck.erase(mainDeck.begin());
		}
	}

	for (unsigned i = 0; i != mainDeck.size();){
		// mainDeck.front().deckPos = i;
		mainDeck.front().deck = 10;
		this->flip->insertCard(mainDeck.back());
		mainDeck.erase(mainDeck.end());
	}

	showGame();
}

Game::~Game(){
	current_count--;

	for(int i = 0; i < 7; i++){
		delete(this->decks[i]);
	}

	for(int i = 0; i < 4; i++){
		delete(this->finalDecks[i]);
	}
	delete(this->flip);
	delete(this->flop);
}

/* TODO add JSON library, convert - history deck id position - into json saved
 * loaded format check for permissions and some other stuff get the correct way
 * of saving  loading methods of Game class */
int Game::save(){
	return 0;
}

int Game::load(){
	return 0;
}

void Game::showGame(){
	this->flip->printDeck();
	this->flop->printDeck();
	for (int i = 0; i < 7; ++i){
		this->decks[i]->printDeck();
	}
	for (int i = 0; i < 4; ++i)
		this->finalDecks[i]->printDeck();
}


bool cardCondition(Deck *first, Card &card){
	if (first->cards.front().number ==
		(card.number - 1)){

		if((first->cards.front().color == club ||
			first->cards.front().color == heart) &&
			(card.color == spade ||
			card.color == diamond)){
			return true;
		}
		else if ((first->cards.front().color == spade ||
				first->cards.front().color == diamond) &&
				(card.color == club ||
				card.color == heart)){
			return true;
		}
	}
	return false;
}

void printMove(std::vector<Move> mov){
	std::cout << "Move:\n";
	// mov.front().from->printDeck();
	// mov.front().to->printDeck();
	// std::cout << "number of cards:" << mov.front().numberOfCards << "\n";

	for (unsigned i = 0; i < mov.size(); ++i){
		mov[i].from->printDeck();
		mov[i].to->printDeck();
		mov[i].card.printCard();
		std::cout << "number of cards: " << i << "\n";
	}
	std::cout << "End\n";
}