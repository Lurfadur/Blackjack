#include <vector>
#include "Hand.h"
#include "Player.h"
#include "Card.h"

void Hand::displayHand();

int Hand::cardCount(){
  int sum = 0;
  for(int i=0; i<cards.size(); i++){
    sum = cards[i]->getValue();
  }
  return sum;
}

void Hand::addCard(Card* newCard){
    cards.push_back(newCard);
}

void Hand::discard(Card* dis){
  delete(dis);
}

