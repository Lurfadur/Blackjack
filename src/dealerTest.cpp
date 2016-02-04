#include "Dealer.h"
#include "Deck.h"

int main(){
  Dealer* d = new Dealer();
  Deck newDeck;
                                                              
  std::cout << "Card Count: " << newDeck.size() << std::endl;
  std::cout << "Shuffling... " << std::endl;
  newDeck.shuffle();

  d->addCard(newDeck.getCard());
  d->addCard(newDeck.getCard());
  d->addCard(newDeck.getCard());

  d->displayHand();

  d->revealHand();
  std::cout << "Hand sum: " << d->getHandSum() << std::endl;

}
