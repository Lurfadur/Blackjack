// Main file for Blackjack

#include "Deck.h"
#include "Player.h"
#include <iostream>
#include <algorithm> // std::random_shuffle
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
using namespace std;

/* Methods for testing and checking*/

#define NUM_CARDS 52 // Constant for the number of cards in a deck
#define BLACKJACK 21 // Constant for the number for Blackjack

// method to check bank amount when splitting that bank is >= to bet 
bool hand_sumCheck(Hand *);
bool deck_creationCheck(Deck *); // done
bool deck_lengthCheck(Deck *, int oldLength); //done

bool player_createCheck(Player *); // done
bool player_checkTotals(Player *); // checks bank, insurance, and bet

/* Methods for controlling game*/

void hit(vector<Player *> players, vector<Deck *> &decks);
bool shuffle_check(vector<Player *> players, vector<Deck *> decks); // done

void deck_create(vector<Deck *> &decks); // done
void deck_delete(vector<Deck *> &decks);
void player_create(vector<Player *> &players); // done

void deal(vector<Player *> players, vector<Deck *> &decks);
bool check_victory(vector<Player *> players);
void split(vector<Player *> &players, vector<Deck *> &decks);


int main(int argc, char **argv){
	
	// Variable and vector declaration and assignment
	vector<Player *> players;
	vector<Deck *> decks;

	int playerCount = 2; // update to get number of players from argv, set to 2 for default
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // create seed for random number creation
	auto engine = std::default_random_engine(seed); // engine for random creatoin, seed is used here
	std::uniform_int_distribution<int> distribution(1,7); // each hand must have between at least 1 card and a maximum of 7 cards
	int numDealCards = distribution(engine); // random number used to get card from vector

	// Deck and Player creation
	for(int i = 0; i < playerCount; i++){ // playerCount used for loop bounds
		player_create(players); // players vector used 
		deck_create(decks); // decks vector used
		
		if(!player_createCheck(players[i])){
			cout << "ERROR: error in player creation, exiting program" << endl;
			exit(1);
		}

		if(!deck_creationCheck(decks[i])){
			cout << "ERROR: error in deck creation, exiting program" << endl;
			exit(1);
		}

	}

	/*shuffle the decks*/
	for(int i = 0; i < decks.size(); i++){
		decks[i]->shuffle();
	}

	/* Master loop to run the game, if check_victory is false then continue loop
	*
	*/
	while(!check_victory(players)){
		
	}
} //end main(

// Method to create a new player, checks if new worked correctly
void player_create(vector<Player *> &players){
	Player * newPlayer = new Player(); // Need to pass bank ammount, or default is 1000
	if(newPlayer == NULL){ // error checking
		cout << "ERROR: error in assigning memory to new Player, exiting program" << endl;
		exit(1);
	}
	players.push_back(newPlayer);
}

// Method to create a new deck, checks if new worked correctly
void deck_create(vector<Deck *> &decks){
	Deck * newDeck = new Deck(); // create a new Deck object
	if(newDeck == NULL){ // error checking 
		cout << "ERROR: error in assigning memory to new Deck, exiting program" << endl;
		exit(1);
	}
	decks.push_back(newDeck);
}

// Check to see if player has been created correctly
bool player_createCheck(Player *player){
	bool retVal = true; // declare return value, assign value to true
	if(player->getBank() <= 0){
		retVal = false; // change return value to false if player's bank is less than or equal to 0
	}
	return retVal; // return bool value of retVal
}

// Checks to see if a deck has 52 cards in it
bool deck_creationCheck(Deck *deck){
	bool retVal = true; // declare return value, assign value to true
	if(deck->size() != NUM_CARDS){
		retVal = false; // change return value if the number of cards in a deck is not equal to NUM_CARDS (52)
	}
	return retVal; // return bool value of retVal
}

// Checks if deck length is one less after deal
bool deck_lengthCheck(Deck *deck, int oldLength){
	bool retVal = true; // declare return value, assign value to true
	if((oldLength - deck->size()) != 1){ // oldLength used for compare
		retVal = false; // change return value if the size of the new deck is not 1 less than the old size
	}
	return retVal; // return bool value of retVal
}

// Method to check if decks to need to be remade and shuffled
bool shuffle_check(vector<Player *> players, vector<Deck *> decks){
	// Formula: (28 * decks.size()) * (players.size() - 1)	
	bool retVal = false; // declare return value, assign value to false
	int formula = (28 * decks.size()) * (players.size() - 1); // int formula uses deck.size() and players.size() values
	int cardSum = 0; // declare and assign cardSum
	for(int i = 0; i < decks.size(); i++){
		cardSum += decks[i]->size(); // cardSum value changed
	}
	if(cardSum < formula){
		retVal = true; // change return value if cardSum is less than formula, deck needs to be shuffled 
	}	
	return retVal; // return bool value of retVal
}

// Method to check if game loop should continue
bool check_victory(vector<Player *> players){
	bool retVal = true; // true to avoid infinite loop in main, change to fasle later ***********************
	for(int i = 0; i < players.size(); i++){
		if(players[i]->getHandSum() >= BLACKJACK){ // BLACKJACK used to compare hand sums of players
			retVal = true; // victory condition found = Blackjack
		}
		
	}
	for(int i = 1; i < players.size(); i++){
		if(players[i]->getBank() <= 0){
			retVal = true; // victory condition found = bank is zero
		}
	}
	return retVal; // return bool value of retVal
}

