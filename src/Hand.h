#include <vector>
#include "Card.h"

class Hand{
  public:
		Hand();
		~Hand();
    void displayHand();
    int cardCount();
    void addCard(Card*);
    void discard(Card*);
    void discard(int);
		int getSum();
		int getCardValue(int index);
		Card* getCard(int index);
  private:
    std::vector<Card*> cards;
};
