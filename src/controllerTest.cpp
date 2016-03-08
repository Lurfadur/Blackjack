// Main file for Blackjack
#include "Controller.h"
#include <fstream>

/* Methods for testing and checking*/
#define MAX_PLAYERS 10
#define MIN_PLAYERS 1
#define MIN_DECKS 1
#define MAX_DECKS 10
#define NUM_CARDS 52 // Constant for the number of cards in a deck
#define BLACKJACK 21 // Constant for the number for Blackjack
#define SURRENDER_AMOUNT 0.5 // Constant for the amount to be multiplied to the player's bet when doing a surrender
#define DEALER_HIT 16 // Constant for when the dealer must hit

using namespace std;

int main(int argc, char **argv){

  ifstream ifs("blackjack_testing.txt", ifstream::in);
  string line; 
  
  //ask for the number of players
  int numPlayers = 0;

  cout << endl << "========Testing for number of players========" << endl;
  cout << "Minimum number of players = " << MIN_PLAYERS << endl;
  cout << "Maximum number of players = " << MAX_PLAYERS << endl;

  while (getline(ifs, line)){
    
    numPlayers = atoi(line.c_str()); 
    
    if (numPlayers < MIN_PLAYERS || numPlayers > MAX_PLAYERS){
      cout << "Number of players incorrect: " << line << endl;
    }
    else{
      cout << "Correct number of players: " << numPlayers << endl;
    }
  }
  
//clear ifstream and reset
  ifs.clear();
  ifs.seekg(0, ios::beg);

//ask for decks
  int numDecks = 0;

  cout << endl << "========Testing for number of decks========" << endl;
  cout << "Minimum number of decks = " << MIN_DECKS << endl;
  cout << "Maximum number of decks = " << MAX_DECKS << endl;

  while (getline(ifs, line)){
   
    numDecks = atoi(line.c_str());
    
    if(numDecks < MIN_DECKS || numDecks > MAX_DECKS){
      cout << "Number of decks incorrect: " << line << endl;
    }
    else{
      cout << "Correct number of decks: " << numDecks << endl;
    }
  }

//clear ifstream and reset
  ifs.clear();
  ifs.seekg(0, ios::beg);

  int playerChoice = 0;

  cout << endl << "========Testing for player turns========" << endl; 
  cout << "Valid values are: 0 > x < 7" << endl;
  while (getline(ifs, line)){

    playerChoice = atoi(line.c_str());

    if (playerChoice < 1 || playerChoice > 6){
      cout << "Player choice is incorrect value: " << line << endl;
    }
    else{
      cout << "Correct player choice: " << playerChoice << endl;
    }
  }

  //clear ifstream and reset
  ifs.clear();
  ifs.seekg(0, ios::beg);

  cout << endl << "========Testing for continue game========" << endl;
  cout << "To continue game, input != 'n'" << endl;

  while (getline(ifs, line)){

    if (line.compare("n") == 0){
      cout << "Game will end on input: " << line << endl;
    }
    else{
      cout << "Game will continue on input: " << line << endl;
    }
  }
  
} //end main