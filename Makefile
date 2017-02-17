CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++14 -Weffc++
CXXLIBS=
LDFLAGS=-L.

EXE=a

.PHONY: all clean

debug: CXXFLAGS += -g3
debug: all

all: a

run:
	./a

clean:
	$(RM) $(EXE) *.o
