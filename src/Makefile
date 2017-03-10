CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++14 -Weffc++
CXXLIBS=
LDFLAGS=-L.
DEPS= classes.o
BIN=hra2017 hra2017-cli

.PHONY: hra2017 hra2017-cli all clean

all: hra2017 hra2017-cli

hra2017: main.cpp $(DEPS)
	@echo "=== Building GUI "
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@
hra2017-cli: main.cpp $(DEPS)
	@echo "=== Building CLI "
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@



clean:
	@echo "cleaning like mexican cleaning lady"
	rm $(BIN)
