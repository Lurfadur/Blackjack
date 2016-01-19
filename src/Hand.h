#include <vector>
#include "Card.h"

class Hand{
  public:
    void displayHand();
    int cardCount();
    void addCard(Card*);
    void discard(Card*);
  private:
    int sum;
    std::vector<Card*> cards;
};
