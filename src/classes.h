/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */

#ifndef CLASSES
#define CLASSES

#include <vector>
#include "core.h"

//enum symbol{A=1,J=11,Q,K};
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
	enum Color{heart,spade,diamond,club};
public:
	int number;
	Color color;
	bool visible;
	Card *successor;

	Card(int ,Color);
	int changeVisibility(void);
};

class Game {
public:
	std::vector<Move> history [5];
	std::vector<Card> mainDeck [52];
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

class Deck final: public Game{
private:
	enum Position{flipDeck=1, flopDeck, starterDeck, finalDeck};
	enum Permissions{insert=1, get, insert_get};
	int checkValidity(Deck *);
public:
	std::vector<Card> cards;
	Position position;
	Permissions permissions;

	Deck(Permissions ,Position );
	~Deck();
	/* deck to deck change, vect cards, position, checkValidity() */
	int insertCards(Card *);
	/* using successor of Cards (Card::successor) */
	std::vector<Card> getCards(Card *);
	/* decorator fnc */
	Card& getLastCard();
	Move* hint(Deck *);
};



#endif
// class Move {
// private:
// 	Deck *deck;
// public:
// 	void execute(){
// 		(deck->*method)();
// 	}
// };