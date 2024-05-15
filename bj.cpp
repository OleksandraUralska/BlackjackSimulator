# include <iostream>
# include "bj.h"
# include <cstdlib>
# include <ctime>
# include <iomanip>
using namespace std;

void LetsBegin(string & username, float & balance){
	cout<<"Welcome to Blackjack Simulator!"<<endl;
	cout<<"Enter the player's name: ";
	cin>>username;
	float nonDecs = static_cast<float>(rand()%(901)+100); //a value between 100 and 1000
	float Decs = static_cast<float>(rand()%(100))/100;
	balance = static_cast<float>(nonDecs) + Decs; 
	cout<<"\n"<<username<<" , your starting balance is: $"<<fixed<<setprecision(2)<<balance<<"!"<<"\nGood luck!"<<endl;
	return;
}


float WagerCheck(const float& balance){
	cout<<"Enter your wager amount: ";
	float Wager;
	bool ValidWager = 0;
	do {
		cin>>Wager;
		if (Wager <= balance && Wager > 0)
			ValidWager = 1;
		if (!ValidWager)
			cout<<"Your wager has to be no more than your balance ($"<<fixed<<setprecision(2)<<balance<<"), and no less than $0! Try again:"; 
	}while(!ValidWager);
	return Wager;
}

Card GenerateRandomCard(const int min, const int max){
	Card card;
	card.value = CardValue(min, max);//assigns a value from 1 to 13
	card.name = CardName(card.value);//chooses name, based on value
	card.suit = CardSuit(card.suitNum);//assigns a random suit
	//points are determined later in points4Card function based on the card value
	return card;
}

Card GenerateRandomCard(const int min, const int max, const int prob){
	Card card;
	int Draw10 = rand()%(101);//a value from 1 to 100 
	if (Draw10 <=  prob)
		card.value = 10;
	 else
		card.value = CardValue(min, max);
	card.name = CardName(card.value);
	card.suit = CardSuit(card.suitNum);
	return card;
}

int CardValue(const int min, const int max){
	return rand()%(max - min + 1) + min; // range 1 - 13
}

string CardName(const int Card){//takes in card value 
	switch(Card){
	case 1:
		return "Ace";
	case 11:
		return "Jack";
	case 12:
		return "Queen";
	case 13:
		return "King"; 
	default: 
		return to_string(Card);
	}
}

string CardSuit(int & suitNum){
	suitNum = rand()%(4) + 1;
	switch(suitNum){
	case 1:
		return "diamonds"; //index 0
	case 2:
		return "hearts";//index 1
	case 3:
		return "clubs";//index 2
	}
	return "spades";//index 3
}

void Points4Card(const int Card, int & points, int & Aces11){//here, Card is card.value
	if (Card > 1 && Card < 11){//+Card value for numeric card
		points += Card;
	} else if (Card == 1) {//+1 or +11 for Ace
		if ((points + 11) > 21){
			points += 1;
		} else {
			points += 11;
			Aces11 += 1;
		}
	} else {
		points += 10;//+10 for Jack, Queen, or King
	}
	return;
}

void isBlackjack(bool & BJ, const int points){
	if (points == 21)
		BJ = 1;
	return;
}

void PlayerChoice(const string username, bool & Hit, bool & Stand, bool & DoubleDown, const string Advise, bool&FollowedAdvise){
	cout<<username<<", choose an option from the list:"<<endl<<endl;
	cout<<"1. Hit"<<endl<<"2. Stand"<<endl<<"3. Double Down"<<endl<<endl<<"Enter the option: ";
	int Choice;
	do {
		cin>>Choice;
		switch(Choice){
		case 1:
			Hit = 1;
			break;
		case 2:
			Stand = 1;
			break;
		case 3: 
			DoubleDown = 1;
			break;
		default: 
			cout<<"Invalid option! Please try again: ";
		}
	}while(Hit == 0 && Stand == 0 && DoubleDown == 0);
	if (Hit && Advise == "Hit")
		FollowedAdvise = 1;
	if (Stand && Advise == "Stand")
		FollowedAdvise = 1;
	if (DoubleDown && Advise == "Double Down")
		FollowedAdvise = 1;
	return;
}

bool Bust(const int points){
	return (points > 21);
}

void DealersTurn(bool & DealersBJ, bool & DealersBust, int & DealersPoints,const  int& PlayersPoints, const int& min, const int& max, int & Aces11Dealer, const Card PlayersHand[], Card DealersHand[], const int size, bool usedCards[][4]){
	cout<<endl<<"Dealer's Turn!"<<endl<<endl;
	do{
		DealersHand[1] =  GenerateRandomCard(min, max);
	}while(validCard(usedCards, DealersHand[1]) == 0);
	Points4Card(DealersHand[1].value, DealersPoints, Aces11Dealer);
	cout<<"\n"<<"Player's hand: ";
	printHand(PlayersHand, size);
	cout<<"\nPlayer's points: "<<PlayersPoints<<endl;
	cout<<"Dealer's hand: ";
	printHand(DealersHand, size);
	cout<<"\nDealer's points: "<<DealersPoints<<endl;
	if (DealersPoints == 21)
		DealersBJ = 1;
	if (!DealersBJ && DealersPoints < 17){
		int i = 2;
		do{
			do{
				DealersHand[i] =  GenerateRandomCard(min, max);
			}while(validCard(usedCards, DealersHand[i]) == 0);
			Points4Card(DealersHand[i].value, DealersPoints, Aces11Dealer);
			DealersBust = Bust(DealersPoints);
			if (DealersBust)
				acesRock(DealersPoints, Aces11Dealer);
			cout<<"\n"<<"Player's hand: ";
		        printHand(PlayersHand, size);
       			cout<<"\nPlayer's points: "<<PlayersPoints<<endl;
		        cout<<"Dealer's hand: ";
		        printHand(DealersHand, size);
		        cout<<"\nDealer's points: "<<DealersPoints<<endl;
			i ++;
		}while(DealersPoints < 17);
	}
	DealersBust = Bust(DealersPoints);
	return;
}

void displayOutcome(const float&balance, const float&Wager, const int&PlayersPoints, const int&DealersPoints, const bool&PlayersBJ, const bool&DealersBJ, const bool&PlayersBust, const bool&DealersBust, int&WinR, int&WinBJ, int&LossR, int&LossBJ, int&Tie, const bool FollowedAndLost, const bool NotFollowedAndWon, const bool NotFollowedAndLost){
	if (PlayersBJ && DealersBJ) {
		Tie += 1;
		cout<<endl<<"Tie!"<<endl<<"Balance update: +$0"<<endl;
	} else if(PlayersBJ == 1){
		WinBJ += 1;
		cout<<endl<<"Congratulations!!! You hit blackjack!"<<endl;
		cout<<"Balance update: +$"<<fixed<<setprecision(2)<<(1.5*Wager)<<endl;
	} else if(!PlayersBust && (PlayersPoints == DealersPoints)){
		Tie += 1;
		cout<<endl<<"Tie!"<<endl<<"Balance update: +$0"<<endl;
	} else if(DealersBJ == 1){
		LossBJ += 1;
		cout<<"The dealer hits blackjack!"<<endl;
		if (FollowedAndLost){
			cout<<"You followed the recommended action and lost. You receive 20% refund."<<endl;
			cout<<"Balance update: -$"<<(Wager - (0.2 * Wager))<<endl;
		} else if(NotFollowedAndLost){
			cout<<"You did not follow the recomended action and lost. You lose an additional 20% of your original wager."<<endl;
			cout<<"Balance update: -$"<<(Wager + (0.2 * Wager))<<endl;
		} else {
			cout<<"Balance update: -$"<<Wager<<endl;
		}
	} else if(PlayersBust == 1){
		LossR += 1;
		cout<<endl<<"You busted!"<<endl;
		if (FollowedAndLost){
			cout<<"You followed the recommended action and lost. You receive 20% refund."<<endl;
			cout<<"Balance update: -$"<<fixed<<setprecision(2)<<(Wager - (0.2 * Wager))<<endl;
		} else if(NotFollowedAndLost){
			cout<<"You did not follow the recomended action and lost. You lose an additional 20% of your original wager."<<endl;
			cout<<"Balance update: -$"<<(Wager + (0.2 * Wager))<<endl;
		} else {
			cout<<"Balance update: -$"<<Wager<<endl;
		}
	} else if(DealersBust == 1){
		WinR += 1;
		cout<<endl<<"The dealer busted!"<<endl;
		if (NotFollowedAndWon){
			cout<<"You did not follow the recommended action an won. You receive 80% on top of your original wager."<<endl;
			cout<<"Balance update: +$"<<fixed<<setprecision(2)<<(Wager + (0.8 * Wager))<<endl;
		} else {
 			cout<<"Balance update: +$"<<Wager<<endl;
		}
	} else if(PlayersPoints > DealersPoints){
		WinR += 1;
		cout<<endl<<"You won!"<<endl;
		if (NotFollowedAndWon){
			cout<<"You did not follow the recommended action an won. You receive 80% on top of your original wager."<<endl;
			cout<<"Balance update: +$"<<fixed<<setprecision(2)<<(Wager + (0.8 * Wager))<<endl;
		} else {
			cout<<"Balance update: +$"<<Wager<<endl;
		}
	} else if(PlayersPoints < DealersPoints){
		LossR += 1;
		cout<<endl<<"The dealer won!"<<endl;
		if (FollowedAndLost){
			cout<<"You followed the recommended action and lost. You receive 20% refund."<<endl;
			cout<<"Balance update: -$"<<fixed<<setprecision(2)<<(Wager - (0.2 * Wager))<<endl;
		} else if(NotFollowedAndLost){
			cout<<"You did not follow the recomended action and lost. You lose an additional 20% of your original wager."<<endl;
			cout<<"Balance update: -$"<<(Wager + (0.2 * Wager))<<endl;
		} else {
			cout<<"Balance update: -$"<<Wager<<endl;
		}
	} else {
		cout<<"Error!"<<endl;
	}
	if (static_cast<int>(balance)<0)
		cout<<"Your current balance: $0"<<endl;
	else
		cout<<"Your current balance: $"<<balance<<endl;
	return;
}

void updatePlayerBalance(float&  balance, const float&Wager, const int& PlayersPoints, const int& DealersPoints, const bool& PlayersBJ, const bool& DealersBJ, const bool& PlayersBust, const bool& DealersBust, const bool FollowedAdvise, bool & FollowedAndLost, bool & NotFollowedAndWon, bool & NotFollowedAndLost){
	bool Won = 0;
	bool Lost = 0;
	if (PlayersBJ && DealersBJ){
		balance += 0;
	} else if (PlayersBJ) {
		balance += 1.5 * Wager;
	} else if(!PlayersBust && (PlayersPoints == DealersPoints)){
		balance += 0;
	} else if(DealersBust){
		balance += Wager;
		Won = 1;
	} else if(PlayersBust || DealersBJ) {
		balance -= Wager;
		Lost = 1;
	} else if(PlayersPoints < DealersPoints){
		balance -= Wager;
		Lost = 1;
	} else if(PlayersPoints > DealersPoints){
		balance += Wager;
		Won = 1;
	} else {
		cout<<"Error"<<endl;
	}
	if (Won && !FollowedAdvise){
		balance += Wager * 0.8;
		NotFollowedAndWon = 1;
	}
	if (Lost &&  FollowedAdvise){
		balance += Wager * 0.2;
		FollowedAndLost = 1;
	}
	if (Lost && !FollowedAdvise){
		balance -= Wager * 0.2;
		NotFollowedAndLost = 1;
	}
	return;
}

void anotherRound(bool & plusRound){
	cout<<"\nWould you like to play another round?"<<endl<<"\n1.Yes"<<"\n2.No"<<endl<<endl;
	cout<<"Your choice: ";
	int Choice;
	bool ValidChoice = 0;
	do{
	cin>>Choice;
	switch(Choice){
	case 1:
		ValidChoice = 1;
		plusRound = 1;
		break;
	case 2:
		ValidChoice = 1;
		plusRound = 0;
		break;
	default:
		cout<<"Invalid option! Try again: ";
	}
	}while(!ValidChoice);
	return;
}


void displayGameSummary(const int&Round, const int&WinR, const int&WinBJ, const int&LossR, const int&LossBJ, const int&Tie, const float&balance, const float&delta, const float&Debt){
	cout<<" =============== GAME SUMMARY =============== "<<endl;
	cout<<"		Total Rounds Played: "<<Round<<endl;
	cout<<"	 	Total Wins (Regular): "<<WinR<<endl;
	cout<<"		Total Wins (BJ): "<<WinBJ<<endl;
	cout<<"	 	Total Losses (Regular): "<<LossR<<endl;
	cout<<"		Total Losses (BJ): "<<LossBJ<<endl;
	cout<<"		Total Ties: "<<Tie<<endl;
	cout<<"		Final Balance: $"<<balance<<endl;
	cout<<"		Net Gain/Loss: $"<<delta<<endl;
	cout<<"		Debt: $"<<Debt<<endl;
	cout<<"Thank you for playing CodeJack: The Blackjack Simulator!"<<endl;
	cout<<"Keep your real wallet safe. Hope to see you again soon!"<<endl;
	return;
}


