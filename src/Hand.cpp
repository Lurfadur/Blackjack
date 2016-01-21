#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"

class Player;

using std::cout;
using std::endl;
using std::string;

Hand::Hand(){};
Hand::~Hand(){
	for(int i=0; i<cards.size(); i++){
		delete cards[i];
	}
}
void Hand::displayHand(){
		for(int line = 0; line < 3; line++){
			for(int i=0; i<cards.size(); i++){
				string s = cards[i]->getSuit();
				string f = cards[i]->getFace_value();
				switch(line){
					case 0:
						cout << "----- ";
						break;
					case 1:
						cout << "-";
						cards[i]->display();
						cout << "- ";
						break;
					case 2:
						cout << "----- ";
				}
			}
		cout << endl;
		}
}

int Hand::cardCount(){
  return cards.size();
}

void Hand::addCard(Card* newCard){
    cards.push_back(newCard);
}

void Hand::discard(Card* dis){
  delete(dis);
}

int Hand::getSum(){
	int retSum = 0;
	int aceCount = 0;
	//Get the raw sum
	for(int i=0; i<cards.size(); i++){
		if(cards[i]->getFace_value()=="A"){
			aceCount++;
		}
		retSum += cards[i]->getValue();
	}

	//check if ace==11 and sum > 21
	while(retSum > 21 && aceCount != 0){
		for(int i=0; i<cards.size(); i++){
			if(cards[i]->getFace_value()=="A"){
				aceCount--;
				if(retSum > 21){
					if(cards[i]->getValue() == 11){
						cards[i]->setValue(1);
						retSum -= 10;
					}
				}
			}
		}
	}


	return retSum;
}

int Hand::getCardValue(int index){
	return cards[index]->getValue();
}


