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
  std::cout << std::setw(3) << std::left << face_value << std::right << suit << std::endl;
}

