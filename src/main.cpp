// Main file for Blackjack

#include "Deck.h"
#include "Player.h"
using namespace std;
// Methods for testing and checking

#define NUM_CARDS 52
#define BLACKJACK 21

bool card_getCheck(Card *);
bool card_createCheck(Card *);

bool hand_sumCheck(Hand *);
bool hand_lengthCheck(Hand *, int oldLength);

bool deck_creationCheck(Deck *); // done
bool deck_lengthCheck(Deck *, int oldLength);

bool player_createCheck(Player *); // done
bool player_checkTotals(Player *); // checks bank, insurance, and bet

// Methods for controlling game
void hit(vector<Player *> players, vector<Deck *> &decks);
bool shuffle_check(vector<Player *> players, vector<Deck *> decks); // done
void deck_create(vector<Deck *> &decks); // done
void deck_delete(vector<Deck *> &decks);
void deal(vector<Player *> players, vector<Deck *> &decks);
void player_create(vector<Player *> &players); // done
bool check_victory(vector<Player *> players);
void split(vector<Player *> &players, vector<Deck *> &decks);

int main(int argc, char **argv){
	
	// Variable and vector setup
	vector<Player *> players;
	vector<Deck *> decks;
	int playerCount = 2; // use argv to get number of players
	
	// Deck and Player creation
	for(int i = 0; i < playerCount; i++){
		player_create(players);
		deck_create(decks);
		
		if(!player_createCheck(players[i])){
			cout << "ERROR: error in player creation, exiting program" << endl;
			exit(1);
		}

		if(!deck_creationCheck(decks[i])){
			cout << "ERROR: error in deck creation, exiting program" << endl;
			exit(1);
		}
	}

	// Master loop to run the game, if check_victory is false then continue loop
	while(!check_victory(players)){
		
		
	}
}

// Method to create a new player, checks if new worked correctly
void player_create(vector<Player *> &players){
	Player * newPlayer = new Player(); // Need to pass bank ammount, or default is 1000
	if(newPlayer == NULL){
		cout << "ERROR: error in assigning memory to new Player, exiting program" << endl;
		exit(1);
	}
	players.push_back(newPlayer);
}

// Method to create a new deck, checks if new worked correctly
void deck_create(vector<Deck *> &decks){
	Deck * newDeck = new Deck();
	if(newDeck == NULL){
		cout << "ERROR: error in assigning memory to new Deck, exiting program" << endl;
		exit(1);
	}
	decks.push_back(newDeck);
}

// Check to see if player has been created correctly
bool player_createCheck(Player *player){
	bool retVal = true;
	if(player->getBank() <= 0){
		retVal = false;
	}
	return retVal;
}

// Checks to see if a deck has 52 cards in it
bool deck_creationCheck(Deck *deck){
	bool retVal = true;
	if(deck->size() != NUM_CARDS){
		retVal = false;
	}
	return retVal;
}

// Method to check if decks to need to be remade and shuffled
bool shuffle_check(vector<Player *> players, vector<Deck *> decks){
	// Formula: (28 * decks.size()) * (players.size() - 1)	
	bool retVal = false;
	int formula = (28 * decks.size()) * (players.size() - 1);
	int cardSum = 0;
	for(int i = 0; i < decks.size(); i++){
		cardSum += decks[i]->size();
	}
	if(cardSum < formula){
		retVal = true;
	}	
	return retVal;
}

// Method to check if game loop should continue
bool check_victory(vector<Player *> players){
	bool retVal = true; // true to avoid infinite loop in main, change to fasle later
	for(int i = 0; i < players.size(); i++){
		if(players[i]->getHandSum() >= BLACKJACK){
			retVal = true; // victory condition found = Blackjack
		}
		
	}
	for(int i = 1; i < players.size(); i++){
		if(players[i]->getBank() <= 0){
			retVal = true; // victory condition found = bank is zero
		}
	}
	return retVal;
}

