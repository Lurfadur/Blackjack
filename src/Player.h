#include "Hand.h"

class Player{
  public:
    Player();
    void addCard(Card*);

		//Hand helper functions
		void displayHand();
		int getHandSum();
		int getHandCount();
		int getCardValue(int index);

  private:
    Hand hand;
    int bank;
    int bet;
    int sideBet;
};
