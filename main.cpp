# include <iostream>
# include "bj.h"
# include <cstdlib>
# include <ctime>
# include <iomanip>
using namespace std;

int main(){

srand(1570);

string username = " ";
float balance = 0, Debt = 0;
LetsBegin(username, balance);
int Round = 0, Luck, min = 1, max = 13, prob4Round, WinR = 0, WinBJ = 0, LossR = 0, LossBJ = 0, Tie = 0, delta = 0, Aces11 = 0, Aces11Dealer = 0;//Aces11 represents player's 11-point aces
bool plusRound;
float startingBalance = balance;
bool usedCards[13][4] = {false};//a 13x4 matrix that keeps track of the used cards.

do {
	Round += 1;
	plusRound = 0;
	cout<<endl<<"================ ROUND "<<Round<<" ================"<<endl<<endl;
	bool PlayersBJ = 0, DealersBJ = 0, PlayersBust = 0, DealersBust = 0, FollowedAndLost = 0, NotFollowedAndWon = 0, NotFollowedAndLost = 0, FollowedAdvise = 0;
	int PlayersPoints = 0, DealersPoints = 0;
	float Wager = WagerCheck(balance);
	string Advise = " ";
	cout<<username<<"'s wager: $"<<fixed<<setprecision(2)<<Wager<<endl;

	Luck = rand()%(101);//New for EACH ROUND; 15% chance that Luck <= 15
	prob4Round = rand()%(101);

	Card PlayersHand[17] = {};
	Card DealersHand[17] = {};
	int size = 17;
	if (Luck >= 15) {
		PlayersHand[0] = GenerateRandomCard(min, max);
		validCard(usedCards, PlayersHand[1]);//The purpose of this line is to document the first card taken by user, or mark it in usedCards matrix. The valu returned from this function call is useless.
		Points4Card(PlayersHand[0].value, PlayersPoints, Aces11);
		do{
			PlayersHand[1] = GenerateRandomCard(min, max);
		}while(validCard(usedCards, PlayersHand[1]) == 0);
		Points4Card(PlayersHand[1].value, PlayersPoints, Aces11);
	} else {
		PlayersHand[0] = GenerateRandomCard(min, max, prob4Round);
		Points4Card(PlayersHand[0].value, PlayersPoints, Aces11);
                PlayersHand[1] = GenerateRandomCard(min, max, prob4Round);
		Points4Card(PlayersHand[1].value, PlayersPoints, Aces11);
	}
	DealersHand[0] = GenerateRandomCard(min, max);
	Points4Card(DealersHand[0].value, DealersPoints, Aces11Dealer);
	cout<<"\n"<<"Player's hand: ";
	printHand(PlayersHand, size);
	cout<<"\nPlayer's points: "<<PlayersPoints<<endl;
	cout<<"Dealers's hand: ";
	printHand(DealersHand, size);
	cout<<"[Hidden Card]";
	cout<<"\nDealer's points: "<<DealersPoints<<" + ? "<<endl<<endl;
	isBlackjack(PlayersBJ, PlayersPoints);

	if (!PlayersBJ)
	// PLAYER'S TURN
		playersTurn(FollowedAdvise, prob4Round, PlayersPoints, DealersPoints, username,  Advise, Luck, Aces11, min, max, PlayersBust, Wager, PlayersHand, DealersHand, size, usedCards);
	//DEALER'S TURN
	if (!PlayersBust)
		DealersTurn(DealersBJ, DealersBust, DealersPoints, PlayersPoints, min, max, Aces11Dealer, PlayersHand, DealersHand, size, usedCards);
	//ROUND RESULTS
	cout<<endl<<"================ ROUND "<<Round<<" RESULTS ==============="<<endl<<endl;
	updatePlayerBalance(balance, Wager, PlayersPoints, DealersPoints, PlayersBJ, DealersBJ, PlayersBust, DealersBust, FollowedAdvise, FollowedAndLost, NotFollowedAndWon, NotFollowedAndLost);
	displayOutcome(balance, Wager, PlayersPoints, DealersPoints, PlayersBJ, DealersBJ, PlayersBust, DealersBust, WinR, WinBJ, LossR, LossBJ, Tie, FollowedAndLost, NotFollowedAndWon, NotFollowedAndLost);
	if (balance == 0){
		cout<<"Your balance is $0! You can no longer place wagers."<<endl;
		break;
	} else if(static_cast<int>(balance) < 0){
		cout<<"You went broke! Your debt: $"<<(-1.0 * balance)<<endl;
		Debt = balance * (-1.0);
		delta = balance - startingBalance;
		balance = 0;
		break;  
	} else {
		anotherRound(plusRound);
	}
}while(plusRound == 1); 
if (delta == 0)
	delta = balance - startingBalance;
displayGameSummary(Round, WinR, WinBJ, LossR, LossBJ, Tie, balance, delta, Debt);
cout<<endl;
return 0;
}

