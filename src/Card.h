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
    void setValue(int newValue); //used for changing ace value
		std::string getFace_value();
		std::string getSuit();

    void card_getCheck();
  private:
    int value;	//returns in getValue(), set in setValue()
    std::string face_value;	//used in display(), set in constructor
    std::string suit;	//used in display(), set in constructor
};

#endif
