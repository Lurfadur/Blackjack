// Main file for Blackjack
#include "Controller.h"

using std::cout;
using std::cin;
using std::vector;
using std::endl;

int main(int argc, char **argv){

  int playerInput = 0; // var for player choices
  Dealer *dealer = new Dealer();
  // check dealer for NULL value
  if (dealer == NULL){ 
    cout << "ERROR: error in dealer creation, exiting program" << endl;
    exit(1);
  }
  // update to get number of players from argv, set to 1 for default
  int playerCount = 1;
  int numDecks = 2;
  vector<Player *> players;
  Deck decks(playerCount + 1);

  // Deck and Player creation
  // playerCount used for loop bounds
  for (int i = 0; i < playerCount; i++){ 
    player_create(players); // players vector used 
    if (!player_createCheck(players[i])){
      cout << "ERROR: error in player creation, exiting program" << endl;
      exit(1);
    }
  }

  decks.shuffle(); // shuffle the decks
  cout << "\033[2J\033[1;1H"; // clear screen
  cout <<"Welcome to K&G Blackjack!" 
    << endl << "Press CTRL + C to quit the game." << endl;

  int roundNumber = 1; // number of rounds played

  /* 
     Master loop to run the game
   */
  // check if players are still in game
  while (check_banks(players)){ 
    cout << "Round number: " << roundNumber << endl;
    roundNumber++;

    // check to see if decks need to be remade
    if (shuffle_check(players, decks, numDecks)){
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
        cout << "Place a bet between 1 and " 
          << players[i]->getBank() << ": ";

        int betAmount = 0; // int amount for player bet
        cin >> betAmount;

        if (betAmount <= players[i]->getBank() 
            && betAmount > 0 && cin){
          //valid input
          loopBreak = true; 
          cout << endl << "Adding " 
            << betAmount << " to your bet." << endl;

          players[i]->addBet(betAmount);

        }else{
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

    /*
       ask each player hit, stand, or surrender 
       if handSum() != BLACKJACK, 
       exclude dealer
     */
    /*splitCheck allows a parent player 
      to play the rest of their hand after making a split*/
    bool splitCheck = true; // bool value for split detection
    for (int i = 0; i < players.size(); i++){		
      // set round status to true so player can play
      players[i]->inRound = true; 
      cout << "Player " << i + 1 
        << " hand: " << players[i]->getHandSum() << endl;

      // show player's their hand
      players[i]->printStatus();
      cout << endl << endl;

      cout << "Would you like some advice? (y/n): ";
      string advice;
      cin >> advice;

      // if user wants help, 
      bool help_while = true; 
      while(help_while){
        if (advice.compare("y") == 0 
            || advice.compare("Y") == 0){
              offer_advice(dealer);
              help_while = false;
        }
        else if (advice.compare("n") == 0 
            || advice.compare("N") == 0){
          cout << "Player " << i + 1 
            << " does not want advice." << endl;
          help_while = false; // break loop
        }
        else{
          cout << "Input not recognized, try again" << endl;
        }
      } // end while-loop

    while (splitCheck){

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
    while (players[i]->getHandCount() > 0){
      players[i]->discard(0);
    }
  }

  display_wait(2);
  // clear screen
  cout << "\033[2J\033[1;1H";

  } // end of game
  cout << "None of the remaining players have "
  << "enough bank left to bet with." 
  << endl << "Thanks for playing!" << endl;

  // Do memory cleanup
  for (int i = 0; i < players.size(); i++){
    delete(players[i]);
  }
delete(dealer);
} //end main


