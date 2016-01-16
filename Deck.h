#ifndef DECK_H
#define DECK_H

#include <vector>
#include <Card.h>

class Deck{

  Public:
    Deck();
    void addCard(Card::Card);
    Card::Card getCard();
    void shuffle();

  Private:
    vector<Card::Card> cards;

};

#endif
