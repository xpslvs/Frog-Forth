
CXX       := g++
CXXFLAGS  := -std=c++11 -O0 -march=native -pedantic
LFLAGS    := 
CXXFILES  := $(wildcard src/*.cc)
OFILES    := $(patsubst src/%.cc, obj/%.cc.o, $(CXXFILES))
ELFFILE   := forth

$(ELFFILE): $(OFILES) Makefile
	$(CXX) -o $@ $(OFILES) $(LFLAGS)

obj/%.cc.o: src/%.cc Makefile
	$(CXX) -o $@ $< $(CXXFLAGS) -c

.PHONY: clean all rebuild

clean:
	$(RM) obj/*.cc.o
	$(RM) $(ELFFILE)

all: $(ELFFILE)

rebuild: clean all

