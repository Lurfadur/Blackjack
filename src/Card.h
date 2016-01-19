#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <iomanip>


class Card{
  public:
    Card(int newValue, std::string newFace_value, std::string newSuit);
    void display();
    int getValue();
  private:
    int value;
    std::string face_value;
    std::string suit;
};

#endif
