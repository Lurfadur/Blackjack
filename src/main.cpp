// Main file for Blackjack
#include "Controller.h"

using std::cout;
using std::cin;
using std::vector;
using std::endl;

/*
  Displays the dealer's hand and the current player's (p) status
*/
void displayBoard(Dealer* dealer, vector<Player*>* players, int p){
  cout << "Dealer's hand:" << endl;
  dealer->displayHand(); 
  cout << "\n\n\n";
      
  // show player's their hand
  players->at(p)->printStatus();
}

/*non-portable way to clear a terminal*/
void clear(){
  printf("\e[1;1H\e[2J");
}

int main(int argc, char **argv){
  clear();

  int playerInput = 0; // var for player choices
  Dealer *dealer = new Dealer();
  // check dealer for NULL value
  if (dealer == NULL){ 
    cout << "ERROR: error in dealer creation, exiting program" << endl;
    exit(1);
  }
  // update to get number of players from argv, set to 1 for default
  int playerCount = 1;
  vector<Player *> players;
  
  //ask for the number of players
  bool sentinel = false;
  
  while(sentinel == false){
    cout << "How many players? ";
    cin >> playerCount;
    if(playerCount >= MIN_PLAYERS && playerCount < MAX_PLAYERS){
      sentinel = true;
    }else{
      cout << "Please enter a number between " << MIN_PLAYERS << " and "
          << MAX_PLAYERS << endl;
    }
  }
  clear();

  //Player creation
  // playerCount used for loop bounds
  for (int i = 0; i < playerCount; i++){
    player_create(players); // players vector used 
    if (!player_createCheck(players[i])){
      cout << "ERROR: error in player creation, exiting program" << endl;
      exit(1);
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

  Deck decks(numDecks);
  decks.shuffle(); // shuffle the decks

  clear();

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

    // check to see if decks need to be remade
    if (shuffle_check(players, decks, numDecks)){
      decks.reshuffle(playerCount + 1);
      cout << "Remaking the decks..." << endl;
    }

    // ask players to bet
    for (int i = 0; i < players.size(); i++){
      bool loopBreak = false; // bool used to break while-loop

      while (!loopBreak){
        cout << "Player " << i << ", place a bet between 1 and " 
          << players[i]->getBank() << ": ";

        int betAmount = 0; // int amount for player bet
        cin >> betAmount;

        if (betAmount <= players[i]->getBank() 
            && betAmount > 0 && cin){
          //valid input
          loopBreak = true; 
          cout << endl << "Adding " << betAmount 
               << " to your bet." << endl;

          players[i]->addBet(betAmount);

        }else{
          // invalid input
          cin.clear();
          cin.ignore(256, '\n');
        }
      }
      
      clear();
    }

    //deal two cards to each player and dealer
    for(int i=0; i<2; i++){
      dealer->addCard(decks.getCard());
      for(int j=0; j<players.size(); j++){
        players[j]->addCard(decks.getCard());
      }
    }

    /*
       ask each player hit, stand, or surrender 
       if handSum() != BLACKJACK, 
       exclude dealer
     */
    /*splitCheck allows a parent player 
      to play the rest of their hand after making a split*/
    bool splitCheck = true; // bool value for split detection
    bool playerTurn = true;
    bool advice = false;
    //iterate through player turns
    cout << "got here" << endl;
    for (int i = 0; i < players.size(); i++){

      //while (splitCheck){
      playerTurn =  true;
      while(playerTurn == true){
        clear();
        displayBoard(dealer, &players, i);
        if(advice == true){
            offer_advice(dealer);
        }
        // If player's hand is not 21, give them their choices
        if (players[i]->getHandSum() != BLACKJACK){
          // playerInput assigned new value
          playerInput = player_choice(players[i], dealer);
        }

        /*
           1 = hit
           2 = stand
           3 = surrender
           4 = double down
           5 = split 
           6 = insurance
         */
        switch (playerInput){
          case 1:
            // player hits
            cout << "Player " << i + 1 << " hits." << endl;
            hit(players[i], decks); 
            splitCheck = false;
            playerTurn = false;
            break;
          case 2:
            // player stands, do nothing
            cout << "Player " << i + 1 << " stands." << endl;
            players[i]->printStatus();
            splitCheck = false;
            playerTurn = false;
            break;
          case 3:
            // player surrenders their hand
            player_surrender(players[i]);
            cout << "Player " << i + 1 << " surrenders their hand." << endl;
            splitCheck = false;
            playerTurn = false;
            break;
          case 4:
            // player wants to double down
            player_doubleDown(players[i], decks);
            cout << "Player " << i + 1 << " doubles down." << endl;
            splitCheck = false;
            playerTurn = false;
            break;
          case 5:
            // do a split
            player_split(players, players[i], decks);
            cout << "Player " << i + 1 << " splits." << endl;
            //splitCheck = true;
            //********SPLIT PLAYER*********
            cout << "********SPLIT PLAYER*********" << endl;
            playerTurn = false;
            break;
          case 6:
            // do insurance
            players[i]->insure();
            cout << "Player " << i + 1 << " takes insurance." << endl;
            splitCheck = false;
            playerTurn = false;
            break;
          case 7:
            cout << "Player" << i+1 << " asks for advice." << endl;
            advice = true;
            break;
          default:
            // player had no choice because they have Blackjack
            cout << "You've got Blackjack!" << endl;
            splitCheck = false;
            playerTurn = false;
            break;
        }
      }
      //}
      display_wait(1);
    }// end for-loop
    //}


    // do dealer AI here
    cout << endl << "Dealer's hand:" << endl;
    dealer->revealHand();
    while ( dealer->getHandSum() != BLACKJACK 
        && dealer->getHandSum() <= DEALER_HIT 
        && playerInput != 0){
      cout << endl;
      display_wait(1);
      cout << "\033[2J\033[1;1H";
      // while dealer's hand is <= to 16, keep hitting
      dealer->addCard(decks.getCard());
      cout << "Dealer is hitting..." << endl;
      dealer->revealHand();
    }

    cout << "Dealer's hand is: " << dealer->getHandSum() << endl;
    // display player hands
    for (int i = 0; i < players.size(); i++){
      cout << "Player " << i + 1 
        << " hand is: " 
        << players[i]->getHandSum() << endl;
      players[i]->printStatus();
    }

    check_victory(players, dealer); // check for victory conditions

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


