CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -pedantic -std=c++14 -Weffc++
CXXLIBS=
LDFLAGS=-L.
DEPS=core.o classes.o
BIN=hra2017 hra2017-cli

#Colors
GREEN=\033[1;32m
RED=\033[1;31m
NC=\033[0m

.PHONY: hra2017 hra2017-cli all clean

all: hra2017 hra2017-cli

hra2017: main.o $(DEPS)
	@echo -e "$(GREEN)=== Building GUI $(NC)"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(DEPS) -o $@
hra2017-cli: main.o $(DEPS)
	@echo -e "$(GREEN)=== Building CLI $(NC)"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(DEPS) -o $@

hra2017-cli-tr: CXX=g++-6
hra2017-cli-tr: hra2017_cli

clean:
	@echo -e "$(RED)cleaning like mexican cleaning lady $(NC)"
	rm $(BIN) *.o
