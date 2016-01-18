#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"
#include <algorithm>

class Card;

class Deck{

  public:
    Deck();
    void addCard(Card*);
    Card* getCard();
    int size();
    void shuffle();

  private:
    std::vector<Card*> cards;

};

#endif
