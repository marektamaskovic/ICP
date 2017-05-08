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

session_t currentSession;

int main(int argc, char *argv[]){

	static_cast<void> (argc);
	static_cast<void> (argv);

#ifdef NGUI
	std::string cmdBuffer = "";
	std::cout << "Welcome to Klondike CLI version.\n";
	std::cout << "authors: Martin Vasko and Marek Tamaskovic\n";
	std::cout << "For any complains please contact us on email: \nxvasko12@stud.fit.vutbr.cz\n";
	std::cout << "or\nxtamas01@stud.fit.vutbr.cz\n";
	std::cout << "Game begins with command 'createGame'.\n";
	std::cout << "To see all available commands use 'help'\n";
	std::cout << "Enjoy the game :).\n";
	std::cout << "\n>>> ";
	while(getline(std::cin, cmdBuffer)){
		if(cmdBuffer == ""){
			std::cout << std::endl;
		}

		if(cmdBuffer == "exit()" || cmdBuffer == "exit"){
			break;
		}
		else{
			resolveCmd(&currentSession, cmdBuffer);
			if (currentSession.slot[currentSession.currentGame]->count_cards_end_game == 52){
				finishGame();
				std::cout << "You finished Game. Congratulations!\n";
			}
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































