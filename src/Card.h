#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <iomanip>


class Card{
  public:
    /*Card class creator
     * assign card value, face value, and suit
     * takes int newValue, string newFace_value, string newSuit
     * returns Card class
     */
    Card(int newValue, std::string newFace_value, std::string newSuit);
    
    /*Display Card
     * display the face-value of the card using cout
     * use face_value in this function
     */
    void display();
    
    /*Get the value of a Card, which is private
     * takes nothing
     * returns int
     */
    int getValue();
    
    /*Set the value of a Card, which is private
     * used for changing the value of Ace card from 11 to 1
     * takes int newValue
     * returns nothing
     */
    void setValue(int newValue); //used for changing ace value
		
    /*Get the face-value of a Card, which is private
     * takes nothing
     * returns string of Card.face_value
     */
    std::string getFace_value();
		
    /*Get the suit of a Card, which is private
     * takes nothing
     * returns string of Card.suit
     */
    std::string getSuit();

    /*Chec the return values of getFace_value, getSuit and getValue
     * takes nothing
     * returns nothing
     */
    void card_getCheck();
  private:
    int value;	//returns in getValue(), set in setValue()
    std::string face_value;	//used in display(), set in constructor
    std::string suit;	//used in display(), set in constructor
};

#endif
