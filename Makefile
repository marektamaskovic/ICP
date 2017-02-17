CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++14 -Weffc++
CXXLIBS=
LDFLAGS=-L.

EXE=a

.PHONY: all

debug: CXXFLAGS += -g3
debug: all

all: a
	

clean:
	$(RM) $(EXE) *.o
