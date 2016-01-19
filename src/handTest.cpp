#include "Player.h"
#include "Deck.h"
#include <string>

int main(){
  Player player;
	Deck deck;
	player.addCard(deck.getCard());
	player.displayHand();
  return 0;
}
