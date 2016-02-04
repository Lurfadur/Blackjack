#include "Hand.h"

class Player{
  public:
    Player(int bankAmount);
    Player(Player*);
		Player();
    void addCard(Card*);
		int getBank();
		void updateBank(int);
		void addBet(int);
    int getBet();
    void push();
    void insure();
    void winBet(double mult);
    void winInsure();
    void loseBet();
    void printStatus();
    void unsplit();

		//Hand helper functions
		void displayHand();
		int getHandSum();
		int getHandCount();
		void discard(Card*);
		void discard(int);
		int getCardValue(int index);
		Card* getCard(int index);
  protected:
    Player* parent = NULL;//used for keeping track of split hands
    Hand hand; //
  private:
    int bank;	//Used to hold amount of player money
    int bet;	//amount taken from bank in bet()
    int sideBet;	//used in insure()
};
