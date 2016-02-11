// Main file for Blackjack
#include "Deck.h"
#include "Dealer.h"
//#include <iostream>
using namespace std;

/* Methods for testing and checking*/
#define NUM_CARDS 52 // Constant for the number of cards in a deck
#define BLACKJACK 21 // Constant for the number for Blackjack
#define SURRENDER_AMOUNT 0.5 // Constant for the amount to be multiplied to the player's bet when doing a surrender
#define DEALER_HIT 16 // Constant for when the dealer must hit

// method to check bank amount when splitting that bank is >= to bet 
//bool deck_creationCheck(Deck *); // done
bool deck_lengthCheck(Deck &, int oldLength); //done

bool player_createCheck(Player *); // done
//bool player_checkTotals(Player *); // NOT DONE checks bank, insurance, and bet

/* Methods for controlling game*/
void hit(Player *player, Deck &); // done
bool shuffle_check(vector<Player *> &players, Deck &); // done

//void deck_create(vector<Deck *> &decks); // done
void player_create(vector<Player *> &players); // done

void check_victory(vector<Player *> &players, Dealer *); // done
void split(vector<Player *> &players, Deck &);
void player_surrender(Player *); // done
void player_doubleDown(Player *, Deck &); // done
void player_split(vector<Player *> &players, Player *, Deck &); // done

int player_choice(Player *, Dealer *); // done
bool check_banks(vector<Player *> &players); // done

int main(int argc, char **argv){
	
	// Variable and vector declaration and assignment
	vector<Player *> players;
	//vector<Deck *> decks; // in future, use multideck creation built in to Deck class
	
	Dealer *dealer = new Dealer();
	if (dealer == NULL){ // check dealer for NULL value
		cout << "ERROR: error in dealer creation, exiting program" << endl;
		exit(1);
	}
	
	int playerCount = 1; // update to get number of players from argv, set to 1 for default
	Deck decks(playerCount + 1);

	// Deck and Player creation
	for (int i = 0; i < playerCount; i++){ // playerCount used for loop bounds
		player_create(players); // players vector used 
		//deck_create(decks); // decks vector used
		
		if (!player_createCheck(players[i])){
			cout << "ERROR: error in player creation, exiting program" << endl;
			exit(1);
		}

		/*
		if (!deck_creationCheck(decks[i])){
			cout << "ERROR: error in deck creation, exiting program" << endl;
			exit(1);
		}
		*/
	}

	/*shuffle the decks
	for (int i = 0; i < decks.size(); i++){
		decks[i]->shuffle();
	}
	*/
	mainDeck.shuffle();

	/* Master loop to run the game
	*/
	cout << endl << "Welcome to K&G Blackjack!" << endl << "Press CTRL + C to quit the game." << endl;
	int roundNumber = 1; // number of rounds played
	while (check_banks(players)){ // check if players are still in game
		cout << "Round number: " << roundNumber << endl;
		roundNumber++; // increment roundNumber by 1

		// check to see if decks need to be remade
		if (shuffle_check(players, decks)){
			decks.reshuffle(playerCount + 1);
			cout << "Remaking the decks..." << endl;
		}

		// dealer gets 2 cards
		dealer->addCard(decks.getCard());
		dealer->addCard(decks.getCard());

		// ask players to bet, deal 2 cards to each
		for (int i = 0; i < players.size(); i++){	
			bool loopBreak = false; // bool used to break while-loop
			while (!loopBreak){
				cout << "Place a bet between 1 and " << players[i]->getBank() << ": ";
				int betAmount; // int amount for player bet
				cin >> betAmount;

				if (betAmount <= players[i]->getBank() && betAmount > 0 && cin){
					loopBreak = true; // change loopBreak to true in order to break loop, valid input
					cout << endl << "Adding " << betAmount << " to your bet." << endl;
					players[i]->addBet(betAmount);
				}
				else{
					// invalid input
					cin.clear();
					cin.ignore(256, '\n');
				}
			}

			// add 2 cards to player's hand
			players[i]->addCard(decks.getCard()); 
			players[i]->addCard(decks.getCard());
		}
		cout << "Dealer's hand:" << endl;
		dealer->displayHand(); // dealer reveals top card
		int playerInput = 0; // var for player choices

		// ask each player hit, stand, or surrender if handSum() != BLACKJACK, exclude dealer
		for (int i = 0; i < players.size(); i++){		
			
			players[i]->inRound = true; // set round status to true so player can play
			cout << "Player " << i + 1 << " hand: " << players[i]->getHandSum() << endl;
			players[i]->printStatus(); // show player's their hand
			cout << endl << endl;
			bool splitCheck = true; // bool value for split detection
		
			while (splitCheck){

				if (players[i]->getHandSum() != BLACKJACK){ // If player's hand is not 21, give them their choices
					playerInput = player_choice(players[i], dealer); // playerInput assigned new value
				}

				/*1 = hit, 2 = stand, 3 = surrender, 4 = double down, 5 = split 6 = insurance
				splitCheck allows a parent player to play the rest of their hand after making a split*/
				switch (playerInput){
					case 1:
						// player hits
						cout << "Player " << i + 1 << " hits." << endl;
						hit(players[i], decks); 
						splitCheck = false;
						break;
					case 2:
						// player stands, do nothing
						cout << "Player " << i + 1 << " stands." << endl;
						players[i]->printStatus();
						splitCheck = false;
						break;
					case 3:
						// player surrenders their hand
						player_surrender(players[i]);
						cout << "Player " << i + 1 << " surrenders their hand." << endl;
						splitCheck = false;
						break;
					case 4:
						// player wants to double down
						player_doubleDown(players[i], decks);
						cout << "Player " << i + 1 << " doubles down." << endl;
						splitCheck = false;
						break;
					case 5:
						// do a split
						player_split(players, players[i], decks);
						cout << "Player " << i + 1 << " splits." << endl;
						splitCheck = true;
						break;
					case 6:
						// do insurance
						players[i]->insure();
						cout << "Player " << i + 1 << " takes insurance." << endl;
						splitCheck = false;
						break;
					default:
						// player had no choice because they have Blackjack
						cout << "You've got Blackjack!" << endl;
						splitCheck = false;
						break;
				}					
			}
			
		}
		// do dealer AI here
		cout << "Dealer's hand:" << endl;
		dealer->revealHand();
		while (dealer->getHandSum() != BLACKJACK && dealer->getHandSum() <= DEALER_HIT && playerInput != 0){ // constant used here
			// while dealer's hand is <= to 16, keep hitting
			dealer->addCard(decks.getCard());
			cout << "Dealer is hitting..." << endl;
			dealer->revealHand();
		}
		cout << "Dealer's hand is: " << dealer->getHandSum() << endl;
		
		// display player hands
		for (int i = 0; i < players.size(); i++){
			cout << "Player " << i + 1 << " hand is: " << players[i]->getHandSum() << endl;
			players[i]->printStatus();
		}

		check_victory(players, dealer); // check for victory conditions

		// remove cards from dealer/player hands
		while (dealer->getHandCount() > 0){
			dealer->discard(0);
		}
		for (int i = 0; i < players.size(); i++){
			while (players[i]->getHandCount() > 0){
				players[i]->discard(0);
			}
		}
		cout << "========================================================" << endl;
	
	} // end of game
	cout << "None of the remaining players have enough bank left to bet with." << endl << "Thanks for playing!" << endl;
	
	// Do memory cleanup
	for (int i = 0; i < players.size(); i++){
		delete(players[i]);
	}
	delete(dealer);
} //end main

// Method to display player options and get their choice
/*Needs to be checked and tested!!!*/
int player_choice(Player *player, Dealer *dealer){

	bool stopLoop = false; // bool to control user input loop
	int userIn; // value entered in by user
	vector<int> validChoices = {1, 2}; // vector containing valid number choices for player

	while (!stopLoop){	
		cout << "Select: (1) Hit, (2) Stand"; // default choices

		if (dealer->getHandSum() != BLACKJACK){
			cout << ", (3) Surrender";
			validChoices.push_back(3);
		}

		if (player->getBank() >= player->getBet()){ // player has option to double down
			cout <<", (4) Double Down";
			validChoices.push_back(4);
		}

		if (player->getHandCount() == 2 && player->get_face_value(0) == player->get_face_value(1)){ // player has option to split
			cout << ", (5) Split";
			validChoices.push_back(5);
		} 

		if (dealer->getCardValue(1) == 11 && 
			(player->getBank() >= (player->getBet() / 2 ))){ // dealer has an ace showing, player must have bank at least 1/2 of bet
			cout << ", (6) Insurance";
			validChoices.push_back(6);
		}
		cout << endl;
		
		cin >> userIn;
		if (cin){
			for (int i = 0; i < validChoices.size(); i++){
				if (userIn == validChoices[i]){
					stopLoop = true;
				}
			}
		}
		else{
			// invalid input
			cout << "Invalid input, please select again." << endl;
			cin.clear();
			cin.ignore(256, '\n');			
		}
	}
	return userIn;
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

// Sets a player's bet to 1/2 of their current amount
void player_surrender(Player *player){
	player->winBet(SURRENDER_AMOUNT); // constant used here
	player->inRound = false; // flip the inRound bool for the player
}

void player_split(vector<Player *> &players, Player *player, Deck &decks){
	Player *splitPlayer = new Player(player); // create a "new" player, give new player one of the pairs from parent player
	splitPlayer->addCard(decks.getCard()); // give new player an extra card

	players.push_back(splitPlayer); // push child onto vector
	player->addCard(decks.getCard()); // give parent player an extra card
}

// Gets the last card in the last deck for a player
void hit(Player *player, Deck &decks){
	
	player->addCard(decks.getCard()); // add card to player hand
	cout << "Player's sum: " << player->getHandSum() << endl;
	
	while (true){	
		player->printStatus(); // show player info

		//if player's sum is less than blackjack, offer them the option to hit again.
		if (player->getHandSum() < BLACKJACK){ 
			cout << "Do you want to hit again? (y/n):";
			string hitAgain; // hitAgain string created
			cin >> hitAgain; // hitAgain string value assigned.

			// if user selected to hit, deal another card and go back to the while loop, otherwise return
			if (hitAgain.compare("y") == 0 || hitAgain.compare("Y") == 0){
				player->addCard(decks.getCard());
			}
			else if (hitAgain.compare("n") == 0 || hitAgain.compare("N") == 0){
				return;
			}
			else{
				cout << "Input not recognized, try again" << endl;
			}
		}
		// if player's sum is equal to 21, tell them they have Blackjack and return to main
		else if (player->getHandSum() == BLACKJACK){
			cout << "You've got Blackjack! " << endl;
			return;
		}
		// player's sum is over 21, they are unable to hit and lose
		else{
			cout << "You've gone over 21 and are no longer able to hit." << endl;
			return;
		}
	}
}

// Player doubles bet and is dealt one more card for round
void player_doubleDown(Player *player, Deck &decks){
	int playerBet = player->getBet(); // playerBet variable declared and initialized
	player->addBet(playerBet); // playerBet used to change value in player
	player->addCard(decks.getCard());
}

// Function to check victory conditions
void check_victory(vector<Player *> &players, Dealer *dealer){	
	for (int i = 0; i < players.size(); i++){
		if (players[i]->inRound){

			int pHandSum = players[i]->getHandSum(); // assign player's hand sum to pHandSum
			int dHandSum = dealer->getHandSum(); // assign dealer's hand sum to dHandSum

			if (pHandSum == BLACKJACK && dHandSum != BLACKJACK){ // player wins Blackjack
				players[i]->winBet(1.5);
				cout << "Player " << i + 1 << " has Blackjack! Player wins 1.5 x their bet." << endl;
			}
			else if (pHandSum == dHandSum){ // player ties with dealer
				players[i]->winBet(0);
				cout << "Player " << i + 1 << " ties with the dealer. Player pushes." << endl;
			}
			else if (pHandSum < BLACKJACK && dHandSum > BLACKJACK){ // player has higher hand value
				players[i]->winBet(0);
				cout << "Dealer busts and Player " << i + 1 << " wins!" << endl;
			}
			else if (pHandSum < BLACKJACK && pHandSum > dHandSum){ // player has higher hand value, dealer does not bust
				players[i]->winBet(0);
				cout << "Player " << i + 1 << " has a better hand than the dealer. Player wins!" << endl;
			}
			else if (dHandSum == BLACKJACK){ // Dealer has Blackjack and player has insurance
				players[i]->winInsure();
			}
			else{ // Dealer has a better hand than the player
				players[i]->loseBet();
				cout << "Dealer has a better hand than Player " << i + 1 << ". Player loses." << endl;
			}

		}
		else{ // player surrendered, gets half their bet back
			cout << "Player surrendered their hand, player gets half their bet back." << endl;
		}
	}
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

/* Method to create a new deck, checks if new worked correctly
void deck_create(vector<Deck *> &decks){

	//Deck * newDeck = new Deck(); // create a new Deck object
	
	if(newDeck == NULL){ // error checking 
		cout << "ERROR: error in assigning memory to new Deck, exiting program" << endl;
		exit(1);
	}
	
	decks.push_back(newDeck);
}
*/


// Check to see if player has been created correctly
bool player_createCheck(Player *player){
	bool retVal = true; // declare return value, assign value to true
	if(player->getBank() <= 0){
		retVal = false; // change return value to false if player's bank is less than or equal to 0
	}
	return retVal; // return bool value of retVal
}

// Checks to see if a deck has 52 cards in it
/*
bool deck_creationCheck(Deck *deck){
	bool retVal = true; // declare return value, assign value to true
	if(deck->size() != NUM_CARDS){
		retVal = false; // change return value if the number of cards in a deck is not equal to NUM_CARDS (52)
	}
	return retVal; // return bool value of retVal
}
*/

// Checks if deck length is one less after deal
bool deck_lengthCheck(Deck *deck, int oldLength){
	bool retVal = true; // declare return value, assign value to true
	if((oldLength - deck->size()) != 1){ // oldLength used for compare
		retVal = false; // change return value if the size of the new deck is not 1 less than the old size
	}
	return retVal; // return bool value of retVal
}

// Method to check if decks to need to be remade and shuffled
bool shuffle_check(vector<Player *> &players, Deck &decks){

	// Formula: (28 * decks.size()) * (players.size() - 1)	
	bool retVal = false; // declare return value, assign value to false
	int formula = (28 * decks.size()) * (players.size()); // int formula uses deck.size() and players.size() values
	int cardSum = decks.size(); // declare and assign cardSum
	/*
	for (int i = 0; i < decks.size(); i++){
		cardSum += decks[i]->size(); // cardSum value changed
	}
	*/
	if (cardSum < formula){
		retVal = true; // change return value if cardSum is less than formula, deck needs to be shuffled 
	}	
	cout << "SHUFFL_CHECK RETURNS: " << retVal << endl;
	return retVal; // return bool value of retVal
}