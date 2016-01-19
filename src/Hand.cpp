#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"

class Player;

using std::cout;
using std::endl;
using std::string;

void Hand::displayHand(){
		for(int i=0; i<cards.size(); i++){
			string s = cards[i]->getSuit();
			string f = cards[i]->getFace_value();
			cout << "----"
					 << "-" << s << f << "-"
					 << "----";
		}
		cout << endl;
}

int Hand::cardCount(){
  int numCards = 0;
  for(int i=0; i<cards.size(); i++){
    numCards = cards[i]->getValue();
  }
  return numCards;
}

void Hand::addCard(Card* newCard){
		sum += newCard->getValue();
    cards.push_back(newCard);
}

void Hand::discard(Card* dis){
  delete(dis);
}

