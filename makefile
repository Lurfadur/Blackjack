CC = g++
CFLAGS = --std=c++11
DEPS = Card.h Deck.h
OBJ = Card.o Deck.o cardTest.o


%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

blackjack: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-rm -f *.o
