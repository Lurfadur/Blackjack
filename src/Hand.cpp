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

/*Function to display formated visualiztion of a Hand
* takes nothing
* returns nothing
*/
void Hand::displayHand(){
		for(int line = 0; line < 3; line++){
			for(int i=0; i<cards.size(); i++){

				/*Strings not needed?*/
				//string s = cards[i]->getSuit();
				//string f = cards[i]->getFace_value();
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

/*Function to remove Card from a Hand
* takes pointer to Card object to remove
* returns nothing
*/
void Hand::discard(Card* dis){
	for(int i=0; i<cards.size(); i++){
		if(cards[i] == dis){
			cards.erase(cards.begin()+i);
		}
	}
}

/*Function to remove Card from Hand based on index
* takes int position
* returns nothing
*/
void Hand::discard(int position){
	if(position >=0 && position <=cards.size()){
		cards.erase(cards.begin()+position);
	}
}

/*Get the sum of cards in a Hand
* takes nothing
* returns nothing
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
		return cards[index];
	}else{
		return NULL;
	}
}
