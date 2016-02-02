#include "Player.h"
#include <iomanip>
#include <math.h>

using std::cout;
using std::endl;

/*Create a Player class
* takes int bankAmount
* returns initialized Player class
*/
Player::Player(int bankAmount){
  if(bankAmount < 0){
    bankAmount *= -1;
  }
  bank = bankAmount;
  bet = 0;
  sideBet = 0;
  parent = NULL;
}

/*
* Create a Player
* takes a parent player and Bet
* useful for initializing split players
* returns an initialized Player with an empty bank
* gives new player a bet that is subtracted from the 
* parent bank and equal to the original bet
*/
Player::Player(Player* pPlayer){
  bank = 0;
  sideBet = 0;
  if(pPlayer->parent == NULL){
    parent = pPlayer;
  }else{
    parent = pPlayer->parent;
  }
  
  //get parent bet amount
  bet = pPlayer->getBet();
  //subtract bet amount from parent
  pPlayer->updateBank(bet * -1);
  
  //get card from parent
  if(pPlayer->getHandCount() != 0){
    hand.addCard(pPlayer->getCard(0));
  }
}

/*Default Plkayer creation
* takes nothing
* returns initialized Player class
*/
Player::Player(){
	bank = 1000;
	bet = 0;
	sideBet = 0;
  parent = NULL;
}

void Player::unsplit(){
  if(parent != NULL){
    //add child bank back to parent
    parent->updateBank(getBank());
    //erase child player bank
    updateBank(getBank() * -1);
  }
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

void Player::push(){
  winBet(1); 
}

void Player::insure(){
  if (bank >= floor(bet/2)){
    sideBet = floor(bet/2);
    updateBank(sideBet*-1);
  }else{
    cout << "Not enough bank to insure" << endl;
  }
}

void Player::winInsure(){
  updateBank(sideBet*2);
  addBet(0);
  sideBet = 0;
}

void Player::addBet(int amount){
    if(amount <= bank){
      if(amount >= 0){
        bet = amount;
        updateBank(amount * -1);
      }else{
        std::cout << "Bet cannot be negative\n";
      }
    }else{
      std::cout << "Bet excedes bank\n";
    }
}

void Player::winBet(double mult){
  updateBank(floor(bet*mult));
  bet = 0;
}

void Player::loseBet(){

}

int Player::getBet(){
  return bet;
}

void Player::printStatus(){
  hand.displayHand();
  std::cout << "Bank: " << bank << std::setw(20) << "bet: " << bet << std::setw(40) << "Insurance: " << sideBet << std::endl;
}

///////////////Hand helper methods////////////////


/*Function to add a card to Player Hand
* takes a pointer to Card object
* returns nothing
*/
void Player::addCard(Card* newCard){
  hand.addCard(newCard);
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
	return hand.cardCount();
}

/*Get the sum of a Player's Hand, which is private
* takes nothing
* returns int
*/
int Player::getHandSum(){
	return hand.getSum();
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

