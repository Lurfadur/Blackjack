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
		int getSum();
		int getCardValue(int index);
  private:
    std::vector<Card*> cards;
};
