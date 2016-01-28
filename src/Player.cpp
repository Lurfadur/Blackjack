#include "Player.h"

/*Create a Player class
* takes int bankAmount
* returns initialized Player class
*/
Player::Player(int bankAmount){
  bank = bankAmount;
  bet = 0;
  sideBet = 0;
}

/*Default Plkayer creation
* takes nothing
* returns initialized Player class
*/
Player::Player(){
	bank = 1000;
	bet = 0;
	sideBet = 0;
}

/*Function to add a card to Player Hand
* takes a pointer to Card object
* returns nothing
*/
void Player::addCard(Card* newCard){
  hand.addCard(newCard);
}

/*Get the Player bank, which is private
* takes nothing
* returns int 
*/
int Player::getBank(){
	return bank;
}

/*Function to update the Player bank
* takes int amount
* returns nothing
*/
void Player::updateBank(int amount){
	bank += amount; // bank variable changed
}

/*Function to display Player's Hand
* takes nothing
* returns nothing
*/
void Player::displayHand(){
	hand.displayHand();
}

/*Function to get the number of cards in a Hand, which is private
* takes nothing
* returns int
*/
int Player::getHandCount(){
	hand.cardCount();
}

/*Get the sum of a Player's Hand, which is private
* takes nothing
* returns int
*/
int Player::getHandSum(){
	hand.getSum();
}

/*Function to remove a card from Player's Hand
* takes pointer to Card object
* returns nothing
*/
void Player::discard(Card* card){
	hand.discard(card);
}

/*Function to remove a card from Player's Hand, used for split
* takes int to remove card by index
* returns nothing
*/
void Player::discard(int position){
	hand.discard(position);
}

/*Gets the value of a card in a Player's Hand
* takes int index
* returns int of card value
*/
int Player::getCardValue(int index){
	return hand.getCardValue(index);
}

/*Gets Card object from Player's Hand
* takes int index
* returns pointer of Card object
*/
Card* Player::getCard(int index){
	return hand.getCard(index);
}

//Hand hand;
//int bank;
//int bet;
//int sideBet;
