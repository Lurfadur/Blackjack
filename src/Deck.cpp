#include "Deck.h"
#include <vector>
#include "Card.h"
#include <algorithm> // std::random_shuffle
#include <random> //std::default_random_engine
#include <chrono> //std::chrono::system_clock

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
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      auto engine = std::default_random_engine(seed);
      std::shuffle(cards.begin(), cards.end(), engine);
    }
