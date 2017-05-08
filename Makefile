###############################################################################
# xTamas01 and xVasko12 presents the ultimate survival Klondike guide         #
# Project: ICP17, a Klondike (Solitaire) game                                 #
# FIT VUT Brno                                                                #
# Authors: xtamas01 - Tamaškovič Marek                                        #
#          xvasko12 - Vaško Martin                                            #
# Makefile supports various types of architectures, machines and much more... #
# supports commands:  make, make clean, make gui, make cli, make run          #
#                     make doxygen, make pack                                 #
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

#Colors
GREEN=\033[1;32m
RED=\033[1;31m
CYAN=\033[1;36m
NC=\033[0m

.PHONY: all clean run doc travis_compile

all: welcom_msg $(GUI) $(CLI)

welcom_msg:
	@echo -e "$(CYAN)=== ICP PROJECT 2017 ===$(NC)"

$(GUI):
	@cd src/ && $(MAKE) $@
	cp src/$(GUI) ./

$(CLI):
	@cd src/ && $(MAKE) $@
	cp src/$(CLI) ./

travis_compile:
	@cd src/ && $(MAKE) hra2017-cli-tr
	cp src/hra2017-cli ./hra2017-cli

run:
	./hra2017
	./hra2017-cli

doxygen:
	cd src/ && doxygen doxyfile

pack: src/* examples/* doc/ Makefile README.txt
	zip -r -9 xvasko12_xtamas01.zip $^

clean:
	@echo -e "$(RED)=== Cleaning $(NC)"
	$(RM) $(GUI) $(CLI)
	@cd src/ && $(MAKE) clean
	$(RM) -r ./doc/* xvasko12_xtamas01.zip
