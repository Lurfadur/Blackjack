// Main file for Blackjack

#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace std;

// Variables and vectors used at setup
vector<Player *> players;
vector<Deck *> decks;


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
void create_player(vector<Player *> &players);
bool check_victory(vector<Player *> players);
void split(vector<Player *> &players, vector<Deck *> &decks);



int main(){


}
