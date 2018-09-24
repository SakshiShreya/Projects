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
    cout << "**********SHUFFLING...**********" << endl << endl;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int r = i + (rand() % (52 - i));
        swap(card[i], card[r]);
    }
}

void initialize_deck(string faces[], string suits[], int cardValue[]) {
    int new_suit = 0;
    for (int i = 0; i < 52; i++) {
		deck[i].face = faces[i % 13];
		deck[i].suit = suits[new_suit];
		deck[i].pointsValue = cardValue[i % 13];
		deck[i].cardStatus = 1;
		if ((i + 1) % 13 == 0)
			new_suit++;
	}
}

void initialize_players(player players[]) {
    for (int i = 0; i < 6; i++) {
        players[i].value = 0;
        players[i].amountLeft = 1000;
        players[i].busted = false;
	}
}

dealer initialize_dealer(dealer dealer) {
    dealer.value = 0;
	dealer.amountLeft = 10000;
	dealer.busted = false;
	return dealer;
}

void askBets(player players[]) {
    cout << "Enter Bets (min = 5, max = 20) - " << endl;
    for (int i = 0; i < 6; i++) {
        cout << "Player " << (i+1) << ": ";
        cin >> players[i].bet;

        // if player enters a bet that is out of bounds,
        while (players[i].bet < 5 || players[i].bet > 20) {
            cout << "You can enter a bet between 5 and 20 only. Enter your bet again." << endl;
            cin >> players[i].bet;
        }
        players[i].amountLeft -= players[i].bet;
    }
}

// stores the index of card on the top of the deck
// that will be given to a player or dealer
int dealt = 0;

player dealCardToP(player p) {
    deck[dealt].cardStatus = 0;
    cout << deck[dealt].face << " of " << deck[dealt].suit << " : Value is " << deck[dealt].pointsValue << endl;
    p.value += deck[dealt].pointsValue;
    dealt++;
    return p;
}

player dealTwoCardsToP(player p) {
    for (int j = 0; j < 2; j++) {
        p = dealCardToP(p);
    }
    // if player has cards of more than 17 value then notify the player
    if (p.value >= 17 && p.value <= 21)
        cout << "Value of hand so far equals " << p.value << endl;

    // check if player is busted
    else if (p.value > 21) {
        cout << "BUSTED!" << endl;
        p.busted = true;
    }
    return p;
}

dealer dealCardToD(dealer d) {
    deck[dealt].cardStatus = 0;
    cout << deck[dealt].face << " of " << deck[dealt].suit << " : Value is " << deck[dealt].pointsValue << endl;
    d.value += deck[dealt].pointsValue;
    dealt++;
    return d;
}

dealer dealTwoCardsToD(dealer d) {
    for (int i = 0; i < 2; i++) {
        d = dealCardToD(d);
    }
    // Check if dealer busted
    if (d.value > 21) {
        cout << "Dealer BUSTED!!" << endl;
        d.busted = true;
    }
    return d;
}

void findWinner(player players[], dealer* dealer) {
    // whoever has higher number wins
    int maxValue = 0;
    // check what is the maxValue in everyone's hand
    // don't update maxValue when that player is busted
    for(int i = 0; i < 6; i++) {
        if (maxValue < players[i].value && !players[i].busted) {
            maxValue = players[i].value;
        }
    }
    // including dealer
    if(maxValue < dealer->value && !dealer->busted) {
        maxValue = dealer->value;
    }

    // now give money to whoever wins
    for (int i = 0; i < 6; i++) {
        if (players[i].value == maxValue) {
            cout << "Player " << (i + 1) << " wins!" << endl;
            players[i].amountLeft += 2 * players[i].bet;
            dealer->amountLeft -= players[i].bet;
        }

        if (dealer->amountLeft < 2000) {
            dealer->amountLeft = 10000;
        }
    }
}

void displayAmounts(player players[]) {
    for (int i = 0; i < 6; i++) {
        cout << "Player " << (i+1) << " has $" << players[i].amountLeft << endl;
	}
}

void discardUsedCards() {
    for (int i = 0; i < dealt; i++) {
        deck[i].cardStatus = 2;
    }
}

void prepareForNextRound(player players[], dealer* dealer, int dealno) {
    // change status of all used cards to discarded
    discardUsedCards();
    displayAmounts(players);

    for (int i = 0; i < 6; i++) {
        players[i].value = 0;
        players[i].busted = false;
    }
    dealer->value = 0;
    dealer->busted = false;

    // Shuffle the card after 2 deals
    if (dealno % 2 == 0) {
        for (int i = 0; i < dealt; i++) {
            deck[i].cardStatus = 1;
        }
        shuffle(deck, 52);
        dealt = 0;
    }
}

int main()
{
    int win = -1; // stores the number of player who wins and 6 if dealer wins
    string faces[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string suits[4] = { "Diamonds", "Clubs", "Hearts", "Spades" };
	int cardValue[13] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

	// status is used only in debugging
	string status[3] = { "In Play", "In Deck", "Discard" };

    initialize_deck(faces, suits, cardValue);

	player players[6];
	dealer dealer;
	// initialize players and dealer
	initialize_players(players);
    dealer = initialize_dealer(dealer);

	//  print the information of deck
    //	cout << "Straight deck of cards.." << endl << endl;
    //	for (int i = 0; i < 52; i ++)
    //		cout << deck[i].face << " of " << deck[i].suit << " : Value of " << deck[i].pointsValue << " : " << status[deck[i].cardStatus] << endl;

    shuffle(deck, 52);
    //    for (int i = 0; i < 52; i ++)
    //		cout << deck[i].face << " of " << deck[i].suit << " : Value of " << deck[i].pointsValue << " : " << status[deck[i].cardStatus] << endl;

	// play 6 times
	for (int dealno = 1; dealno <= 6; dealno++) {
        win = -1;
        // ask for bet
        askBets(players);

        char choice = 'y';
        cout << "Dealing 2 cards to " << endl;
        for (int i = 0; i < 6; i++) {
            cout << "Player " << i + 1 << "'s hand..." << endl;
            players[i] = dealTwoCardsToP(players[i]);

            // Check if player wins
            if (players[i].value == 21) {
                win = i;
            }
            cout << endl;
        }
        cout << "Dealer's hand..." << endl;
        dealer = dealTwoCardsToD(dealer);

        // check if dealer wins
        if (dealer.value == 21) {
            cout << "Dealer won" << endl;
            win = 6;
        }

        // if someone wins after getting two cards
        if (win >= 0) {
            for (int i = 0; i < 6; i++) {
                // if there is a draw between any player and dealer
                if (players[i].value == 21 && dealer.value == 21) {
                    cout << "tie between dealer and player " << (i + 1) << endl;
                    // players gets its bet back
                    players[i].amountLeft += players[i].bet;
                    // all other players loose
                }
                // if player is a blackjack
                else if (players[i].value == 21 && dealer.value != 21) {
                    cout << "Player " << (i + 1) << " won!!" << endl;
                    // player gets 50% more than players debt
                    // since bet is already subtracted from amountLeft,
                    // player gets the bet back and 150% of the bet from dealer.
                    // That sums to 250%.
                    players[i].amountLeft += 2.5 * players[i].bet;
                    dealer.amountLeft -= 1.5 * players[i].bet;
                }
            }
            // don't execute the statements below
            // move to the next round
            prepareForNextRound(players, &dealer, dealno);
            continue;
        }

        // give more cards to dealer while value is less than 17
        while (dealer.value < 17) {
            dealer = dealCardToD(dealer);

            // check if dealer busted
            if (dealer.value > 21) {
                cout << "Dealer BUSTED!!" << endl;
                dealer.busted = true;
            }
        }
        cout << "Dealer's value = " << dealer.value << endl << endl;

        if (dealer.busted) {
            // return money to all the players
            for (int i = 0; i < 6; i++) {
                players[i].amountLeft += players[i].bet;
            }
            // move to next round
            prepareForNextRound(players, &dealer, dealno);
            continue;
        }

        // else ask players if they want more cards till they are not busted
        else {
            for (int i = 0; i < 6 && !players[i].busted; i++) {
                cout << "Player " << (i+1) << ", do you want more cards? (y or n)? ";
                cin >> choice;

                while (choice != 'n' && choice != 'N') {
                    players[i] = dealCardToP(players[i]);
                    // if player has cards of more than 17 value then notify the player
                    if (players[i].value > 17 && players[i].value <= 21)
                        cout << "Value of hand so far equals " << players[i].value << endl;
                    // if player is busted
                    if (players[i].value > 21) {
                        cout << "BUSTED!" << endl;
                        players[i].busted = true;
                        break;
                    }
                    // Check if player gets 21 then ask next player
                    if (players[i].value == 21) {
                        break;
                    }
                    cout << "Do you want more cards? (y or n)? ";
                    cin >> choice;
                }
            }

            findWinner(players, &dealer);
        }
        // change status of all used cards to discarded
        prepareForNextRound(players, &dealer, dealno);
	}

    return 0;
}
