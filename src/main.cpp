// Main file for Blackjack

#include "Card.h"
#include "Deck.h"
#include "Player.h"
using namespace std;

// Methods for testing and checking

bool card_getCheck(Card *);
bool card_createCheck(Card *);

bool hand_sumCheck(Hand *);
bool hand_lengthCheck(Hand *, int oldLength);

bool deck_creationCheck(Deck *);
bool deck_lengthCheck(Deck *, int oldLength);

bool player_createCheck(Player *);
bool player_checkTotals(Player *); // checks bank, insurance, and bet

// Methods for controlling game
void hit(vector<Player *> players, vector<Deck *> &decks);
void shuffle_check(vector<Player *> players, vector<Deck *> decks);
void deck_create(vector<Deck *> &decks);
void deck_delete(vector<Deck *> &decks);
void deal(vector<Player *> players, vector<Deck *> &decks);
void player_create(vector<Player *> &players);
bool check_victory(vector<Player *> players);
void split(vector<Player *> &players, vector<Deck *> &decks);

int main(int argc, char **argv){
	
	// Variable and vector setup
	vector<Player *> players;
	vector<Deck *> decks;

	bool game = true;
	int playerCount = 2;
	
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

	// Master loop to run the game
	while(game){
		game = false; // prevent infinite loop
		
	}
}

void player_create(vector<Player *> players){
	Player * newPlayer = new Player();
	players.push_back(newPlayer);
}

void deck_create(vector<Deck *> decks){

}

bool player_createCheck(Player *player){
	return true;
}

bool deck_createCheck(Deck *deck){
	return true;
}

