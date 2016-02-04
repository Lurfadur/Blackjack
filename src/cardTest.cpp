#include "Card.h"
#include "Deck.h"
#include <string>

int main(){
  
  Deck newDeck(3);
 
  std::cout << "Card Count: " << newDeck.size() << std::endl;
  std::cout << "Shuffling... " << std::endl;
  newDeck.shuffle();
  for(int i=newDeck.size(); i>0; i--){
   std::cout << i << " ";
   Card* c = newDeck.getCard();
   c->display();
   std::cout << std::endl;
   delete(c);
  }
  std::cout << "Card Count: " << newDeck.size() << std::endl;
  return 0;
}
