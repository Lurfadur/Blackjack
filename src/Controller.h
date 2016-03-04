#include "Deck.h"
#include "Dealer.h"
#include <string.h>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::cin;

class Controller{
  public:
    Controller(int numPlayers, int numDecks);
    ~Controller();
    //display interface methods

    /*
      clears the terminal.
      non-portable.
    */
    void clear();

    /*
      waits 'loops' number of ticks
    */
    void display_wait(int loops);

    /*
      Displays the dealers hand and the hand of players[playerNum]
    */
    void displayBoard(int playerNum);
    
    /*
      Displays the dealer's hand and "player"s hand
    */
    void displayBoard(Player* player);
    
    /*
      prints out a menu based on choices
    */
    void displayMenu(vector<int>* choices);
   
    /*
      returns 0 if input is invalid
    */
    int getMenuInput(vector<int>* choices);
    
    //player options
    
    /*
      Displayes the menu and gets player input
    */
    int player_choice(Player* player);
    int  player_choice(int playerNum);

    /*

    */
    void hit(Player* player);
    void player_split( Player *player);
    void player_doubleDown(Player *player);
    void offer_advice(int playerNum);

    //helper methods
    void bet();
    void deal();
    bool check_banks();
    void player_surrender(Player *player);
    void check_victory();
    void player_create();
    bool player_createCheck(Player *player);
    bool shuffle_check(int numDecks);
    /*
      discards the players and dealers hands
    */
    void discardHands();

    /*
      Iterates through players' turns
    */
    void playerTurns();

    /*
      Finished the dealer's turn
    */ 
    void dealerTurn();

  private:
    vector<Player*>* players;
    Deck* decks;
    Dealer* dealer;
    

};
