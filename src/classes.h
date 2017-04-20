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

enum Position{flipDeck=1, flopDeck, starterDeck, finalDeck};
enum Permissions{insert=1, get, insert_get};
// TODO Doxygen

class Card;
class Game;
class Deck;
class ICommand;

typedef struct {
	int from;
	int to;
	Card *card;
	unsigned numberOfCards; // successor
}Move;

/* Interface for Command pattern */
class ICommand{
// int a;
// public:
	// virtual void executePopQD() =0;
	// virtual void executeMoveCards() =0;
	// virtual void undo() =0;
};

class Card final{
private:
	void printColor(std::string);
	void printColor(int);
public:
	bool operator==(const Card&);
	int number;
	Color color;
	bool visible;
	// unsigned deckPos = 0;

	Card();
	Card(const Card &);
	Card(int ,Color);
	void printCard();
	void changeVisibility();
};

class Game {
// friend class Deck;
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
	int save();
	int load();
	void showGame();
	static inline int numberOfGames(){ return current_count; }
	static int current_count;
private:
	int id = 0;
	int position = 0;
};

class Deck: ICommand{
private:
	int checkValidity(Card &card);
	void pushCardVector(std::vector<Card>);
public:
	int deck = 0;
	std::vector<Card> cards;
	Position position;
	Permissions permissions;

	Deck();
	Deck(Permissions, Position, int);
	Deck(const Deck&);
	inline void insertCard(Card &);
	int moveCards(std::vector<Card> );
	Move* hint(Deck *, Card &);
	inline Card& getLastCard();
	void printDeck();
	int dequeue(Deck *);

	/* Command pattern */
	// void executePopQD();
	// void executeMoveCards();
	//  reverzne operacie k MoveCards a PopQD podla presunu
	// void undo();
};


// random generator function:
static inline int myrandom (int i) { return std::rand()%i;}
bool cardCondition(Card &, Card &);
void printMove(std::vector<Move>);
void clearHistory(std::vector<Move>);
std::vector<Card> parseCard(std::string, int *);
Deck *parseDeck(std::string);
Card *checkNext(Card &, Card &);

#endif
