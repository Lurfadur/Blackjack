#include "Hand.h"
#include <string>

using std::string;

class Player{
  public:
    /*Create a Player class
     * takes int bankAmount
     * returns initialized Player class
     */
    Player(int bankAmount);
    
    /*
     * Create a Player
     * takes a parent player and Bet
     * useful for initializing split players
     * returns an initialized Player with an empty bank
     * gives new player a bet that is subtracted from the 
     * parent bank and equal to the original bet
     */
    Player(Player*);
		
    /*Default Plkayer creation
     * takes nothing
     * returns initialized Player class
     */
    Player();
    
    /*Function to add a card to Player Hand
     * takes a pointer to Card object
     * returns nothing
     */
    void addCard(Card*);
		
    /*Get the Player bank, which is private
     * takes nothing
     * returns int 
     */
    int getBank();
		
    /*Function to update the Player bank
     * takes int amount
     * returns nothing
     */
    void updateBank(int);
		
    /*Method to add a player bet
    *and subtract the bet amount
    *from the player's bank
    */
    void addBet(int);
    
    /*Method to access
    *the value stored int the 
    *bet variable
    */
    int getBet();
    
    /*Method to return
    *the player's bet variable
    *value
    */
    void push();
    
    /*Method to add half of the player's
    *bet amount into the sideBet var
    * and subtract half the bet amount
    * from bank
    */
    void insure();
    
    /*Returns the player's bet
    * amount multiplied by mult
    * back to the player's bank
    */
    void winBet(double mult);
    
    /*Returns the player's sideBet
    * multiplied by two back to the
    * player's bank.  Dealer takes 
    * the player's bet
    */
    void winInsure();
    
    /*sets the player's
    * bet to 0
    */
    void loseBet();
    
    /*prints the player's bet,
    *bank, sidebet (insurance).
    */
    void printStatus();
    
    /*merges a split player back
    * into the original player
    * this is done using parent*
    */
    void unsplit();

		//Hand helper functions
		
    /*Function to display Player's Hand
     * takes nothing
     * returns nothing
     */
    void displayHand();
		
    /*Get the sum of a Player's Hand, which is private
     * takes nothing
     * returns int
     */
    int getHandSum();
		
    /*Function to get the number of cards in a Hand, which is private
     * takes nothing
     * returns int
     */
    int getHandCount();
		
    /*Function to remove a card from Player's Hand
     * takes pointer to Card object
     * returns nothing
     */
    void discard(Card*);
		
    /*Function to remove a card from Player's Hand, used for split
     * takes int to remove card by index
     * returns nothing
     */
    void discard(int);
		
    /*Gets the value of a card in a Player's Hand
     * takes int index
     * returns int of card value
     */
    int getCardValue(int index);
		
    /*Gets Card object from Player's Hand
     * takes int index
     * returns pointer of Card object
     */
    Card* getCard(int index);
    

    /* returns a card's face value
     *  takes an integer for position in hand
     *  
    */
    string get_face_value(int);
  
    bool inRound = true;//quick way to test if the player is in the round
  protected:
    Player* parent = NULL;//used for keeping track of split hands
    Hand hand; //Hand class represents a player's hand
  private:
    int bank;	//Used to hold amount of player money
    int bet;	//amount taken from bank in bet()
    int sideBet;	//used in insure()
};
