#ifndef CARD_H
#define CARD_H

class Card{
  Public:
    Card(int newValue, char newFace_value, char newSuit);
  Private:
    int value;
    char face_value;
    char suit;
};

#endif
