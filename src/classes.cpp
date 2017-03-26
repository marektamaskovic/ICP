#include "classes.h"
#include "core.h"

Card::Card(int num, Color clr): number(num),
								color(clr),
								visible(true),
								successor(nullptr){}

int Card::changeVisibility(void){
	this->visible = !this->visible;
	return 0;
}

Deck::Deck(Permissions perm, Position pos):	cards(),
											position(pos),
											permissions(perm){}

Deck::~Deck(){
	for (unsigned i = 0; i < this->cards.size(); i++){
		this->cards[i].successor = nullptr;
	}
}

int Deck::insertCards(Card *card){
	//FIXME card iterator or array of cards , inserts only 1 card !!!
	// inserts array of cards or a reference to a card
	if (this->cards.empty() == true)
		this->cards.insert(this->cards.begin(), *card);
	else
		this->cards.push_back(*card);
	return 0;
}

/* check validity between two decks */
int Deck::checkValidity(Deck *other){
	if (this->permissions == insert){
		//TODO 3 == club
		if 	(this->cards.front().number == (other->cards.front().number - 1) &&
			(this->cards.front().color != other->cards.front().color &&
			this->cards.front().color == 3) )
			return 0;
		// other->insertCards( &(this->cards.front()) );
	}
	else if (this->permissions == get){
		// just flip to flop deck
		;
	}
	//insert_get
	else{
		// 4 final decks
		;
	}
	return -1;
}

std::vector<Card> Deck::getCards(Card *card){
	std::vector<Card> cards;
	if (this->cards.empty() != true){
		cards.push_back(*card);
		while(card->successor != nullptr){
			card=card->successor;
			cards.push_back(*card);
		}
	}
	return cards;
}

Card &Deck::getLastCard(){
	//decorator ?
	return this->cards.back();
}

/* TODO need all decks to match in between them */
Move* Deck::hint(Deck *other){
	Move *help = nullptr;
	if (checkValidity(other) == 0){
		help->from = this;
		help->to = other;
		help->card = this->cards.front();
		unsigned i = 0;
		while (i < this->cards.size()){ i++; }
		help->numberOfCards = i;
	}
	return help;
}

int Game::current_count = 0;


Game::Game(){
	current_count++;
	id = current_count;
	position = getPosition();
	// create cards and shuffle at least twice (for && for)
}

Game::~Game(){
	current_count--;
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

