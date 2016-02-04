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
bool deck_creationCheck(Deck *); // done
bool deck_lengthCheck(Deck *, int oldLength); //done

bool player_createCheck(Player *); // done
bool player_checkTotals(Player *); // NOT DONE checks bank, insurance, and bet

/* Methods for controlling game*/

void hit(vector<Player *> players, vector<Deck *> &decks);
bool shuffle_check(vector<Player *> players, vector<Deck *> decks); // done

void deck_create(vector<Deck *> &decks); // done
void deck_delete(vector<Deck *> &decks);
void player_create(vector<Player *> &players); // done

void deal(vector<Player *> players, vector<Deck *> &decks);
bool check_victory(vector<Player *> players); // done
void split(vector<Player *> &players, vector<Deck *> &decks);

void display_hand(Player *);
int player_choice(Player *);
bool check_banks(vector<Player *> &players);


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

	/* Master loop to run the game
	*
	*/
	// deal initial cards

	while (check_banks()){ // check if players are still in game
		// ask each player bet, stand, or surrender if handSum() != BLACKJACK, exclude dealer
		for (int i = 1; i < players.size(); i++){
			if(players[i]->endRound){ // player is still playing this round
				cout << "Player " << i << " hand" << endl;
				display_hand(players[i]);
				int playerInput = player_choice(players[i]);				
			}
			else{
				cout << "Player " << i << " is out this turn." << endl;
			}

			
		}
		// deal cards
		// check for insurance


	}
} //end main

// Method to display player options and get their choice
int player_choice(Player *player){
	cout << "Select: (1) Hit\n(2) Stand\n(3) Surrender" << endl;
	
}

// Check to see if there are any remaining players able to play
bool check_banks(vector<Player *> &players){
	bool retVal = false; // assume no players are able to play
	for (int i = 0; i < players.size(); i++){
		if (players[i]->getBank() > 0){
			retVal = true; // if player still has money in their bank, set to true
		}
	}
	return retVal;
}

// Method to dispaly a player's hand
void display_hand(Player *player){
	player->displayHand();
	cout << "Hand sum: " << player->getHandSum() << endl;
	cout << "Card count: " << player->getHandCount() << endl;
	cout << "Card values: ";
	for(int i = 0; i < player->getHandCount(); i++){
		cout << player->getCardValue(i) << " ";
	}
	cout << endl;
}

// Function to check victory conditions
bool check_victory(vector<Player *> players){
	bool retVal = false; // return value set to false by default

	// If players and dealer have Blackjack, then push
	// Dealer is players[0]
	for(int i = 1; i < players.size(); i++){
		if (players[0]->getHandSum() == BLACKJACK && players[i]->getHandSum() == BLACKJACK){
			players[i]->push();
			retVal = true;
		}
	}
	if (retVal)
		return retVal; // victory condition found, leave method

	for(int i = 1; i < players.size(); i++){
		// Player has Blackjack and dealer does not, player wins
		if (players[i]->getHandSum() == BLACKJACK && players[0]->getHandSum() != BLACKJACK){
			players[i]->winBet(1.5);
			retVal = true;
		}
		// Player does not have Blackjack and dealer does, player loses bet
		else if (players[i]->getHandSum() != BLACKJACK && players[0]->getHandSum() == BLACKJACK){
			players[i]->loseBet();
			retVal = true;
		}
	}
	if (retVal)
		return retVal; // victory condition found, leave method

	/*If none of the above win conditions are found, return false*/
	return retVal; // victory condition not found, leave method 
}

// Method to create a new player, checks if new worked correctly
void player_create(vector<Player *> &players){
	Player * newPlayer = new Player(); // Need to pass bank ammount, or default is 1000
	if (newPlayer == NULL){ // error checking
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

