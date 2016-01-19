#include "Hand.h"

class Player{
  public:
    Player();
    void addCard(Card*);
		void displayHand();

  private:
    Hand hand;
    int bank;
    int bet;
    int sideBet;
};
