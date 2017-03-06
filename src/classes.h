/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */

#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#ifndef
#define CLASSES

//enum symbol{A=1,J=11,Q,K};
/* TODO Doxygen */
class Card;
class Game;
class Deck;

typedef struct {
  Deck &from;
  Deck &to;
  Card &card;
  unsigned numberOfCards; //successor
}Move;

class Card{
  enum Color{heart,spade,diamond,club};
public:
  Color color;
  int number;
  Card successor;
  bool visible;

  Card();
  ~Card();
  changeVisibility();
};

class Deck : public Game{
public:
  std::vector<&Card> cards;
  Position position;
  Permissions permissions;

  Deck();
  ~Deck();
  /* deck to deck change, vect cards, position, checkValidity() */
  insertCards();
  /* using successor of Cards (Card::successor) */
  getCards();
  /* decorator fnc */
  getLastCard();
private:
  enum Permissions{insert=1, get, insert_get};
  enum Position{flipDeck=1, flopDeck, starterDeck, finalDeck};

  checkValidity();
};

class Game{
public:
  std::vector<Move> history;
  std::vector<&Card> mainDeck;

  Game();
  ~Game();
  /* FILE */
  save();
  load();
  hint();
  static inline numberOfGames(){ return current_count; }

private:
  int id;
  int position;

  static int current_count=0;
};

#endif
