#include "Card.h"
#include <string>
#include <iostream>
#include <iomanip>

Card::Card(int newValue, std::string newFace_value, std::string newSuit){
  value = newValue;
  face_value = newFace_value;
  suit = newSuit;
}

void Card::display(){
  std::cout << face_value;
	if(face_value != "10"){
	 	std::cout << " ";
	}
	std::cout << suit;
}

int Card::getValue(){
  return value;
}

void Card::setValue(int newValue){
	value = newValue;
}

std::string Card::getFace_value(){
	return face_value;
}
std::string Card::getSuit(){
	return suit;
}
