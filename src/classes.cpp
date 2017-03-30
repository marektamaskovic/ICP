#include "classes.h"
#include "core.h"

int Game::current_count = 0;


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