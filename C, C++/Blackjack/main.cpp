#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct player {
    int bet;
    int amountLeft;
    int value;
    bool busted;
};
struct dealer {
    int amountLeft;
    int value;
    bool busted;
};

struct cardInfo {
    string suit;
    string face;
    int pointsValue;    // value of card
    int cardStatus;     // 0 = Playing, 1 = In deck, 2 = Discard
} deck[52];

void shuffle(cardInfo card[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int r = i + (rand() % (52 - i));
        swap(card[i], card[r]);
    }
}

int main()
{
    int new_suit = 0;
    int win = -1; // stores the number o player who wins
    bool tie = false;
    string faces[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	string status[3] = { "In Play", "In Deck", "Discard" };
	int cardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
    // Initialize deck
    for (int i = 0; i < 52; i++) {
		deck[i].face = faces[i % 13];
		deck[i].suit = suits[new_suit];
		deck[i].pointsValue = cardValue[i % 13];
		deck[i].cardStatus = 1;
		if ((i + 1) % 13 == 0)
			new_suit++;
	}

	player players[6];
	dealer dealer;
	// initialize players and dealer
	for (int i = 0; i < 6; i++) {
        players[i].value = 0;
        players[i].amountLeft = 1000;
        players[i].busted = false;
	}
	dealer.value = 0;
	dealer.amountLeft = 10000;
	dealer.busted = false;

	//  print the information of deck
    //	cout << "Straight deck of cards.." << endl << endl;
    //	for (int i = 0; i < 52; i ++)
    //	{
    //		cout << deck[i].face << " of " << deck[i].suit << " : Value of " << deck[i].pointsValue << " : " << status[deck[i].cardStatus] << endl;
    //	}

        shuffle(deck, 52);
        cout << "**********SHUFFLING...**********" << endl << endl;
    //    for (int i = 0; i < 52; i ++)
    //	{
    //		cout << deck[i].face << " of " << deck[i].suit << " : Value of " << deck[i].pointsValue << " : " << status[deck[i].cardStatus] << endl;
    //	}

	// play 6 times
	int dealt = 0;
	for (int dealno = 1; dealno <= 6; dealno++) {

        // ask for bet
        cout << "Enter Bets (min = 5, max = 20) - " << endl;
        for (int i = 0; i < 6; i++) {
            cout << "Player " << (i+1) << ": ";
            cin >> players[i].bet;
            players[i].amountLeft -= players[i].bet;
        }

        char choice = 'y';
        int value = 0;
        cout << "Dealing 2 cards to " << endl;
        for (int i = 0; i < 6; i++) {
            cout << "Player " << i + 1 << "'s hand..." << endl;
            for (int j = 0; j < 2; j++) {
                deck[dealt].cardStatus = 0;
                cout << deck[dealt].face << " of " << deck[dealt].suit << " : Value is " << deck[dealt].pointsValue << endl;
                players[i].value += deck[dealt].pointsValue;
                dealt++;
            }
            if (players[i].value >= 17 && players[i].value <= 21)
                cout << "Value of hand so far equals " << players[i].value << endl;
            if (players[i].value > 21) {
                cout << "BUSTED!" << endl;
                players[i].busted = true;
            }
            if (players[i].value == 21) {
                win = i;
            }
            cout << endl;
        }
        cout << "Dealer's hand...";
        for (int i = 0; i < 2; i++) {
            deck[dealt].cardStatus = 0;
            cout << deck[dealt].face << " of " << deck[dealt].suit << " : Value is " << deck[dealt].pointsValue << endl;
            dealer.value += deck[dealt].pointsValue;
            dealt++;
            if (dealer.value > 21) {
                cout << "Dealer BUSTED!!" << endl;
            }
        }
        while (dealer.value < 17) {
            deck[dealt].cardStatus = 0;
            cout << deck[dealt].face << " of " << deck[dealt].suit << " : Value is " << deck[dealt].pointsValue << endl;
            dealer.value += deck[dealt].pointsValue;
            dealt++;
            if (dealer.value > 21) {
                cout << "Dealer BUSTED!!" << endl;
            }
        }
        cout << "Dealer's value = " << dealer.value << endl << endl;


        // if someone has won
        if (win >= 0) {
            for (int i = 0; i < 6; i++) {
                // if there is a draw between this player and dealer
                if (players[i].value == 21 && dealer.value == 21) {
                    cout << "tie between dealer and player " << (i + 1) << endl;
                    tie = true;
                    players[i].amountLeft += players[i].bet;
                    // all other players loose
                }
                // if player is a blackjack
                else if (players[i].value == 21 && dealer.value != 21) {
                    cout << "Player " << (i + 1) << " won!!";
                    players[i].amountLeft += 2.5 * players[i].bet;
                    dealer.amountLeft -= 2.5 * players[i].bet;
                }
            }
        }
        else if (dealer.busted) {
            // return money to all the players
            for (int i = 0; i < 6; i++) {
                players[i].amountLeft += players[i].bet;
            }
        }
        // else ask players if they want more cards
        else {
            for (int i = 0; i < 6 && !players[i].busted; i++) {
                cout << "Player " << (i+1) << ", do you want more cards? (y or n)? ";
                cin >> choice;
                while (choice != 'n' && choice != 'N') {
                    deck[dealt].cardStatus = 0;
                    cout << deck[dealt].face << " of " << deck[dealt].suit << " : Value is " << deck[dealt].pointsValue << endl;
                    players[i].value += deck[dealt].pointsValue;
                    dealt++;
                    if (players[i].value > 17 && players[i].value <= 21)
                        cout << "Value of hand so far equals " << players[i].value << endl;
                    if (players[i].value > 21) {
                        cout << "BUSTED!" << endl;
                        players[i].busted = true;
                        break;
                    }
                    cout << "Do you want more cards? (y or n)? ";
                    cin >> choice;
                }
            }

            // compare the hands
            for (int i = 0; i < 6; i++) {
                if (dealer.value < players[i].value && players[i].value <= 21) {
                    players[i].amountLeft += 2 * players[i].bet;
                }
                else if (dealer.value == players[i].value) {
                    players[i].amountLeft += players[i].bet;
                }
                // if player has more than 21, then no money is transacted

                if (dealer.amountLeft < 2000) {
                    dealer.amountLeft = 10000;
                }
            }
        }
        // change status of all used cards to discarded
        for (int i = 0; i < dealt; i++) {
            deck[i].cardStatus = 2;
        }
        if (dealno % 2 == 0) {
            for (int i = 0; i < dealt; i++) {
                deck[i].cardStatus = 1;
            }
            shuffle(deck, 52);
            for (int i = 0; i < 6; i++) {
                players[i].value = 0;
            }
            dealer.value = 0;
        }
        for (int i = 0; i < 6; i++) {
            cout << "Player " << (i+1) << " has $" << players[i].amountLeft << endl;
        }
	}

	for (int i = 0; i < 6; i++) {
        cout << "Player " << (i+1) << " has $" << players[i].amountLeft << endl;
	}
    return 0;
}
