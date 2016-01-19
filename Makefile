#
#Makefile for CS362 BlackJack
#

CXX = g++
CXXFLAGS = --std=c++11 -finput-charset=utf-8 -Wall

SRCEXT := cpp
SRCDIR := src

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJS = $(patsubst $(SRCDIR)/%.cpp,%.o,$(SRCS))

BIN := cardTest handTest

cardTestDeps := Card.o Deck.o cardTest.o
handTestDeps := Card.o Deck.o Player.o Hand.o handTest.o

all: handTest cardTest

$(OBJS):
	@echo "------------Compiling: " $@ "------------"
	$(CXX) -o $@ -c $(SRCDIR)/$(basename $@).$(SRCEXT) $(CXXFLAGS)
	@echo ""

handTest: $(handTestDeps)
	@echo "------------Linking: " $@ "------------"
	$(CXX) -o $@ $^ $(CXXFLAGS)
	@echo ""

cardTest: $(cardTestDeps)
	@echo "------------Linking: " $@ "------------"
	$(CXX) -o $@ $^ $(CXXFLAGS)
	@echo ""

.PHONY: all directories clean

clean:
	@echo "------------Cleaning------------"
	@rm -fv *.o
	@rm -fv $(BIN)
