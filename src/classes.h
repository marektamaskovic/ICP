/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */

#ifndef CLASSES
#define CLASSES

#include <vector>		// vector primitives
#include <algorithm>	// std::shuffle
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "core.h"

enum Symbol{A=1,J=11,Q,K,undef};
enum Color{Heart,Spade,Diamond,Club};

enum Position{stack=1, waste, pileau, foundation};
enum Permissions{insert=1, get, insert_get};
// TODO Doxygen
extern int count_cards_end_game;


class Card;
class Game;
class Deck;
class ICommand;

typedef struct {
	int from;
	int to;
	Card *card;
	bool turnedUp;
}Move;

class Card final{
private:
	void printColor(std::string);
	void printColor(int);
public:
	bool operator==(const Card&);
	int number;
	Color color;
	bool visible;

	Card();
	Card(const Card &);
	Card(int ,Color);
	Card(int ,Color, bool);
	void printCard();
	inline void changeVisibility(){
		this->visible = !this->visible;
		if (this->visible == true) { ++count_cards_end_game; }
		else { --count_cards_end_game; }
	};
};

class Game {
// friend class Deck;
/* 11 = flop deck
 * 12 = flip deck
 * 0-3 finalDecks
 * 4-10 for starterDecks
 */
public:
	std::vector<Move> history;
	std::vector<Card> mainDeck;
	Deck *decks [13];
	int m = 0;

	Game();
	Game(const Game &G);
	Game& operator=(const Game &G);
	~Game();
	/* FILE */
	void showGame();
	Move* hint();
	static inline int numberOfGames(){ return current_count; }
	static int current_count;
private:
	int id = 0;
	int position = 0;
};

class Deck{
private:
	void pushCardVector(std::vector<Card>);
public:
	int deck = 0;
	// ASK preco tu nieje ukazatel?
	std::vector<Card> cards;
	Position position;
	Permissions permissions;

	Deck();
	Deck(Permissions, Position, int);
	Deck(const Deck&);
	int moveCards(std::vector<Card> );
	inline Card& getLastCard();
	void printDeck();
	int dequeue(Deck *);
	int checkValidity(Card &card);
	inline void insertCard(Card &card){ this->cards.push_back(card); }
};


// random generator function:
static inline int myrandom (int i) { return std::rand()%i;}
bool cardCondition(Card &, Card &);
void printMove(std::vector<Move>);
void clearHistory(std::vector<Move>);
std::vector<Card> parseCard(std::string, int *);
Deck *parseDeck(std::string);
Card *checkNext(Card &, Card *);
std::vector<Move> undo(std::vector<Move>);
void finishGame();

#endif
