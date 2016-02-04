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
    
    /* Deck destructor
    * deletes any cards from the 
    *deck
    */
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
    
    /*Size method for Deck
    * returns an integer of the
    *number of cards in the deck
    */
    int size();
    
    /*Deck shuffle method
    * takes and returns nothing
    * shuffles the deck with a random distribution
    * based on the system time
    */
    void shuffle();

  private:
    std::vector<Card*> cards; //accessed to distribute cards.

};

#endif
