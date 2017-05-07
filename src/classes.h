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

/**
 * enum which converts number of card to name ( based on real Cards )
 */
enum Symbol{A=1,J=11,Q,K,undef};
/**
 * enum colors of cards
 */
enum Color{Heart,Spade,Diamond,Club};
/**
 * Position of deck in game
 */
enum Position{stack=1, waste, pileau, foundation};
/**
 * Permissions of deck in game
 */
enum Permissions{insert=1, get, insert_get};
/**
 * number of turned face up cards
 */
extern int count_cards_end_game;


class Card;
class Game;
class Deck;
class ICommand;
/**
 * public stucture where is stored Move - used for undo functionality and for
 * hint. Hint does not need turnedUp attribute so it is ignored.
 */
typedef struct {
	int from; 		///< from which deck is Card taken
	int to;			///< to which deck is Card given
	Card *card;		///< Card which should be taken
	bool turnedUp;	///< Card before should be turnedUp or not
}Move;

/**
 * Card class, attributes are modeling real Card and some abstraction methods.
 * @see Color
 * @see Symbol
 */
class Card final{
private:
	void printColor(std::string);	///< print color by given name
	void printColor(int);			///< print color by given number
public:
	bool operator==(const Card&);	///< overload operator == with 2 cards
	int number;						///< number of card from 1 to 13
	Color color;					///< color of card defined by enum
	bool visible;					///< visibility of card

	Card();							///< empty constructor
	Card(const Card &);				///< copy constructor of card
	Card(int ,Color);				///< implicit false visibility
	Card(int ,Color, bool);			///< full constructor
	void printCard();				///< prints Card to std::cout
	/**
	 * change visibility of given card to negated visibility of given card.
	 */
	inline void changeVisibility(){
		this->visible = !this->visible;
		if (this->visible == true) { ++count_cards_end_game; }
		else { --count_cards_end_game; }
	};
};

/**
 * Game class which holds entire Game - mulptiple games, decks and history.
 */
class Game {
// friend class Deck;
/* */
public:
	std::vector<Move> history;			///< history of moves
	std::vector<Card> mainDeck;			///< all cards when dealing to decks
	/**
	 * @see deck
	 * All decks in game
	 * 11   = flop deck
	 * 12   = flip deck
	 * 0-3  = finalDecks
	 * 4-10 = for starterDecks
	 */
	Deck *decks [13];
	int m = 0;

	Game();								///< Empty constructor
	Game(const Game &G);				///< copy constructor of Game
	Game& operator=(const Game &G);		///< assign operator to copy Game
	~Game();							///< destructor for all decks
	void showGame();					///< shows Game status
	/**
	 * @return  On success move structure is filled with necessary things else nullptr is returned.
	 * Method is traversing all decks twice and tries every card to place on
	 * another.Move filled - from which deck you should put card to which deck
	 * and which card.
	 */
	Move* hint();
	/**
	 * @return how many games are created.
	 */
	static inline int numberOfGames(){ return current_count; }
	static int current_count;			///< number of games created.
private:
	int id = 0;							///< id of created game.
	int position = 0;					///< which position game occupies.
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
