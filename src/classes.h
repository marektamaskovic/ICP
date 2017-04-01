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
	Card *successor;

	Card();
	Card(int ,Color);
	void printCard();
	void changeVisibility();
};

// random generator function:
static inline int myrandom (int i) { return std::rand()%i;}

class Game {
public:
	std::vector<Move> history [5];
	std::vector<Card> mainDeck;
	int m = 0;
	Game();
	~Game();
	/* FILE */
	int save();
	int load();
	static inline int numberOfGames(){ return current_count; }
	static int current_count;

private:
	int id = 0;
	int position = 0;
};

class Deck final{
private:
	int checkValidity(Deck *);
public:
	std::vector<Card> cards;
	Position position;
	Permissions permissions;

	Deck();
	Deck(Permissions ,Position );
	Deck(const Deck&);
	~Deck();
	/* deck to deck change, vect cards, position, checkValidity() */
	int insertCards(Card &);
	int swapCards(Deck *);
	/* using successor of Cards (Card::successor) */
	std::vector<Card> getCards(Card *);
	/* decorator fnc */
	Card& getLastCard();
	void printDeck();
	Move* hint(Deck *);
};
bool cardCondition(Deck *, Deck *);


#endif
// class Move {
// private:
// 	Deck *deck;
// public:
// 	void execute(){
// 		(deck->*method)();
// 	}
// };