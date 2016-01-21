#
#Makefile for CS362 BlackJack
#

#Compiler
CXX = g++

#Non-test build flags
CXXFLAGS = --std=c++11 -finput-charset=utf-8 -Wall

#Test build flags
CXXTFLAGS = --std=c++11 -finput-charset=utf-8 -Wall -g

SRCEXT := cpp
SRCDIR := src

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJS = $(patsubst $(SRCDIR)/%.cpp,%.o,$(SRCS))

BIN := cardTest handTest main

mainDeps := Card.o Deck.o Hand.o Player.o main.o
cardTestDeps := Card.o Deck.o cardTest.o
handTestDeps := Card.o Deck.o Player.o Hand.o handTest.o

all: handTest cairdTest main

$(OBJS):
	@echo "------------Compiling: " $@ "------------"
	$(CXX) -o $@ -c $(SRCDIR)/$(basename $@).$(SRCEXT) $(CXXTFLAGS)
	@echo ""

handTest: $(handTestDeps)
	@echo "------------Linking: " $@ "------------"
	$(CXX) -o $@ $^ $(CXXTFLAGS)
	@echo ""

cardTest: $(cardTestDeps)
	@echo "------------Linking: " $@ "------------"
	$(CXX) -o $@ $^ $(CXXTFLAGS)
	@echo ""

main: $(mainDeps)
	@echo "------------Linking: " $@ "------------"
	$(CXX) -o $@ $^ $(CXXFLAGS)
	@echo ""

.PHONY: all directories clean

clean:
	@echo "------------Cleaning------------"
	@rm -fv *.o
	@rm -fv $(BIN)
