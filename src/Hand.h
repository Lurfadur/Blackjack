#include <vector>
#include "Card.h"

class Hand{
    public:
        /*Create Hand object
         * takes nothing
         * returns initialized Hand object
         */
        Hand();
        /*Destroys card pointers
         * takes nothing
         * returns nothing
         */
        ~Hand();

        /*Function to display formated visualiztion of a Hand
         * takes nothing
         * returns nothing
         */
        void displayHand();

        /*Function to display formated visualiztion of a dealer's Hand
         * takes nothing
         * returns nothing
         */
        void displayDealerHand();

        /*Get the number of cards in Hand, which is protected
         * takes nothing
         * returns int
         */
        int cardCount();

        /*Function to add a card to a Hand
         * takes pointer to Card object
         * returns nothing
         */
        void addCard(Card*);

        /*Function to remove Card from a Hand
         * takes pointer to Card object to remove
         * returns nothing
         */
        void discard(Card*);

        /*Function to remove Card from Hand based on index
         * takes int position
         * returns nothing
         */
        void discard(int);

        /*Checks hand length after removing a card form the hand
         * takes int
         * returns nothing
         */
        void checkLength(int);

        /*Get the sum of cards in a Hand
         * takes nothing
         * returns int
         */
        int getSum();

        /*Get value of a Card
         * takes int index
         * returs int 
         */
        int getCardValue(int index);

        /*Get Card in a Hand
         * takes int index
         * returns pointer to Card object
         */
        Card* getCard(int index);

        /* returns a card's face value
         *  takes an integer for position in hand
         *  
         */
        std::string get_face_value(int);

    private:
        //accessed to hold cards and distribute cards on split
        std::vector<Card*> cards; 
};
