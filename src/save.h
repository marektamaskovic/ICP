#ifndef SAVE_H
#define SAVE_H

#include "core.h"
#include "json.hpp"

using json = nlohmann::json;

#define err_msg(x)	do{																	\
						std::cerr << "ERROR: " << __func__ << ": " << x << std::endl;	\
					}while(0)

int save(std::string &, Game &);
int load_game(std::string &, session_t *);
int load_deck(json::iterator, Deck *);

#endif