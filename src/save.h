#ifndef SAVE_H
#define SAVE_H

#include "core.h"
#include "json.hpp"

using json = nlohmann::json;

int save(std::string &, Game &);

#endif