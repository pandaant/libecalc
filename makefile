# compiler
CXX = clang++ -g

# variables for libecalc
LIB_OUT=libecalc.a
INCLUDES=-I ./include -I ../poker/include
CPPFLAGS=-m64 -O3 -static -ansi -std=c++11 \
		 -MMD -MP -Weverything -Wno-c++98-compat #-Werror
LIBRARIES=

# gobble a files for compilation
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(OBJ_FILES:.o=.d)

$(LIB_OUT): $(OBJ_FILES)
	ar rcs $@ $^

obj/%.o: src/%.cpp
	$(CXX) $(INCLUDES) $(CPPFLAGS) $(LIBRARIES) -c -o $@ $<

all: $(LIBFILE)

.PHONY: clean
clean:
	rm -f $(OBJ_FILES)
	rm -f $(DEP_FILES)
	rm -f $(LIB_OUT)

-include $(DEP_FILES)
