# compiler
CC=clang++

DEBUGFLAGS=-O0 -g
CPPFLAGS=-m64 -O3 -Wall -pedantic -std=c++11
INCLUDES=-I ../include -I ../../../dep/UnitTest++/src -I ../../poker/include
OUTFILE=run_tests
DEPFILE=.depend
CPP_FILES = $(wildcard *.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LIBS= -L ./.. -lecalc -L ../../../dep/UnitTest++ -lUnitTest++ -L ../../poker/dist/Release -lpoker

obj/%.o: %.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) -c -o $@ $<

all: $(OBJ_FILES)
	$(CC) $(INCLUDES) $(OBJ_FILES) $(LIBS) -o $(OUTFILE)

depend: $(DEPFILE)
$(DEPFILE): $(CPP_FILES)
	rm -f ./$(DEPFILE)
	$(CC) $(INCLUDES) $(CPPFLAGS) -MM $^>>./$(DEPFILE);
	# make libecalc
	cd .. && $(MAKE);
include $(DEPFILE)

clean:
	rm -f $(DEPFILE)
	rm -f $(OBJ_FILES)
	rm -f $(OUTFILE)
