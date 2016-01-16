#include card.h

Card::Card(int newValue, char newFace_value, char newSuit){
  value = newValue;
  face_value = newFace_value;
  suit = newSuit;
}

Card::~Card(){}
