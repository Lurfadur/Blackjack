#include "Player.h"
#include <iomanip>
#include <math.h>

using std::cout;
using std::endl;
using std::string;

Player::Player(int bankAmount){
  if (bankAmount < 0){
    bankAmount *= -1;
  }
  bank = bankAmount;
  bet = 0;
  sideBet = 0;
  parent = NULL;
  inRound = true;
}

Player::Player(Player* pPlayer){
  bank = 0;
  sideBet = 0;
  inRound = true;
  if (pPlayer->parent == NULL){
    parent = pPlayer;
  }
  else{
    parent = pPlayer->parent;
  }
  
  //get parent bet amount
  bet = pPlayer->getBet();
  //subtract bet amount from parent
  pPlayer->updateBank(bet * -1);
  
  //get card from parent
  if (pPlayer->getHandCount() != 0){
    hand.addCard(pPlayer->getCard(0));
  }
}

Player::Player(){
	bank = 1000;
	bet = 0;
	sideBet = 0;
  parent = NULL;
}

void Player::unsplit(){
  if (parent != NULL){
    //add child bank back to parent
    parent->updateBank(getBank());
    //erase child player bank
    updateBank(getBank() * -1);
  }
}

int Player::getBank(){
	return bank;
}

void Player::updateBank(int amount){
	bank += amount; // bank variable changed
}

void Player::push(){
  winBet(1); 
}

void Player::insure(){
  if (bank >= floor(bet/2)){
    sideBet = floor(bet/2);
    updateBank(sideBet*-1);
  }
  else{
    cout << "Not enough bank to insure" << endl;
  }
}

void Player::winInsure(){
  updateBank(sideBet*2);
  addBet(0);
  sideBet = 0;
}

void Player::addBet(int amount){
  if (amount <= bank){
     if (amount >= 0){
       bet += amount;
       updateBank(amount * -1);
     }
     else{
       std::cout << "Bet cannot be negative\n";
     }
   }
   else{
     std::cout << "Bet excedes bank\n";
   }
}

void Player::winBet(double mult){
  updateBank(floor(bet*mult)+bet);
  bet = 0;
}

void Player::loseBet(){
  bet = 0;
}

int Player::getBet(){
  return bet;
}

void Player::printStatus(){
  hand.displayHand();
  std::cout << "Bank: " << bank << std::setw(20) << "bet: " << bet << std::setw(40) << "Insurance: " << sideBet << std::endl;
}

///////////////Hand helper methods////////////////


void Player::addCard(Card* newCard){
  hand.addCard(newCard);
}

void Player::displayHand(){
	hand.displayHand();
}

int Player::getHandCount(){
	return hand.cardCount();
}

int Player::getHandSum(){
	return hand.getSum();
}

void Player::discard(Card* card){
	hand.discard(card);
}

void Player::discard(int position){
	hand.discard(position);
}

int Player::getCardValue(int index){
	return hand.getCardValue(index);
}

Card* Player::getCard(int index){
	return hand.getCard(index);
}

string Player::get_face_value(int pos){
  return hand.get_face_value(pos);
}
