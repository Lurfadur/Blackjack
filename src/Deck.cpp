#include "Deck.h"
#include <vector>
#include "Card.h"
#include <algorithm> // std::random_shuffle
#include <random> //std::default_random_engine
#include <chrono> //std::chrono::system_clock

    /*Create Deck*/
    Deck::Deck(){
		for(int i=0; i<4; i++){
  		  for(int j=0; j<13; j++){
  		    std::string newSuit; //declare newSuit
  		    switch(i){
  		      case 0: newSuit = u8"♠"; //newSuit used on next 8 lines
  		        break;
  		      case 1: newSuit = u8"♥";
  		        break;
  		      case 2: newSuit = u8"♣";
  		        break;
  		      case 3: newSuit = u8"♦";
  		      break;
  		      default: newSuit = "E";
  		    }
  		    
  		    int newValue; //declare newVlaue, used in switch cases
  		    std::string newFValue; //declare newFVlaue, used in switch cases
  		    switch(j){
  		      case 0:
  		        newValue = 11;
  		        newFValue = "A";
  		        break;
  		      case 1:
  		        newValue = 2;
  		        newFValue = "2";
  		        break;
  		      case 2:
  		        newValue = 3;
  		        newFValue = "3";
  		        break;
  		      case 3:
  		        newValue = 4;
  		        newFValue = "4";
  		        break;
  		      case 4:
  		        newValue = 5;
  		        newFValue = "5";
  		        break;
  		      case 5:
  		        newValue = 6;
  		        newFValue = "6";
  		        break;
  		      case 6:
  		        newValue = 7;
  		        newFValue = "7";
  		        break;
  		      case 7:
  		        newValue = 8;
  		        newFValue = "8";
  		        break;
  		      case 8:
  		        newValue = 9;
  		        newFValue = "9";
  		        break;
  		      case 9:
  		        newValue = 10;
  		        newFValue = "10";
  		        break;
  		      case 10:
  		        newValue = 10;
  		        newFValue = "J";
  		        break;
  		      case 11:
  		        newValue = 10;
  		        newFValue = "Q";
  		        break;
  		      case 12:
  		        newValue = 10;
  		        newFValue = "K";
  		        break;
  		      default:
  		        newValue = 0;
  		        newFValue = "E";
  		    }
          /*newValue, newFValue, newSuit used to create a new Card*/
  		    Card* newCard = new Card(newValue, newFValue, newSuit);
  		    cards.push_back(newCard);
  		    //newCard->display();
  		 	}
  		}
		}
    
    /*Pushes a new Card onto the Deck
    * takes a Card pointer
    * returns nothing
    */
    void Deck::addCard(Card* newCard){
      cards.push_back(newCard);
    }

    /*Gets a Card from the Deck
    * takes nothing
    * returns a pointer to a Card in the Deck
    */
    Card* Deck::getCard(){
      Card* retCard = cards.back(); //assign a new Card obj to last element in vec
      cards.pop_back();
      return retCard; 
    }

    /*Gets the size of the deck, which is private
    * takes nothing
    * returns the size of Deck with an int
    */
    int Deck::size(){
      return cards.size();
    }

    /*Function to shuffle a Deck
    * takes nothing
    * returns nothing
    */
    void Deck::shuffle(){
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //declare and assign seed variable
      auto engine = std::default_random_engine(seed); //make and assign engine, seed used here
      std::shuffle(cards.begin(), cards.end(), engine); // engine used here
    }

    /*Function to delete a Deck
    * takes nothing
    */
		Deck::~Deck(){
			for(int i=0; i<cards.size(); i++){
				delete(cards[i]);
			}
		}
