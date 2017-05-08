#ifndef SAVE_H
#define SAVE_H

#include "core.h"
#include "json.hpp"

using json = nlohmann::json;

/**
 * @brief      Error printing macro
 *
 * @param      x     additional message
 *
 * @return    nothing
 */
#define err_msg(x)	do{																	\
						std::cerr << "ERROR: " << __func__ << ": " << x << std::endl;	\
					}while(0)

/**
 * @brief      Save game
 *
 * @param[in] std::string& Filename where to save game
 * @param[in] Game& Which game to save.
 *
 * @return     If successful returns 0 otherwise non-zero value;
 */
int save(std::string &, Game &);

/**
 * @brief      Loads a game.
 *
 * @param      std::string filename where is game saved.
 * @param[in]	session_t*	Pointer to a game session where should this function load the game.
 *
 * @return     If successful returns 0 else non-zero value.
 */
int load_game(std::string &, session_t *);

/**
 * @brief      Loads a deck. Pushes all cards from json::iterator to a deck.
 *
 * @param[in]  element  iterator where are cards located.
 * @param[out]      deck		here will be stored all loaded cards.
 *
 * @return     If successful returns 0 else non-zero value.
 */
int load_deck(json::iterator, Deck *);

#endif