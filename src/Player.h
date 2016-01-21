#include "Hand.h"

class Player{
  public:
    Player(int bankAmount);
		Player();
    void addCard(Card*);
		int getBank();
		void updateBank(int);

		//Hand helper functions
		void displayHand();
		int getHandSum();
		int getHandCount();
		void discard(Card*);
		int getCardValue(int index);
		Card* getCard(int index);

  private:
    Hand hand;
    int bank;
    int bet;
    int sideBet;
};
