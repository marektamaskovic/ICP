/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */

#ifndef CLASSES
#define CLASSES

#include <vector>

//enum symbol{A=1,J=11,Q,K};
// TODO Doxygen

class Card;
class Game;
class Deck;



typedef struct {
  Deck &from;
  Deck &to;
  Card &card;
  unsigned numberOfCards; // successor
}Move;

class Card{
  enum Color{heart,spade,diamond,club};
public:
  Color color;
  int number;
  Card &successor;
  bool visible;

  Card();
  ~Card();
  int changeVisibility(void);
};

class Game{
public:
  std::vector<Move> history [5];
  std::vector<Card> mainDeck [52];
  Game();
  ~Game();
  /* FILE */
  int save();
  int load();
  Move* hint();
  static inline int numberOfGames(){ return current_count; }

private:
  int id = 0;
  int position = 0;

  static int current_count;
};

class Deck : public Game{
private:
  enum Permissions{insert=1, get, insert_get};
  enum Position{flipDeck=1, flopDeck, starterDeck, finalDeck};

  int checkValidity(void);
public:
  std::vector<Card> cards;
  Position position;
  Permissions permissions;

  Deck();
  ~Deck();
  /* deck to deck change, vect cards, position, checkValidity() */
  int insertCards();
  /* using successor of Cards (Card::successor) */
  Card& getCards(void);
  /* decorator fnc */
  Card& getLastCard();
};

int Game::current_count = 0;


#endif
