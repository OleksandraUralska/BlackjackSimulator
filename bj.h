//Student: Oleksandra Uralska 
//Date (created): 03/22/2024
//File: bj.h
//Assignment: HW5
//Purpose: to create a basic version of the Blackjack card game in C++. This simulation will involve a single player (the user) playing against the dealer (the computer).
# include <iostream>
# ifndef BJ_H
# define BJ_H
using namespace std;

struct Card{
	string name;
	string suit; 
	int suitNum;
	int value;
};

//Desc: THis function is needed to overload the < (less than) operator to use it with struct data type
//Pre: None
//Post: Returns true if an object in struct is less than right hand side, and false otherwise.
bool operator < (const Card & card, const int & rhs);

//Desc: THis function is needed to overload the << operator to use it with struct data type
//Pre: None
//Post: Prints out the members of structure in a specified way.
istream& operator << (istream& os, const Card & card);

//Desc: This function checks if the card generated to user or dealer is a valid card, and if it is, it documents this new card as used. 
//Pre: usedCards is a 13 x 4 matrix. In card, suit num is between 1 and 4, value is between 1 and 13
//Post: Returns true if the card is valid and updates the usedCards matrix, else returns false.
bool validCard(bool usedCards[][4], const Card card);

//Desc: Assigns a new value to a card between 1 and 13.
//Pre: min = 1, max = 13
//Post: Returns a random number between 1 and 13.
int CardValue(const int min, const int max);

//Desc: Facilitates players turn.
//Pre: prob4Round, PlayersPonts, DealersPoints, Luck,  Wager are all positive integers. Aces11 is nonnegative. max > min > 0. usedCards is a 13 x 4 matrix. In card, suit num is between 1 and 4, value is between 1 and 13 
//Post: Advices the player on action, promts the player to enter their turn, checks for bust. Facilitates every action related to player's turn.
void playersTurn(bool&FollowedAdvise, const int&prob4Round, int&PlayersPoints, const int&DealersPoints, const string&username,  string&Advise, const int&Luck, int&Aces11, const int&min, const int&max,bool&PlayersBust, float&Wager, Card PlayersHand[],const Card DealersHand[], const int size, bool usedCards[][4]);

//Desc: This function updates the points and player's hand based on a received card.
//Pre: In handOf[], suit num is between 1 and 4, value is between 1 and 13. count is positive.
//Post: updates the points and player's hand based on a received card in the main function
void printHand(const Card handOf[], const int count);

//Desc: This function advises the user on their next action based on their luck
//Pre:  All variables are positivve integers
//Post: Prints out advice on the users action based on their points, dealers points, and and users luck 
template <typename T>
string adviseOptimalActionOnLuck(const T& prob4Round, const int&PlayersPoints, const int&DealersPoints){
        int prob2 = rand()%(101);
        cout<<"\n* Recommended Action: ";
        if (prob2 > prob4Round){
                if (PlayersPoints <= 11 && PlayersPoints >= 9){
                        return "Double Down";
                } else if(PlayersPoints <= 11){
                        return "Hit";
                } else if(PlayersPoints >= 12 && PlayersPoints <= 16){
                        if (DealersPoints >= 7)
                                return "Hit";
                        else
                                return "Stand";
                } else {
                        return "Stand";
                }
        } else {
                int randomAdvice = rand()%(3)+1;//1 to 3
                switch(randomAdvice){
                case 1:
                        return "Hit";
                        break;
                case 2:
                        return "Stand";
                        break;
                case 3:
                        return "Double Down";
                }
        }
        cout<<endl;
        return "Error";
}



//Desc:This function greets the player and generates their account balance
//Pre: balance is a positive number 
//Post: Saves username and balance in the main function
void LetsBegin(string & username, float & balance);

//Desc: Takes in and validates thae wager
//Pre: balance  is positive
//Post: promts the user to enter the wager. Validates it. Saves to main function
float WagerCheck(const float& balance);

//Desc: Generates a random card suit
//Pre: None (it's assigned a valid value withing the function)
//Post: one of four cardsuits is randomly assigned to a card
string CardSuit(int & suitNum);

//Desc: Generates a random card for the user or dealer
//Pre: max > min > 0 
//Post: returns a card number from 1 to 13 
Card GenerateRandomCard(const int min, const int max);

//Desc: Random card generating function for lucky users (luck is <= 15)
//Desc: prob > 0, max > min > 0
//Post: returns a card number from 1 to 13, but there's a higher change of getting a 10-value card
Card GenerateRandomCard(const int min, const int max, const int prob); 

//Desc: Names the card based on its randomly generated number
//Pre: In card, suit num is between 1 and 4, value is between 1 and 13
//Post: The card's name is returned
string CardName(const int Card);

//Desc: Calculates how much points are given for the card
//Pre: In card, suit num is between 1 and 4, value is between 1 and 13, points are initially 0
//Post: adds the points for card to user's or dealer's points, fixes this number in the main function
void Points4Card(const int Card, int & points, int & Aces11);

//Desc: Checks if the player or the dealer have blackjack
//Pre: BJ is 0 by default, points > 0
//Post: Changes BJ to 1 is there's blackjack , else keeps it at 0
void isBlackjack(bool & BJ, const int points);

//Desc: The player choses their move and decides whether to follow the given advice
//Pre: Hit, Stand, DoubleDown, and FollowedAdvise are 0 by default
//Post: Promts the player to chose their next move: hit, stand, or double down. Checks if the player followed the advice
void PlayerChoice(const string username, bool & Hit, bool & Stand, bool & DoubleDown, const string Advise, bool&FollowedAdvise);

//Desc: Checks whether the turn maker busted
//Pre: points > 0
//Post: If the turn maker busted, returns 1. else returns 0.
bool Bust(const int points);

//Desc: This fuction represents the delers turn(s).
//Pre: DealersPoints, PlayersPoints > 0. max > min > 0. DealersBJ and  DealersBust are initially false. Aces11 is initially at most 1. usedCards is a 13 x 4 matrix
//Post: Generates the cards for the dealer until the dealer's points are over 17. Determines whether the dealer has BJ or bust. extends dealer's hand. prints out the outcomes, 
void DealersTurn(bool & DealersBJ, bool & DealersBust, int & DealersPoints, const int& PlayersPoints, const int& min, const int& max, int & Aces11Dealer, const Card PlayersHand[], Card DealersHand[], const int size, bool usedCards[][4]);

//Desc: Displays the outcome of the round.
//Pre: balance, Wager, PlayersPoints, DealersPoints are positive. 
//Post: Prints out who won, the balnce update, and the new balance.
void displayOutcome(const float&balance, const float&Wager, const int&PlayersPoints, const int&DealersPoints, const bool&PlayersBJ, const bool&DealersBJ, const bool&PlayersBust, const bool&DealersBust, int&WinR, int&WinBJ, int&LossR, int&LossBJ, int&Tie, const bool FollowedAndLost, const bool NotFollowedAndWon, const bool NotFollowedAndLost); 

//Desc: Updates player's balance.
//Pre: FollowedAndLost and NotFollowedAndWon are initially false. balance, Wager, PlayersPoints, DealersPoints are positive.
//Post: Updates the player's balance based on their winning status. Refunds 20% of wager if the player followed the advice and lost, adds 80% of wager if didn't follow the advice and won. 
void updatePlayerBalance(float &  balance, const float&Wager, const int& PlayersPoints, const int& DealersPoints, const bool& PlayersBJ, const bool& DealersBJ, const bool& PlayersBust, const bool&DealersBust, const bool FollowedAdvise, bool & FollowedAndLost, bool & NotFollowedAndWon, bool & NotFollowedAndLost);

//Desc: A function that determines whether to play another round
//Pre: plusRound = false, initially.
//Post: Promts the reader to select whether they would like to play another round, 
void anotherRound(bool & plusRound);

//Desc: Displays the game summary
//Pre: all parameters are nonnegative 
//Post: Prints out the number of rounds played, wins, losses, player's and dealer's blackjacks, ties, final balance, net loss/gain
void displayGameSummary(const int&Round, const int&WinR, const int&WinBJ, const int&LossR, const int&LossBJ, const int&Tie, const float&balance, const float&delta, const float&Debt);

//Desc: Modifies the aces values when needed
//Pre: balance > 0, Aces is nonnegative
//Post: when the player or the dealer bust and if they have any 11-valued aces, the ace value changes to 1.
void acesRock(int & points, int & Aces);
# endif


