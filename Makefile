###############################################################################
# xTamas and xVasko presents the ultimate survival Klondike guide             #
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
#Change working directory
#CWD=./src/

.PHONY: all clean run

all: $(GUI) $(CLI)

$(GUI):
	@cd src/ && $(MAKE) GUI
	cp src/$(GUI) ./

$(CLI):
	@cd src/ && $(MAKE) CLI
	cp src/$(CLI) ./

#FIXME, run CLI or GUI?
run:
	./hra2017_cli

#FIXME recursive
zip: src/* examples/* doc/ Makefile README.txt
	zip xvasko12_xtamas01.zip -r $^

#FIXME doxygen doxyfile
clean:
	$(RM) $(GUI) $(CLI) && $(MAKE) clean
