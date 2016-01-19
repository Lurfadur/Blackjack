#
#Makefile for CS362 BlackJack
#
#see
#http://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables
#for reference information

CXX = g++
CXXFLAGS = --std=c++11 -finput-charset=utf-8 -Wall

SRCEXT := cpp
SRCDIR := src

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJS = $(patsubst $(SRCDIR)/%.cpp,%.o,$(SRCS))

BIN := cardTest handTest

cardTestDeps := Card.o Deck.o cardTest.o
handTestDeps := Deck.o Player.o Hand.o handTest.o

all: handTest cardTest

$(OBJS):
	@echo "------------Compiling: " $@ "------------"
	$(CXX) -o $@ -c $(SRCDIR)/$(basename $@).$(SRCEXT) $(CXXFLAGS)
	@echo ""

handTest: $(handTestDeps)
	$(CXX) -o $@ $^ $(CXXFLAGS)

cardTest: $(cardTestDeps)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: all directories clean

clean:
	@echo "------------Cleaning------------"
	@rm -fv *.o
	@rm -fv $(BIN)
