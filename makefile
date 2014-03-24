# compiler
CC=clang++ -g

# variables for libecalc
DEPFILE=.depend
LIBFILE=libecalc.a
INCLUDES=-I ./include -I ../poker/include
CPPFLAGS=-m64 -O3 -Wall -static -ansi -pedantic -std=c++11
LIBRARIES=

# gobble a files for compilation
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

$(LIBFILE): $(OBJ_FILES)
	ar rcs $@ $^

obj/%.o: src/%.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) $(LIBRARIES) -c -o $@ $<

all: $(LIBFILE)

depend: $(DEPFILE)
$(DEPFILE): $(CPP_FILES)
	rm -f ./$(DEPFILE)
	$(CC) $(INCLUDES) $(CPPFLAGS) -MM $^>>./$(DEPFILE);
include $(DEPFILE)

clean:
	rm -f $(DEPFILE)
	rm -f $(OBJ_FILES)
	rm -f $(LIBFILE)
