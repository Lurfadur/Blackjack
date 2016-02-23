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
    value = newValue; //value assigned newValue
}

std::string Card::getFace_value(){
    return face_value;
}

std::string Card::getSuit(){
    return suit;
}

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
