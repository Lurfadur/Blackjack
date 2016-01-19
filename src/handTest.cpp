#include "Player.h"
#include "Deck.h"
#include <string>
#include <iostream>
#include <algorithm> // std::random_shuffle
#include <random> //std::default_random_engine
#include <chrono> //std::chrono::system_clock

using std::cout;
using std::endl;


int main(){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//each Hand can hold a max of 7 cards
	std::uniform_int_distribution<int> distribution(1,7);
  auto engine = std::default_random_engine(seed);
	int numDealCards = distribution(engine);

  Player player;
	Deck deck;
	deck.shuffle();
	//for (int i=0; i< numDealCards; i++){
	//	player.addCard(deck.getCard());
	//}
	
	Card* card1 = new Card(11, "A", "♠");
	Card* card2 = new Card(9, "9", "♠");
	Card* card3 = new Card(11, "A", "♥");
	Card* card4 = new Card(2, "2", "♥");
	Card* card5 = new Card(10, "k", "♥");
	
	player.addCard(card1);
	player.addCard(card2);
	player.addCard(card3);
	player.addCard(card4);
	player.addCard(card5);

	player.displayHand();
	
	cout << "Card Sum: ";
	cout << player.getHandSum();
	cout << endl;

	cout << "Card Count: ";
	cout << player.getHandCount();
	cout << endl;

	cout << "Card Values: ";
	for(int i=0; i<player.getHandCount(); i++){
		cout << player.getCardValue(i) << " ";	
	}
	cout << endl;

  return 0;
}
