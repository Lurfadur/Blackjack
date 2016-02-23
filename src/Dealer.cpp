#include "Dealer.h"
#include <iostream>

Dealer::Dealer(){
    parent = NULL;
}
void Dealer::displayHand(){
    hand.displayDealerHand();
}
void Dealer::revealHand(){
    hand.displayHand();
}
