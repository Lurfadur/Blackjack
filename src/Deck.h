#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"
#include <algorithm>

class Card;

class Deck{

  public:
    /*Create Deck of 52 cards with
    * one card of each face value
    * with each suit
    */
    Deck();
    
    /*Create Deck of 52 cards with
    * one card of each face value
    * with each suit for numDecks decks
    */
    Deck(int numDecks);
		
    
    ~Deck();
    
    /*Pushes a new Card onto the Deck
    * takes a Card pointer
    * returns nothing
    */
    void addCard(Card*);
    
    /*Gets a Card from the Deck
    * takes nothing
    * returns a pointer to a Card in the Deck
    */
    Card* getCard();
    
    int size();
    
    void shuffle();

  private:
    std::vector<Card*> cards; //accessed to distribute cards.

};

#endif
