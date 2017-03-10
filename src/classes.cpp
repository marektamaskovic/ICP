#include "classes.h"
#include "core.h"


Game::Game(){
	current_count++;
	id = current_count;
	position = getPosition();
}

Game::~Game(){
	current_count--;
}

/* */
Move* Game::hint(){
	return nullptr;
}