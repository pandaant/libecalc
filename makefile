# compiler
CXX = clang++ -g

# variables for libecalc
INCLUDES=-I ./include/ecalc -I ./dep/libpoker/include
CXXFLAGS=-m64 -static -ansi -std=c++11 -MMD -MP 

# add paths of libraries the
# targets depend on.
LIBRARIES =

DOC_OUT = doc

ifeq ($(target),debug)
    CXXFLAGS +=-O0 -Weverything -Wno-c++98-compat #-Werror
else
    target = release
	CXXFLAGS +=-O3 -Wall
endif

LIB_OUT = lib/$(target)/libecalc.a

# gobble a files for compilation
CPP_FILES = $(wildcard src/*.cpp)
OBJ_FILES = $(addprefix obj/$(target)/,$(notdir $(CPP_FILES:.cpp=.o)))
DEP_FILES = $(OBJ_FILES:.o=.d)

$(LIB_OUT): $(OBJ_FILES)
	ar rcs $@ $^

obj/$(target)/%.o: src/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c -o $@ $<

dep:
	cd dep/libpoker && make all

prepare:
	mkdir -p obj/{release,debug}
	mkdir -p lib/{release,debug}

all: prepare dep $(LIB_OUT)

doc:
	mkdir -p $(DOC_OUT)
	doxygen doxyfile

clean:
	rm -f $(OBJ_FILES)
	rm -f $(DEP_FILES)
	rm -f $(LIB_OUT)
	rm -f -r $(DOC_OUT)
	cd dep/libpoker && make clean

-include $(DEP_FILES)

.PHONY: clean all doc dep
