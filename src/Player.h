#include "Hand.h"

class Player{
  public:
    Player();
    void addCard(Card*);

  private:
    Hand hand;
    int bank;
    int bet;
    int sideBet;
};
