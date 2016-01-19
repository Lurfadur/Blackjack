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

void Player::displayHand(){
	hand.displayHand();
}

//Hand hand;
//int bank;
//int bet;
//int sideBet;
