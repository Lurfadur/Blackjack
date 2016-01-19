#include "Player.h"

#define INIT_BANK_AMOUNT 1000


Player::Player(){
  bank = INIT_BANK_AMOUNT;
  bet = 0;
  sideBet = 0;
}

void Player::addCard(Card* newCard){
  hand.addCard(newCard);
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

int Player::getCardValue(int index){
	return hand.getCardValue(index);
}

//Hand hand;
//int bank;
//int bet;
//int sideBet;
