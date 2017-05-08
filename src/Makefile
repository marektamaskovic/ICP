###############################################################################
# xTamas01 and xVasko12 presents the ultimate survival Klondike guide         #
# Project: ICP17, a Klondike (Solitaire) game                                 #
# FIT VUT Brno                                                                #
# Authors: xtamas01 - Tamaškovič Marek                                        #
#          xvasko12 - Vaško Martin                                            #
# Makefile supports various types of architectures, machines and much more... #
# supports commands: make, make clean, make gui, make cli, make zip, make run #
###############################################################################

#variables of compilation
ifeq ($(OS),Windows_NT)
	#REMOVE =del
	GUI=hra2017.exe
	CLI=hra2017-cli.exe
else
	#libraries
	GUI=hra2017
	CLI=hra2017-cli
endif

CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++11 -Weffc++ -g3
CXXLIBS=
LDFLAGS=-L.
DEPS=core.o classes.o save.o
BIN=hra2017 hra2017-cli

#Colors
GREEN=\033[1;32m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

.PHONY: $(CLI) $(GUI) all clean

all: $(CLI) $(GUI)

core.o: core.h core.cpp
	@echo -e "$(YELLOW)=== BUILDING OBJ $(NC)"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c core.cpp -o $@
classes.o: classes.h classes.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c classes.cpp -o $@

$(GUI):
	@echo -e "$(GREEN)=== Building GUI $(NC)"
	qmake 4.pro -o qmakefile
	make -f qmakefile
$(CLI):$(DEPS)
	@echo -e "$(GREEN)=== Building CLI $(NC)"
	$(CXX) -c $(CXXFLAGS) $(LDFLAGS) -DNGUI main.cpp -o main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o $(DEPS) -o $@

hra2017-cli-tr: CXX=g++-6
hra2017-cli-tr: hra2017-cli

clean:
	@echo -e "$(RED)cleaning like mexican cleaning lady $(NC)"
	rm $(BIN) *.o qrc* moc_* ui_*.h qmakefile
