#include "Dealer.h"
#include <iostream>

Dealer::Dealer(){
    parent = NULL;
}
void Dealer::displayHand(){
    hand.displayDealerHand();
}
void Dealer::revealHand(){
    std::cout << "Dealer:" << std::endl;
    hand.displayHand();
    std::cout << "Dealer's hand is: " << hand.getSum() << std::endl;
}
