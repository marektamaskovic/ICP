/* xTamas01 and xVasko12 presents the ultimate survival Klondike guide
 * Project: ICP17, a Klondike (Solitaire) game
 * FIT VUT Brno
 * Authors: xtamas01 - Tamaškovič Marek
 *          xvasko12 - Vaško Martin
 */

#include <cstdio>
#include <cstdlib>

#include "core.h"
#include "classes.h"
#include "json.hpp"
// #include <ncurses.h> // Link \w -lncurses

// #define NGUI
#ifndef NGUI

#include <QApplication>

#include "table.h"
#include "mainwindow.h"

#endif




extern int position[];
extern int count_cards_end_game;

session_t currentSession;

int main(int argc, char *argv[]){

	static_cast<void> (argc);
	static_cast<void> (argv);

#ifdef NGUI
	std::string cmdBuffer = "";

	std::cout << ">>> ";
	while(getline(std::cin, cmdBuffer)){
		// std::cout << "Game: " << count_cards_end_game << "\n";
		if (count_cards_end_game == 52){
			finishGame();
			std::cout << "You finished Game. Congratulations!\n";
			// TODO score + remove game and end session?
		}
		if(cmdBuffer == ""){
			std::cout << std::endl;
			// break;
		}

		if(cmdBuffer == "exit()" || cmdBuffer == "exit"){
			break;
		}
		else{
			resolveCmd(&currentSession, cmdBuffer);
		}

		std::cout << ">>> ";
		cmdBuffer = "";
	}
	if(cmdBuffer == ""){
		std::cout << std::endl;
	}

    return 0;
#else

    QApplication klondike(argc, argv);
    MainWindow window;
    window.showMaximized();

    return klondike.exec();

#endif
}































