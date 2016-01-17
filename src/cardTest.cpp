#include "Card.h"
#include "Deck.h"
#include <string>

int main(){
  
  Deck newDeck;

  for(int i=0; i<4; i++){
    for(int j=0; j<13; j++){
      std::string newSuit;
      switch(i){
        case 0: newSuit = u8"♠";
          break;
        case 1: newSuit = u8"♥";
          break;
        case 2: newSuit = u8"♣";
          break;
        case 3: newSuit = u8"♦";
        break;
        default: newSuit = "E";
      }
      
      int newValue;
      std::string newFValue;
      switch(j){
        case 0:
          newValue = 11;
          newFValue = "A";
          break;
        case 1:
          newValue = 2;
          newFValue = "2";
          break;
        case 2:
          newValue = 3;
          newFValue = "3";
          break;
        case 3:
          newValue = 4;
          newFValue = "4";
          break;
        case 4:
          newValue = 5;
          newFValue = "5";
          break;
        case 5:
          newValue = 6;
          newFValue = "6";
          break;
        case 6:
          newValue = 7;
          newFValue = "7";
          break;
        case 7:
          newValue = 8;
          newFValue = "8";
          break;
        case 8:
          newValue = 9;
          newFValue = "9";
          break;
        case 9:
          newValue = 10;
          newFValue = "10";
          break;
        case 10:
          newValue = 10;
          newFValue = "J";
          break;
        case 11:
          newValue = 10;
          newFValue = "Q";
          break;
        case 12:
          newValue = 10;
          newFValue = "K";
          break;
        default:
          newValue = 0;
          newFValue = "E";
      }

      Card* newCard = new Card(newValue, newFValue, newSuit);
      newDeck.addCard(newCard);
      newCard->display();
    
    }
  }
  std::cout << "Card Count: " << newDeck.size() << std::endl;
  std::cout << "Shuffling... " << std::endl;
  newDeck.shuffle();
  for(int i=newDeck.size(); i>0; i--){
   std::cout << i << " ";
   Card* c = newDeck.getCard();
   c->display();
   delete(c);
  }
  std::cout << "Card Count: " << newDeck.size() << std::endl;
  return 0;
}
