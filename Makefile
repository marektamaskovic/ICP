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
	CLI=hra2017_cli.exe
else
	#libraries
	GUI=hra2017
	CLI=hra2017_cli
endif

.PHONY: all clean run doc travis_compile

all: $(GUI) $(CLI)

$(GUI):
	@cd src/ && $(MAKE) $@
	cp src/$(GUI) ./

$(CLI):
	@cd src/ && $(MAKE) $@
	cp src/$(CLI) ./

travis_compile:
	@cd src/ && $(MAKE) hra2017_cli-tr
	cp src/hra2017_cli ./

#FIXME, run CLI or GUI?
run:
	./hra2017_cli

doc:
	cd src/ && doxygen doxyfile

#FIXME recursive
zip: src/* examples/* doc/ Makefile README.txt
	zip xvasko12_xtamas01.zip -r $^

#FIXME doxygen doxyfile
clean:
	$(RM) $(GUI) $(CLI)
	@cd src/ && $(MAKE) clean
	$(RM) -r ./doc/*
