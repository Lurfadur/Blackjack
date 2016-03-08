#
#Makefile for CS362 BlackJack
#

#Compiler
CXX = g++

#Non-test build flags
CXXFLAGS = --std=c++11 -finput-charset=utf-8

#Test build flags
CXXTFLAGS = --std=c++11 -finput-charset=utf-8 -g

SRCEXT := cpp
SRCDIR := src

SRCS := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJS = $(patsubst $(SRCDIR)/%.cpp,%.o,$(SRCS))

mainDeps := Card.o Deck.o Hand.o Player.o Dealer.o Controller.o main.o
cardTestDeps := Card.o Deck.o cardTest.o
handTestDeps := Card.o Deck.o Player.o Hand.o handTest.o
playerTestDeps := Card.o Deck.o Player.o Hand.o playerTest.o
dealerTestDeps := Card.o Deck.o Player.o Hand.o Dealer.o dealerTest.o
controllerTestDeps := Card.o Deck.o Player.o Hand.o Dealer.o Controller.o controllerTest.o

all: handTest cardTest playerTest dealerTest controllerTest main 
BIN := cardTest handTest playerTest dealerTest controllerTest main

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

playerTest: $(playerTestDeps)
	@echo "------------Linking: " $@ "------------"
	$(CXX) -o $@ $^ $(CXXTFLAGS)
	@echo ""

dealerTest: $(dealerTestDeps)
	@echo "------------Linking: " $@ "------------"
	$(CXX) -o $@ $^ $(CXXTFLAGS)
	@echo ""

controllerTest: $(controllerTestDeps)
	@echo "-------------Linking: " $@ "------------"
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
