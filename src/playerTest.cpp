#include "Player.h"
#include "Deck.h"

using std::cout;
using std::endl;

int main(){

 //make a deck and deal to players; 
  Deck newDeck;
                                                              
  std::cout << "Card Count: " << newDeck.size() << std::endl;
  std::cout << "Shuffling... " << std::endl;
  newDeck.shuffle();
  
  Player* p = new Player(1000);

  p->addCard(newDeck.getCard());
  p->addCard(newDeck.getCard());
  
  p->addBet(15);
  cout << "Player P: \n";
  p->printStatus();
  cout << endl;

  Player* q = new Player(p);
  cout << "Player P: \n";
  p->printStatus();
  cout << endl;
  cout << "Player Q: \n";
  q->printStatus();
  cout << endl;
  
  q->push();

  cout << "push Player Q: \n";
  q->printStatus();
  cout << endl;
  q->addBet(15);
  cout << "addbet 15 Player Q: \n";
  q->printStatus();

  q->winBet(1.5);
  cout << "winbet(x1.5) Player Q: \n";
  q->printStatus();

  q->unsplit(); 
  std::cout << "after unsplit\n";
  cout << "Player P: \n";
  p->printStatus();
  cout << endl;
  cout << "Player Q: \n";
  q->printStatus();
  cout << endl;

  p->insure();
  std::cout << "insure\n";
  cout << "Player P: \n";
  p->printStatus();
  cout << endl;

  p->winInsure();
  std::cout << "win insure\n";
  cout << "Player P: \n";
  p->printStatus();
  cout << endl;
  delete(q);
  delete(p);
}
