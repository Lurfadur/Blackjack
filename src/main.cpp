// Main file for Blackjack
#include "Controller.h"

/* Methods for testing and checking*/
#define MAX_PLAYERS 10
#define MIN_PLAYERS 1
#define MIN_DECKS 1
#define MAX_DECKS 10
#define NUM_CARDS 52 // Constant for the number of cards in a deck
#define BLACKJACK 21 // Constant for the number for Blackjack
#define SURRENDER_AMOUNT 0.5 // Constant for the amount to be multiplied to the player's bet when doing a surrender
#define DEALER_HIT 16 // Constant for when the dealer must hit

using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::string;

int getInput(vector<int>* choices){
  string in;
  getline(cin, in);
  
  //convert to integer
  int opt = in[0] - 48;

  for(int i=0; i<choices->size(); i++){
    if(opt == choices->at(i)){
      return opt;
    }
  }
  return 0;
}


int main(int argc, char **argv){

  
  //ask for the number of players
  bool sentinel = false;
  int numPlayers = 0;
  while(sentinel == false){
    cout << "How many players? ";
    string in;
    getline(cin, in);
    numPlayers = in[0]-48;
    if(numPlayers >= MIN_PLAYERS && numPlayers < MAX_PLAYERS){
      sentinel = true;
    }else{
      cout << "Please enter a number between " << MIN_PLAYERS << " and "
          << MAX_PLAYERS << endl;
    }
  }
  

  
  //Deck creation
  int numDecks = 0;
  sentinel = false;
  
  while(sentinel == false){
    cout << "How many decks? ";
    string in;
    getline(cin, in);
    numDecks = in[0]-48;
    if(numDecks >= MIN_DECKS && numDecks < MAX_DECKS){
      sentinel = true;
    }else{
      cout << "Please enter a number between " << MIN_DECKS << " and "
          << MAX_DECKS << endl;
    }
  }

  //create the controller
  Controller* controller = new Controller(numPlayers, numDecks);

  controller->clear();

  cout <<"Welcome to K&G Blackjack!" 
    << endl << "Press CTRL + C to quit the game." << endl;

  int roundNumber = 1; // number of rounds played

  /* 
     Master loop to run the game
   */
  // check if players are still in game
  char keepPlaying = 'y';
  //while (check_banks(players)){
  while (keepPlaying != 'n'){
    cout << "Round number: " << roundNumber << endl;
    roundNumber++;

    controller->bet();
    controller->deal();
    controller->playerTurns();
    controller->dealerTurn();
    controller->check_victory();
    controller->discardHands();

    //ask the player to keep playing
    cout << "Players ";
    for(int i=0; i<controller->getPlayerCount(); i++){
      cout << controller->getPlayerNum(i);
      if(i != controller->getPlayerCount()-1){
        cout << ", ";
      }else{
        cout << " ";
      }
    }
    cout << "Would you like to keep playing?";
    string in;
    getline(cin, in);
    keepPlaying = in[0];

} // end of game

  cout << "Thanks for playing!" << endl;
  free(controller);
} //end main


