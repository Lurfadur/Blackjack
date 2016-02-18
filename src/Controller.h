#include "Deck.h"
#include "Dealer.h"
#include <string.h>
#include <vector>
#include <unistd.h>

using std::cout;
using std::endl;
using std::vector;
using std::cin;

/* Methods for testing and checking*/
#define NUM_CARDS 52 // Constant for the number of cards in a deck
#define BLACKJACK 21 // Constant for the number for Blackjack
#define SURRENDER_AMOUNT 0.5 // Constant for the amount to be multiplied to the player's bet when doing a surrender
#define DEALER_HIT 16 // Constant for when the dealer must hit

void offer_advice(Dealer *dealer){
	string dealerTop = dealer->get_face_value(1); // assign dealerTop to the face value of dealer's top card
	
	if (dealerTop.compare("A") == 0){ // top card is Ace
		cout << "Extreme danger, a loss is likely." << endl;
	}
	else if (dealerTop.compare("K") == 0 ||
			dealerTop.compare("Q") == 0 ||
			dealerTop.compare("J") == 0 ||
			dealerTop.compare("10") == 0){
		cout << "Big trouble! You'll be lucky to push." << endl;
	}
	else if (dealerTop.compare("9") == 0){
		cout << "You're a little uptight and maybe in trouble." << endl;
	}
	else if (dealerTop.compare("8") == 0 || 
			dealerTop.compare("7") == 0){
		cout << "Breathe a little easier. The dealer is beatable." << endl;
	}
	else if (dealerTop.compare("6") == 0 ||
			dealerTop.compare("5") == 0 ||
			dealerTop.compare("4") == 0){
		cout << "Looking good. You are in the driver's seat." << endl;
	}
	else{
		cout << "Wait and see. Be cautious." << endl;
	}
}

void display_wait(int loops){
	cout << "Thinking ";
  cout << "-" << std::flush;
  for(int i = 0; i < loops; i++){
    sleep(1);
    cout << "\b\\" << std::flush;
    sleep(1);
    cout << "\b|" << std::flush;
    sleep(1);
    cout << "\b/" << std::flush;
    sleep(1);
    cout << "\b-" << std::flush;

  }	
}

// Method to display player options and get their choice
int player_choice(Player *player, Dealer *dealer){

	bool stopLoop = false; // bool to control user input loop
	int userIn = 0; // value entered in by user
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

		/*
    if player's sum is less than blackjack, 
    offer them the option to hit again.
    */
		if (player->getHandSum() < BLACKJACK){ 
			cout << "Do you want to hit again? (y/n):";
			string hitAgain; // hitAgain string created
			cin >> hitAgain; // hitAgain string value assigned.

			/*
      if user selected to hit, 
      deal another card and go back to the while loop,
      otherwise return
      */
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
		
    /*
    if player's sum is equal to 21,
    tell them they have Blackjack and return to main
    */
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

// iPlayer doubles bet and is dealt one more card for round
void player_doubleDown(Player *player, Deck &decks){
  // playerBet variable declared and initialized
	int playerBet = player->getBet();
  // playerBet used to change value in player
	player->addBet(playerBet); 
	player->addCard(decks.getCard());
}

// Function to check victory conditions
void check_victory(vector<Player *> &players, Dealer *dealer){	
	for (int i = 0; i < players.size(); i++){
		if (players[i]->inRound){
      
      // assign player's hand sum to pHandSum
			int pHandSum = players[i]->getHandSum();
      // assign dealer's hand sum to dHandSum
			int dHandSum = dealer->getHandSum();

			if (pHandSum == BLACKJACK && dHandSum != BLACKJACK){
        // player wins Blackjack
				players[i]->winBet(1.5);
				cout  << "Player " << i + 1 
              << " has Blackjack! Player wins 1.5 x their bet." 
              << endl;
			}
			else if (pHandSum == dHandSum){
        // player ties with dealer
				players[i]->winBet(0);
				cout  << "Player " << i + 1 
              << " ties with the dealer. Player pushes." 
              << endl;
			}

			else if (pHandSum < BLACKJACK && dHandSum > BLACKJACK){ 
        // player has higher hand value
				players[i]->winBet(0);
				cout << "Dealer busts and Player " << i + 1 << " wins!" << endl;
			}
			else if (pHandSum < BLACKJACK && pHandSum > dHandSum){
      // player has higher hand value, dealer does not bust
				players[i]->winBet(0);
				cout << "Player " << i + 1 
              << " has a better hand than the dealer. Player wins!"
              << endl;
			}
			else if (dHandSum == BLACKJACK){ 
        // Dealer has Blackjack and player has insurance
				players[i]->winInsure();
			}else{
        // Dealer has a better hand than the player
				players[i]->loseBet();
				cout << "Dealer has a better hand than Player " 
              << i + 1 << ". Player loses." << endl;
			}
		}else{ // player surrendered, gets half their bet back
			cout << "Player surrendered their hand, player gets half their bet back." << endl;
		}
	}
}

// Method to create a new player, checks if new worked correctly
void player_create(vector<Player *> &players){
	Player * newPlayer = new Player();
  // Need to pass bank ammount, or default is 1000
	if (newPlayer == NULL){
    // error checking
		cout << "ERROR: error in assigning memory to new Player, exiting program" 
         << endl;
		exit(1);
	}
	players.push_back(newPlayer);
}

// Check to see if player has been created correctly
bool player_createCheck(Player *player){
	bool retVal = true; // declare return value, assign value to true
	if (player->getBank() <= 0){
    /*
    change return value to false if player's bank 
    is less than or equal to 0
    */
		retVal = false; 
	}
	return retVal; // return bool value of retVal
}

// Method to check if decks to need to be remade and shuffled
bool shuffle_check(vector<Player *> &players, Deck &decks, int numDecks){

	// Formula: (28 * decks.size()) * (players.size() - 1)	
	bool retVal = false; // declare return value, assign value to false
	int formula = (28 * numDecks) * (players.size()); // int formula uses deck.size() and players.size() values

	if (decks.size() <= formula){
		retVal = true; // change return value if cardSum is less than formula, deck needs to be shuffled 
	}	
	return retVal; // return bool value of retVal
}
