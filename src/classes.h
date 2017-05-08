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

class Card;
class Game;
class Deck;
class ICommand;
/**
 * Public stucture where is stored Move - used for undo functionality and for
 * hint. Hint does not need turnedUp attribute so it is ignored.
 */
typedef struct {
	int from; 		///< From which deck is Card taken
	int to;			///< To which deck is Card given
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
	void printColor(std::string);	///< Print color by given name
	void printColor(int);			///< Print color by given number
public:
	bool operator==(const Card&);	///< Overload operator == with 2 cards
	int number;						///< Number of card from 1 to 13
	Color color;					///< Color of card defined by enum
	bool visible;					///< Visibility of card

	Card();							///< Empty constructor
	Card(const Card &);				///< Copy constructor of card
	Card(int ,Color);				///< Implicit false visibility
	Card(int ,Color, bool);			///< Full constructor
	void printCard();				///< Prints Card to standard output.
	/**
	 * change visibility of given card to negated visibility of given card.
	 */
	void changeVisibility();
};

/**
 * Game class which holds entire Game - mulptiple games, decks and history.
 */
class Game {
// friend class Deck;
/* */
public:
	std::vector<Move> history;			///< History of moves
	std::vector<Card> mainDeck;			///< All cards when dealing to decks
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
	int count_cards_end_game = 0;

	Game();								///< Empty constructor
	Game(const Game &G);				///< Copy constructor of Game
	Game& operator=(const Game &G);		///< Assign operator to copy Game
	~Game();							///< Destructor for all decks
	void showGame();					///< Shows Game status
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
	static int current_count;			///< Number of games created.
private:
	int id = 0;							///< Id of created game.
	int position = 0;					///< Which position game occupies.
};

class Deck{
private:
	/**
	 * @param vector of Cards.
	 * @see Card
	 * Method pushes card of vector given as parameter to deck.
	 */
	void pushCardVector(std::vector<Card>);
public:
	int deck = 0;						///< Indicates deck number.
	std::vector<Card> cards;			///< Vector of cards in deck.
	Position position;					///< Deck position in game.
	Permissions permissions;			///< Permission of deck, wether we can take card from it or place on it or both.

	Deck();								///< Empty deck constructor.
	Deck(Permissions, Position, int);	///< Full deck constructor.
	Deck(const Deck&);					///< Copy constructor of deck.
	/**
	 * @param vector of Cards.
	 * @return 0 on success of move command. Otherwise -1.
	 * Method moves Cards from one deck which is represented as parameter of
	 * vector cards to current deck.
	 */
	int moveCards(std::vector<Card> );
	/**
	 * Gets last card from deck.
	 */
	inline Card& getLastCard();
	/**
	 * Prints Deck to std output.
	 */
	void printDeck();
	/**
	 * @param Waste deck.
	 * @return 0 when successfull pop.Otherwise -1.
	 * Pops card from stack deck and move it to waste deck.
	 */
	int dequeue(Deck *);
	/**
	 * @param Card which should be checked
	 * @return 0 when it is valid to move card to deck. Otherwise -1.
	 * Method checks permissions of deck and position where card should be
	 * movec, card number and color.Every move is based on rules of Klondike
	 * movement.
	 * @see cardCondition
	 */
	int checkValidity(Card &card);
	/**
	 * @param Pushed card.
	 * Pushes card to end of the vector.
	 */
	inline void insertCard(Card &card){ this->cards.push_back(card); }
};


/**
 * @return random number.
 * Generates random number with help of standard library.
 */
static inline int myrandom (int i) { return std::rand()%i;}
/**
 * @param Card which should be put on.
 * @param Card on which should be put card.
 * @return true when it is possible. Otherwise false is returned.
 * Checks card condition - the card on back should be the same number as put
 * card number - 1. Then chcecks for color. Card can be put only with oposite
 * color Red to Black for example Heart to Spade.
 */
bool cardCondition(Card &, Card &);
/**
 * @param History vector.
 * Prints to standard output Whole vector of Move, used for history checkout.
 */
void printMove(std::vector<Move>);
/**
 * @param History vector.
 * Clears history. After that undo is empty.
 */
void clearHistory(std::vector<Move>);
/**
 * @param Input argument of card which is processed
 * @param Output parameter where is deck number stored.
 * @return vector of cards which should be moved.
 * Parses standard input command argument to Card, loop all decks and find
 * that parsed card. Fill deck number, check wether are there some cards after
 * this card and make vector of cards from that card to end of deck.
 * @see Card
 * @see checkNext
 */
std::vector<Card> parseCard(std::string, int *);
/**
 * @param Input string of deck which is processed.
 * @return deck.
 * From deck number parse deck and return it.
 */
Deck *parseDeck(std::string);
/**
 * @param Card which should be put on.
 * @param Card on which should be put card.
 * @return Card which should be put on.
 * Check next is used to push vector of cards after exact card. Used for parse Card.
 * @see parseCard.
 */
Card *checkNext(Card &, Card *);
/**
 * @param History of moves
 * @return History of moves without last record.
 * Function executes undo movement based on operation filled in move vector.
 * 3 types of movement - Pop, pop which reverses waste to Stack, and move cards between decks. At end of undo is last record deleted since movement was executed backwards.
 */
std::vector<Move> undo(std::vector<Move>);
/**
 * Executes end of game loop when all 52 cards are visible.
 */
void finishGame();

#endif
