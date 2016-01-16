#include "Deck.h"
#include <vector>
#include "Card.h"
#include <algorithm>

    Deck::Deck(){}
    
    void Deck::addCard(Card* newCard){
      cards.push_back(newCard);
    }

    Card* Deck::getCard(){
      Card* retCard = cards.back();
      cards.pop_back();
      return retCard;
    }

    int Deck::size(){
      return cards.size();
    }

    void Deck::shuffle(){
      std::random_shuffle(cards.begin(), cards.end());
    }
