#include <unistd.h>
#include <string>
#include "Controller.h"

#define BLACKJACK 21 // Constant for the number for Blackjack
#define DEALER_HIT 16 // Constant for when the dealer must hit

Controller::Controller(int numPlayers, int numDecks){
  //Player creation
  // playerCount used for loop bounds
  for (int i = 0; i < numPlayers; i++){
    player_create(); 
    if (!player_createCheck(players->at(i))){
      cout << "ERROR: error in player creation, exiting program" << endl;
      exit(1);
    }
  }

  //Create and shuffle the decks
  decks = new Deck(numDecks);
  decks->shuffle();
}

Controller::~Controller(){
  // Do memory cleanup
  //delete(dealer);
  //for (int i = 0; i < players.size(); i++){
  //  delete(players[i]);
  //}
}

//===================Display interface methods===============================//
void Controller::clear(){
  printf("\e[1;1H\e[2J");
}

void Controller::display_wait(int loops){
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
void Controller::displayBoard(int playerNum){
  cout << "Dealer's hand:" << endl;
  dealer->displayHand(); 
  cout << "\n\n\n";
      
  // show player's their hand
  players->at(playerNum)->printStatus();

}

void Controller::displayBoard(Player* player){
  cout << "Dealer's hand:" << endl;
  dealer->displayHand(); 
  cout << "\n\n\n";
      
  // show player's their hand
  player->printStatus();
  
}

void Controller::displayMenu(vector<int>* choices){
  for (int i = 0; i < choices->size(); i++){
    switch(choices->at(i)){
      case 1:
        cout << "[1] Hit";
        break;
      case 2:
        cout << "[2] Stand";
        break;
      case 3:
        cout << "[3] Surrender";
        break;
      case 4:
        cout <<"[4] Double Down";
        break;
      case 5:
        cout << "[5] Split";
        break;
      case 6:
        cout << "[6] Insurance";
        break;
      case 7:
        cout << "[7] Advice";
        break;
    }
    if(i != choices->size()-1){
      cout << ", ";
    }
  }
  cout << endl; 
}

int Controller::player_choice(int playerNum){
  return player_choice(players->at(playerNum));  
}

int Controller::player_choice(Player* player){
  bool stopLoop = false;
  int userIn = 0;
  //hit, stand
  vector<int> validChoices = {1, 2};

  //surrender
  if (dealer->getHandSum() != BLACKJACK){
      validChoices.push_back(3);
  }
  
  //double down
  if (player->getBank() >= player->getBet()){
      validChoices.push_back(4);
  }

  //split
  if (player->getHandCount() == 2 &&
  player->get_face_value(0) == player->get_face_value(1)){

      validChoices.push_back(5);
  } 
  
  //insurance
  if (dealer->getCardValue(1) == 11 && 
  (player->getBank() >= (player->getBet() / 2 ))){
      validChoices.push_back(6);
  }

  //advice
  validChoices.push_back(7);

  bool sentinel = true;
  int playerInput = 0;
  while(sentinel){
    clear();
    displayBoard(player);
    displayMenu(&validChoices);
    playerInput = getMenuInput(&validChoices);
    if(playerInput != 0){
      sentinel = false;
    }
  }
  return playerInput;
}
    
int Controller::getMenuInput(vector<int>* choices){
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

//===================Player option methods===================================//

void Controller::hit(Player* player){
    player->addCard(decks->getCard()); // add card to player hand
    cout << "Player's sum: " << player->getHandSum() << endl;

    while (true){
      clear();
      displayBoard(player);

        /*
           if player's sum is less than blackjack, 
           offer them the option to hit again.
         */
        if (player->getHandSum() < BLACKJACK){ 
            vector<int> choices = {1,2};
            displayMenu(&choices);
            int hitAgain = getMenuInput(&choices);

            /*
               if user selected to hit, 
               deal another card and go back to the while loop,
               otherwise return
             */
            if (hitAgain == 1){
                player->addCard(decks->getCard());
            }else if (hitAgain == 2){
                return;
            }else{
                //shouldn't ever see this
                cout << "Input not recognized, try again" << endl;
            }
        }else if (player->getHandSum() == BLACKJACK){
         /*
           if player's sum is equal to 21,
           tell them they have Blackjack and return to main
         */
         cout << "You've got Blackjack! " << endl;
         return;
       }else{
         // player's sum is over 21, they are unable to hit and lose
         cout << "You've gone over 21 and are no longer able to hit." << endl;
         return;
       }
    }
}

void Controller::player_split( Player *player){}
void Controller::player_doubleDown(Player *player){}
void Controller::offer_advice(int playerNum){}

//===================Helper methods==========================================//
void Controller::bet(){
  clear();
    for (int i = 0; i < players->size(); i++){
      bool loopBreak = false; // bool used to break while-loop
      while (!loopBreak){
        cout << "Player " << i+1 << ", place a bet between 1 and " 
          << players->at(i)->getBank() << ": ";

        int betAmount = 0; // int amount for player bet
        cin >> betAmount;

        if (betAmount <= players->at(i)->getBank() 
            && betAmount > 0 && cin){
          //valid input
          loopBreak = true; 
          cout << endl << "Adding " << betAmount 
               << " to your bet." << endl;

          players->at(i)->addBet(betAmount);

        }else{
          // invalid input
          cin.clear();
          cin.ignore(256, '\n');
        }
      }
    }
    display_wait(3);
}

void Controller::deal(){
    for(int i=0; i<2; i++){
      dealer->addCard(decks->getCard());
      for(int j=0; j<players->size(); j++){
        players->at(j)->addCard(decks->getCard());
      }
    }
}

bool Controller::check_banks(){}
void Controller::player_surrender(Player *player){}
void Controller::check_victory(){
    cout << "Dealer's hand is: " << dealer->getHandSum() << endl;
    // display player hands
    for (int i = 0; i < players->size(); i++){
      cout << "Player " << i + 1 
        << " hand is: " 
        << players->at(i)->getHandSum() << endl;
      players->at(i)->printStatus();
    }


    for (int i = 0; i < players->size(); i++){
        if (players->at(i)->inRound){

            // assign player's hand sum to pHandSum
            int pHandSum = players->at(i)->getHandSum();
            // assign dealer's hand sum to dHandSum
            int dHandSum = dealer->getHandSum();

            if (pHandSum == BLACKJACK && dHandSum != BLACKJACK){
                // player wins Blackjack
                players->at(i)->winBet(1.5);
                cout  << "Player " << i + 1 
                    << " has Blackjack! Player wins 1.5 x their bet." 
                    << endl;
            }
            else if (pHandSum == dHandSum){
                // player ties with dealer
                players->at(i)->winBet(1);
                cout  << "Player " << i + 1 
                    << " ties with the dealer. Player pushes." 
                    << endl;
            }

            else if (pHandSum < BLACKJACK && dHandSum > BLACKJACK){ 
                // player has higher hand value
                players->at(i)->winBet(1);
                cout << "Dealer busts and Player " << i + 1 << " wins!" << endl;
            }
            else if (pHandSum < BLACKJACK && pHandSum > dHandSum){
                // player has higher hand value, dealer does not bust
                players->at(i)->winBet(1);
                cout << "Player " << i + 1 
                    << " has a better hand than the dealer. Player wins!"
                    << endl;
            }
            else if (dHandSum == BLACKJACK){ 
                // Dealer has Blackjack and player has insurance
                players->at(i)->winInsure();
            }else{
                // Dealer has a better hand than the player
                players->at(i)->loseBet();
                cout << "Dealer has a better hand than Player " 
                    << i + 1 << ". Player loses." << endl;
            }
        }else{ // player surrendered, gets half their bet back
            cout << "Player surrendered their hand, player gets half their bet back." << endl;
        }
    }
}

void Controller::player_create(){
    Player * newPlayer = new Player();
    // Need to pass bank ammount, or default is 1000
    if (newPlayer == NULL){
        // error checking
        cout << "ERROR: error in assigning memory to new Player, exiting program" 
            << endl;
        exit(1);
    }
    players->push_back(newPlayer);
}

bool Controller::player_createCheck(Player *player){
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

bool Controller::shuffle_check(int numDecks){

    // Formula: (28 * decks->size()) * (players->size() - 1)	
    bool retVal = false; // declare return value, assign value to false
    int formula = (28 * numDecks) * (players->size()); // int formula uses deck.size() and players->ize() values

    if (decks->size() <= formula){
        retVal = true; // change return value if cardSum is less than formula, deck needs to be shuffled 
    }	
    return retVal; // return bool value of retVal


}
    
void Controller::playerTurns(){
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
    int playerInput;
    //iterate through player turns
    for (int i = 0; i < players->size(); i++){

      //while (splitCheck){
      playerTurn =  true;
      while(playerTurn == true){
        clear();
        displayBoard(i);
        if(advice == true){
          offer_advice(i);
        }
        // If player's hand is not 21, give them their choices
        if (players->at(i)->getHandSum() != BLACKJACK){
          // playerInput assigned new value
          playerInput = player_choice(i);
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
            hit(players->at(i));
            clear();
            displayBoard(i);
            cout << "Player " << i + 1 << " hits." << endl;
            splitCheck = false;
            playerTurn = false;
            break;
          case 2:
            // player stands, do nothing
            cout << "Player " << i + 1 << " stands." << endl;
            //players->at(i)->printStatus();
            splitCheck = false;
            playerTurn = false;
            break;
          case 3:
            // player surrenders their hand
            player_surrender(players->at(i));
            cout << "Player " << i + 1 << " surrenders their hand." << endl;
            splitCheck = false;
            playerTurn = false;
            break;
          case 4:
            // player wants to double down
            player_doubleDown(players->at(i));
            cout << "Player " << i + 1 << " doubles down." << endl;
            splitCheck = false;
            playerTurn = false;
            break;
          case 5:
            // do a split
            player_split(players->at(i));
            cout << "Player " << i + 1 << " splits." << endl;
            //splitCheck = true;
            //********SPLIT PLAYER*********
            cout << "********SPLIT PLAYER*********" << endl;
            playerTurn = false;
            break;
          case 6:
            // do insurance
            players->at(i)->insure();
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
}

void Controller::dealerTurn(){
    // do dealer AI here
    cout << endl << "Dealer's hand:" << endl;
    dealer->revealHand();
    while ( dealer->getHandSum() != BLACKJACK 
        && dealer->getHandSum() <= DEALER_HIT){
      cout << endl;
      display_wait(1);
      cout << "\033[2J\033[1;1H";
      // while dealer's hand is <= to 16, keep hitting
      dealer->addCard(decks->getCard());
      cout << "Dealer is hitting..." << endl;
      dealer->revealHand();
    }

}

void Controller::discardHands(){
    // remove cards from dealer/player hands
    while (dealer->getHandCount() > 0){
      dealer->discard(0);
    }

    for (int i = 0; i < players->size(); i++){
        players->at(i)->discardHand();
        //check if any players need to be removed
        if(players->at(i)->getBank() == 0){
          players->erase(players->begin()+i);
        }
    }

}
