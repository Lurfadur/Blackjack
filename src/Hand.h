#include <vector>
#include "Card.h"

class Hand{
  public:
		Hand();
		~Hand();
    void displayHand();
    void displayDealerHand();
    int cardCount();
    void addCard(Card*);
    void discard(Card*);
    void discard(int);
    void checkLength(int);
		int getSum();
		int getCardValue(int index);
		Card* getCard(int index);
    
  private:
    std::vector<Card*> cards; //accessed to hold cards and distribute cards on split
};
