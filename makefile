# compiler
CC=clang++

# variables for libecalc
ECALC_CPPFLAGS=-m64 -Ofast -Wall -static -ansi -pedantic -std=c++11 -g
ECALC_INCLUDES=-I ./include
ECALC_LIBFILE=libecalc.a
ECALC_DEPFILE=.depend

ECALC_CPP_FILES = $(wildcard src/*.cpp)
ECALC_OBJ_FILES = $(addprefix obj/,$(notdir $(ECALC_CPP_FILES:.cpp=.o)))

# variables for tests
TEST_CPPFLAGS=-m64 -Ofast -Wall -pedantic -std=c++11 -g
TEST_INCLUDES=-I ./include -I ../../dep/UnitTest++/src -I ../poker/include
TEST_OUTFILE=test/ecalc_tests
TEST_CPP_FILES = $(wildcard test/src/*.cpp)
TEST_OBJ_FILES = $(addprefix test/obj/,$(notdir $(TEST_CPP_FILES:.cpp=.o)))
TEST_LIBS= -L ./ -lecalc -L ../../dep/UnitTest++ -lUnitTest++ -L ../poker/dist/Release -lpoker


$(ECALC_LIBFILE): $(ECALC_OBJ_FILES)
	ar rcs $@ $^

obj/%.o: src/%.cpp
	$(CC) $(ECALC_INCLUDES) $(ECALC_CPPFLAGS) -c -o $@ $<

test/obj/%.o: test/src/%.cpp
	$(CC) $(TEST_INCLUDES) $(TEST_CPPFLAGS) -c -o $@ $<

tests: $(TEST_OBJ_FILES)
	$(CC) $(TEST_INCLUDES) $(TEST_OBJ_FILES) $(TEST_LIBS) -o $(TEST_OUTFILE)

all: $(LIBFILE)

depend: $(ECALC_DEPFILE)
$(ECALC_DEPFILE): $(ECALC_CPP_FILES)
	rm -f ./$(ECALC_DEPFILE)
	$(CC) $(ECALC_INCLUDES) $(ECALC_CPPFLAGS) -MM $^>>./$(ECALC_DEPFILE);
include $(ECALC_DEPFILE)

clean:
	rm -f $(ECALC_DEPFILE)
	rm -f $(ECALC_OBJ_FILES)
	rm -f $(TEST_OBJ_FILES)
	rm -f $(ECALC_LIBFILE)
	rm -f $(TEST_OUTFILE)
