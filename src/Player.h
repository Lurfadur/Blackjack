#include "Hand.h"

class Player{
  public:
    Player(int bankAmount);
		Player();
    void addCard(Card*);
		int getBank();
		void updateBank(int);
		//void bet(int);
		//void insure();

		//Hand helper functions
		void displayHand();
		int getHandSum();
		int getHandCount();
		void discard(Card*);
		void discard(int);
		int getCardValue(int index);
		Card* getCard(int index);

  private:
    Hand hand; //
    int bank;	//Used to hold amount of player money
    int bet;	//amount taken from bank in bet()
    int sideBet;	//used in insure()
};
