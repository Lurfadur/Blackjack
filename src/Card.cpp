#include "Card.h"
#include <string>
#include <iostream>
#include <iomanip>

/*Card class creator
* assign card value, face value, and suit
* takes int newValue, string newFace_value, string newSuit
* returns Card class
*/
Card::Card(int newValue, std::string newFace_value, std::string newSuit){
  value = newValue;
  face_value = newFace_value;
  suit = newSuit;
}

/*Display Card
* display the face-value of the card using cout
* use face_value in this function
*/
void Card::display(){
  std::cout << face_value;
	if(face_value != "10"){
	 	std::cout << " ";
	}
	std::cout << suit;
}

/*Get the value of a Card, which is private
* takes nothing
* returns int
*/
int Card::getValue(){
  return value;
}

/*Set the value of a Card, which is private
* used for changing the value of Ace card from 11 to 1
* takes int newValue
* returns nothing
*/
void Card::setValue(int newValue){
	value = newValue; //value assigned newValue
}

/*Get the face-value of a Card, which is private
* takes nothing
* returns string of Card.face_value
*/
std::string Card::getFace_value(){
	return face_value;
}

/*Get the suit of a Card, which is private
* takes nothing
* returns string of Card.suit
*/
std::string Card::getSuit(){
	return suit;
}

/*Chec the return values of getFace_value, getSuit and getValue
* takes nothing
* returns nothing
*/
void Card::card_getCheck(){
	int testVal = this->getValue();
	std::string testFace = this->getFace_value();
	std::string testSuit = this->getSuit();
	if (testVal < 1 || testVal > 11){
		std::cout << "Error with card value\n";
		exit(1);
	}
	if (testFace != "A" ||
		testFace != "1" ||
		testFace != "2" ||
		testFace != "3" ||
		testFace != "4" ||
		testFace != "5" ||
		testFace != "6" ||
		testFace != "7" ||
		testFace != "8" ||
		testFace != "9" ||
		testFace != "10" ||
		testFace != "J" ||
		testFace != "Q" ||
		testFace != "K"){
			std::cout << "Error with card face-value\n";
			exit(1);
	}
	if (testSuit != u8"♠" || testSuit != u8"♥" || testSuit != u8"♣" || testSuit != u8"♦"){
		std::cout << "Error with card suit-value\n";
		exit(1);
	}

}