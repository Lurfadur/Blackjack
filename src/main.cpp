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



int main(int argc, char **argv){

  
  //ask for the number of players
  bool sentinel = false;
  int numPlayers = 0;
  while(sentinel == false){
    cout << "How many players? ";
    cin >> numPlayers;
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
    cin >> numDecks;
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


    // ask players to bet
    for (int i = 0; i < numPlayers; i++){
      bool loopBreak = false; // bool used to break while-loop

      while (!loopBreak){
        cout << "Player " << i+1 << ", place a bet between 1 and " 
          << controller->players->at(i)->getBank() << ": ";

        int betAmount = 0; // int amount for player bet
        cin >> betAmount;

        if (betAmount <= controller->players->at(i)->getBank() 
            && betAmount > 0 && cin){
          //valid input
          loopBreak = true; 
          cout << endl << "Adding " << betAmount 
               << " to your bet." << endl;

          controller->players->at(i)->addBet(betAmount);

        }else{
          // invalid input
          cin.clear();
          cin.ignore(256, '\n');
        }
      }
      
      clear();
    }
    
    controller->deal();

    controller->playerTurns();
    controller->dealerTurn();



    controller->check_victory(); // check for victory conditions

    // remove cards from dealer/player hands
    while (dealer->getHandCount() > 0){
      dealer->discard(0);
    }

    for (int i = 0; i < players.size(); i++){
        players[i]->discardHand();
        //check if any players need to be removed
        if(players[i]->getBank() == 0){
          players.erase(players.begin()+i);
        }
    }

    //display_wait(2);
    // clear screen
   // clear();

    //ask the player to keep playing
    cout << "Would you like to keep playing?";
    cin >> keepPlaying;

} // end of game
//cout << "None of the remaining players have "
//<< "enough bank left to bet with." 
//<< endl << "Thanks for playing!" << endl;
cout << "Thanks for playing!" << endl;

// Do memory cleanup
for (int i = 0; i < players.size(); i++){
  delete(players[i]);
}
delete(dealer);
} //end main


