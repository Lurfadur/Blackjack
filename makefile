CC = g++
CFLAGS = --std=c++11 -finput-charset=utf-8

card.o: Card.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

deck.o: Deck.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

cardTest.o: cardTest.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

blackjack: cardTest.o deck.o  card.o
	$(CC) -o blackjack cardTest.o deck.o card.o $(CFLAGS)

clean:
	rm -fv *.o
	rm -fv blackjack
