#include "classes.h"
#include "core.h"

Card::Card(): 	number(0),
				color(heart),
				visible(false),
				successor(nullptr){}

Card::Card(int num, Color clr): number(num),
								color(clr),
								visible(true),
								successor(nullptr){}

void Card::printCard(){
	switch(this->color){
	case 0:
		std::cout << this->number << "H" << "\n";
		break;
	case 1:
		std::cout << this->number << "S" << "\n";
		break;
	case 2:
		std::cout << this->number << "D" << "\n";
		break;
	case 3:
		std::cout << this->number << "C" << "\n";
		break;
	}
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

Deck::~Deck(){
	for (unsigned i = 0; i < this->cards.size(); i++){
		this->cards[i].successor = nullptr;
	}
}

int Deck::insertCards(Card &card){
	//FIXME card iterator or array of cards , inserts only 1 card !!!
	// inserts array of cards or a reference to a card
	if (this->cards.empty() == true)
		this->cards.insert(this->cards.begin(), card);
	else
		this->cards.insert(this->cards.begin(), card);
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

void Deck::printDeck(){
	std::cout << "Deck {\n";
	for (unsigned i = 0; i < this->cards.size(); i++){
		this->cards[i].printCard();
	}
	std::cout << "\n}";
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


Game::Game() : mainDeck(){
	current_count++;
	id = current_count;
	position = getPosition();
	Color clr;
	for (int i =0; i < 4; i++){
		clr = static_cast<Color> (i);
		for (int j = 1; j < 14; j++){
			Card card (Card(j,clr));
			mainDeck.push_back(card);
		}
	}
	/* Game will create all decks at first not filled with cards */
	//shuffling cards
	std::srand ( unsigned ( std::time(0) ) );
	std::random_shuffle(mainDeck.begin(), mainDeck.end(), myrandom);

	Deck flip (get, flipDeck);
	Deck flop (get, flopDeck);

	Deck starter[7] = { Deck(insert_get,starterDeck),
	Deck(insert_get,starterDeck), Deck(insert_get,starterDeck),
	Deck(insert_get,starterDeck), Deck(insert_get,starterDeck),
	Deck(insert_get,starterDeck), Deck(insert_get,starterDeck)};

	// final decks are empty as well as flop deck
	Deck final[4] = { Deck(insert_get, finalDeck), Deck(insert_get, finalDeck),
					Deck(insert_get, finalDeck), Deck(insert_get, finalDeck)};

	for (int j = 0; j < 7; j++){
		for (int i = 0; i <= j; i++){
			starter[j].insertCards(mainDeck.front());
			// successor fill
			// filled from 0 to size successored
			Card tmp = starter[j].cards.back();
			for (unsigned k = 0 ; k < starter[j].cards.size(); k++){
				// DEBUG
				// std::cout << "tmp is : ";
				// tmp.printCard();
				// std::cout << " *it is : ";
				// starter[j].cards[k].printCard();
				// std::cout << "\n";

				// same card
				if (tmp == starter[j].cards[k]){
					tmp.printCard();
					starter[j].cards[k].changeVisibility();
					break;
				}
				tmp.successor = &(starter[j].cards[k]);
				tmp = starter[j].cards[k];
			}
			mainDeck.erase(mainDeck.begin());
			// DEBUG
			// starter[j].cards.front().printCard();
			// std::cout << i << " j: " << j << "\n";
		}
		// DEBUG
		// std::cout << "deck number: " << j << "\n";
	}
	// shuffle one more time to get more random shuffeled cards
	std::random_shuffle(mainDeck.begin(), mainDeck.end(), myrandom);
	for (unsigned i = 0; i < mainDeck.size(); i++){
		flip.insertCards(mainDeck.front());
		mainDeck.erase(mainDeck.begin());
	}
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

