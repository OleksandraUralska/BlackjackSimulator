//Purpose: this file is a "part 2" of bj.cpp to make function implementations more accessible
# include <iostream>
# include "bj.h"
using namespace std;

bool operator < (const Card & card, const int & rhs){
	return (card.suitNum < rhs);
}

ostream& operator << (ostream& os, const Card & card){
	os<<card.name<<" of "<<card.suit<<", ";
	return os;
}

bool validCard(bool usedCards[][4], const Card card){
	int count = 0;
	for(int i = 0; i < 13; i++){//rows
		for(int j = 0; j < 4; j++){//cols
			if(usedCards[i][j] != 0)
				count ++;
		}
	}
	if (count == (4*13)){
		cout<<"\n\n (Out of cards! Re-using the deck...) "<<endl<<endl;
		for(int i = 0; i < 13; i++){//rows
                	for(int j = 0; j < 4; j++){//cols
				usedCards[i][j] = false;
			}
		}
	}
	if (usedCards[card.value - 1][card.suitNum - 1] == 0){
		usedCards[card.value - 1][card.suitNum - 1] = 1;
		return true; //the card was not used
	} else {
		return false; 
	}
}

void acesRock(int & points, int & Aces){
	if (Aces >= 1){
		points -= 10;
		Aces -= 1;
		}
	return;
}

void printHand(const Card handOf[], const int count){
	Card hand[17] = {};
	//Because handOf cannot be modified.
	for(int i = 0; i < count; i++){
		hand[i] = handOf[i];
	}
	//Sorting the cards by suits. Diamonds -> Hearts -> Clubs -> Spades. 
        for(int i = 0; i < count; i++){
                int min = hand[i].suitNum, minInd = i;
                for(int j = i+1; j < count; j++){
                        if(hand[j] < min){
                                min = hand[j].suitNum;
                                minInd = j;
                        }
                }
                Card  var = hand[i];
                hand[i] = hand[minInd];
                hand[minInd] = var;
  	}
	//Sorting the cards values. Ace > ... > King.
	for(int i = 0; i < count; i++){
		int min = hand[i].value, minInd = i;
		for(int j = i+1; j < count; j++){
			if(hand[j].value < min){
				min = hand[j].value; 
				minInd = j;
			}
		}
		Card var = hand[i];
		hand[i] = hand[minInd];
		hand[minInd] = var;
	}
	for(int k = 0; k < count; k++){
		if (hand[k].value != 0)
			cout<<hand[k];
	}
	return;
}

void playersTurn(bool&FollowedAdvise, const int&prob4Round, int&PlayersPoints,const int&DealersPoints, const string&username,  string&Advise, const int&Luck, int&Aces11, const int&min, const int&max,bool&PlayersBust, float&Wager, Card PlayersHand[],const Card DealersHand[], const int size, bool usedCards[][4]){
        bool Hit;
	int i = 2;
        do {
                FollowedAdvise = 0;
                Advise = adviseOptimalActionOnLuck(prob4Round, PlayersPoints, DealersPoints);
                cout<<Advise<<endl;
                Hit = 0;
                bool Stand = 0;
                bool DoubleDown = 0;
                PlayerChoice(username, Hit, Stand, DoubleDown, Advise, FollowedAdvise);
                if (Hit == 1 || DoubleDown == 1) {//generate a card based on luck, update points and cards, check for bust
                        if (Luck >= 15) {
				do{
                               		PlayersHand[i] = GenerateRandomCard(min, max);
				}while(validCard(usedCards, PlayersHand[i]) == 0);
				Points4Card(PlayersHand[i].value, PlayersPoints, Aces11);
                                PlayersBust = Bust(PlayersPoints);
                                if (PlayersBust == 1)
                                        acesRock(PlayersPoints, Aces11);
                                cout<<"\n"<<"Player's hand: ";
				printHand(PlayersHand, size);
                                cout<<"\nPlayer's points: "<<PlayersPoints<<endl;
                                cout<<"Dealers's hand: ";
				printHand(DealersHand, size);
				cout<<", [Hidden Card]";
                                cout<<"\nDealer's points: "<<DealersPoints<<" + ? "<<endl<<endl;
                        } else {
				do{
                                	PlayersHand[i] = GenerateRandomCard(min, max, prob4Round);
				}while (validCard(usedCards, PlayersHand[i]) == 0);
				Points4Card(PlayersHand[i].value, PlayersPoints, Aces11);
                                PlayersBust = Bust(PlayersPoints);
                                if (PlayersBust == 1)
                                        acesRock(PlayersPoints, Aces11);
                                cout<<"\n"<<"Player's hand: ";
                                printHand(PlayersHand, size);
                                cout<<"\nPlayer's points: "<<PlayersPoints<<endl;
                                cout<<"Dealers's hand: ";
                                printHand(DealersHand, size);
                                cout<<", [Hidden Card]";
                                cout<<"\nDealer's points: "<<DealersPoints<<" + ? "<<endl<<endl;
                        }
                }
                if (DoubleDown == 1){
                        Wager *= 2;
                        cout<<"You chose to double down. Your new wager: $"<<Wager<<endl;
                }

                if (PlayersBust == 1)
                        break;
		i++;
        }while(Hit == 1);
        return;
}


