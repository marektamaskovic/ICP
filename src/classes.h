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

enum Symbol{A=1,J=11,Q,K};
enum Color{heart,spade,diamond,club};

enum Position{flipDeck=1, flopDeck, starterDeck, finalDeck};
enum Permissions{insert=1, get, insert_get};
// TODO Doxygen

class Card;
class Game;
class Deck;

typedef struct {
	Deck *from;
	Deck *to;
	Card &card;
	unsigned numberOfCards; // successor
}Move;

class Card final{
public:
	bool operator==(const Card&);
	int number;
	Color color;
	bool visible;
	int deck = 0;
	unsigned deckPos = 0;

	Card();
	Card(int ,Color, int, int);
	void printCard();
	void changeVisibility();
};

class Game {
// friend class Deck;
public:
	std::vector<Move> history;
	std::vector<Card> mainDeck;
	Deck *decks [7];
	Deck *finalDecks [4];
	Deck *flip;
	Deck *flop;
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

class Deck final{
private:
	int checkValidity(Card &card);
public:
	std::vector<Card> cards;
	Position position;
	Permissions permissions;

	Deck();
	Deck(Permissions, Position);
	Deck(const Deck&);
	inline void insertCard(Card &);
	/* deck to deck change, vect cards, position, checkValidity() */
	int moveCards(Deck *, Card &);
	Move* hint(Deck *, Card &);
	/* decorator fnc */
	inline Card& getLastCard();
	void printDeck();
	int dequeue(Deck *);
};

// random generator function:
static inline int myrandom (int i) { return std::rand()%i;}
bool cardCondition(Deck *, Card &);
void printMove(std::vector<Move>);

#endif
// class Move {
// private:
// 	Deck *deck;
// public:
// 	void execute(){
// 		(deck->*method)();
// 	}
// };