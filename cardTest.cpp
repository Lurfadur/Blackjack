#include "Card.h"
#include "Deck.h"

int main(){
  
  Deck newDeck;

  for(int i=0; i<4; i++){
    for(int j=0; j<13; j++){
      char newSuit;
      switch(i){
        case 0: newSuit = '♠';
          break;
        case 1: newSuit = '♥';
          break;
        case 2: newSuit = '♣';
          break;
        case 3: newSuit = '♦';
        break;
        default: newSuit = 'E';
      }
      
      int newValue;
      char newFValue;
      switch(j){
        case 0:
          newValue = 11;
          newFValue = 'A';
          break;
        case 1:
          newValue = 11;
          newFValue = 'A';
          break;
        case 2:
          newValue = 11;
          newFValue = 'A';
          break;
        case 3:
          newValue = 11;
          newFValue = 'A';
          break;
        case 4:
          newValue = 11;
          newFValue = 'A';
          break;
        case 5:
          newValue = 11;
          newFValue = 'A';
          break;
        case 6:
          newValue = 11;
          newFValue = 'A';
          break;
        case 7:
          newValue = 11;
          newFValue = 'A';
          break;
        case 8:
          newValue = 11;
          newFValue = 'A';
          break;
        case 9:
          newValue = 11;
          newFValue = 'A';
          break;
        case 10:
          newValue = 11;
          newFValue = 'A';
          break;
        case 11:
          newValue = 11;
          newFValue = 'A';
          break;
        case 12:
          newValue = 11;
          newFValue = 'A';
          break;
        default:
          newValue = 0;
          newFValue = 'E';
      }

      //Card* newCard = new Card(newValue, newFValue, newSuit);

    }
  }
  return 0;
}
