# compiler
CC=clang++

CPPFLAGS=-m64 -Ofast -Wall -pedantic -std=c++11 -g
INCLUDES=-I ../include -I ../../../dep/UnitTest++/src -I ../../poker/include
OUTFILE=run_tests
DEPFILE=.depend
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LIBS= -L ./.. -lecalc -L ../../../dep/UnitTest++ -lUnitTest++ -L ../../poker/dist/Release -lpoker

obj/%.o: src/%.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) -c -o $@ $<

all: $(OBJ_FILES)
	$(CC) $(INCLUDES) $(OBJ_FILES) $(LIBS) -o $(OUTFILE)

depend: $(DEPFILE)
$(DEPFILE): $(CPP_FILES)
	rm -f ./$(DEPFILE)
	$(CC) $(INCLUDES) $(CPPFLAGS) -MM $^>>./$(DEPFILE);
include $(DEPFILE)

clean:
	rm -f $(DEPFILE)
	rm -f $(OBJ_FILES)
	rm -f $(OUTFILE)
