#include <vector>
#include <iostream>
#include "Hand.h"
#include "Card.h"

class Player;

using std::cout;
using std::endl;
using std::string;

/*Create Hand object
* takes nothing
* returns initialized Hand object
*/
Hand::Hand(){};
Hand::~Hand(){
	for(int i=0; i<cards.size(); i++){
		delete cards[i];
	}
}

bool discard_check(){
}

/*Function to display formated visualiztion of a Hand
* takes nothing
* returns nothing
*/
void Hand::displayHand(){
		for(int line = 0; line < 3; line++){
			for(int i=0; i<cards.size(); i++){
				switch(line){
					case 0:
						cout << "----- ";
						break;
					case 1:
						cout << "|";
						cards[i]->display();
						cout << "| ";
						break;
					case 2:
						cout << "----- ";
				}
			}
		cout << endl;
		}
}

void Hand::displayDealerHand(){
		for(int line = 0; line < 3; line++){
			for(int i=0; i<cards.size(); i++){
				switch(line){
					case 0:
						cout << "----- ";
						break;
					case 1:
						cout << "|";
            if(i==0){
              cout << "   ";
            }else{
						  cards[i]->display();
            }
						cout << "| ";
						break;
					case 2:
						cout << "----- ";
				}
			}
		cout << endl;
		}

}

/*Get the number of cards in Hand, which is private
* takes nothing
* returns int
*/
int Hand::cardCount(){
  return cards.size();
}

/*Function to add a card to a Hand
* takes pointer to Card object
* returns nothing
*/
void Hand::addCard(Card* newCard){
    cards.push_back(newCard);
}

/*Checks hand length after removing a card form the hand
* takes int
* returns nothing
*/
void Hand::checkLength(int oldVal){
	if (oldVal <= 0){
		cout << "Error with hand length, shoudl be more than 0\n";
		exit(1);
	}
	if ((oldVal - this->cardCount()) != 1){
		cout << "Error removing card from the hand\n";
		exit(1);
	}

}

/*Function to remove Card from a Hand
* takes pointer to Card object to remove
* returns nothing
*/
void Hand::discard(Card* dis){
	/*look for card in hand*/
	for (int i=0; i<cards.size(); i++){
		if (cards[i] == dis){
			int oldVal = this->cardCount(); // hand length
			cards.erase(cards.begin()+i);
			this->checkLength(oldVal); // oldVal passed here
		}
	}
}

/*Function to remove Card from Hand based on index
* takes int position
* returns nothing
*/
void Hand::discard(int position){
	if(position >=0 && position <=cards.size()){
		int oldVal = this->cardCount(); // hand length
		cards.erase(cards.begin()+position);
		this->checkLength(oldVal); // oldVal passed here
	}
}

/*Get the sum of cards in a Hand
* takes nothing
* returns int
*/
int Hand::getSum(){
	/*Declare variables*/
	int retSum = 0;
	int aceCount = 0;
	//Get the raw sum
	for(int i=0; i<cards.size(); i++){
		if(cards[i]->getFace_value()=="A"){
			aceCount++;
		}
		retSum += cards[i]->getValue(); //value assigned to retSum
	}

	//check if ace==11 and sum > 21
	while(retSum > 21 && aceCount != 0){
		for(int i=0; i<cards.size(); i++){
			if(cards[i]->getFace_value()=="A"){
				aceCount--; //value changed by -1 for aceCount
				if(retSum > 21){
					if(cards[i]->getValue() == 11){
						cards[i]->setValue(1);
						retSum -= 10; //retSum changed by subtracting 10
					}
				}
			}
		}
	}
	return retSum;
}

/*Get value of a Card
* takes int index
* returs int 
*/
int Hand::getCardValue(int index){
	return cards[index]->getValue();
}

/*Get Card in a Hand
* takes int index
* returns pointer to Card object
*/
Card* Hand::getCard(int index){
	if(index < cards.size() && index >= 0){
    Card* givenCard = cards[index];
	  cards.erase(cards.begin()+index);
    return givenCard;
  }else{
		return NULL;
	}
}
