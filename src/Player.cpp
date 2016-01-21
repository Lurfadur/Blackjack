#include "Player.h"

Player::Player(int bankAmount){
  bank = bankAmount;
  bet = 0;
  sideBet = 0;
}

Player::Player(){
	bank = 1000;
	bet = 0;
	sideBet = 0;
}

void Player::addCard(Card* newCard){
  hand.addCard(newCard);
}


int Player::getBank(){
	return bank;
}

void updateBank(int amount){
	bank += amount;
}


//Hand helper methods
void Player::displayHand(){
	hand.displayHand();
}

int Player::getHandCount(){
	hand.cardCount();
}

int Player::getHandSum(){
	hand.getSum();
}

void Player::discard(Card* card){
	hand.discard(card);
}

int Player::getCardValue(int index){
	return hand.getCardValue(index);
}

Card* Player::getCard(int index){
	return hand.getCard(index);
}

//Hand hand;
//int bank;
//int bet;
//int sideBet;
