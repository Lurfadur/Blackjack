#include "Player.h"

class Dealer:public Player{
  public:
    Dealer();
    /*
    *Displays the dealer's hand with the
    *hole card face down
    */
    void revealHand();

    /*
    *Dispalys the dealers hand with the
    *hole card face up
    */
    void displayHand();

};
