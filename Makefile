CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17
CPPFLAGS = -Isrc/

MAIN_OBJ = src/main.o $(OBJ)
MAIN_BIN = main

TESTS_OBJ = tests/unary_tests.o $(OBJ)
TESTS_BIN = unary_tests

all: $(MAIN_BIN) $(TESTS_BIN)

$(MAIN_BIN): $(MAIN_OBJ)
	$(LINK.cc) $^ $(LDLIBS) -o $@

$(TESTS_BIN): LDLIBS += -lcriterion
$(TESTS_BIN): $(TESTS_OBJ)
	$(LINK.cc) $^ $(LDLIBS) -o $@

check: $(TESTS_BIN)
	./$(TESTS_BIN)

clean:
	$(RM) $(OBJ) $(MAIN_OBJ) $(MAIN_BIN) $(TESTS_BIN) $(TESTS_OBJ)


.PHONY: all check clean
