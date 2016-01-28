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
