# BlackJack (Card Game)

There are 6 players and a dealer in the game. Game runs for 6 rounds.
The code performs the following functions:

1. Shuffle the deck
2. Put the bet on the table. Minimum bet is $5 and maximum bet is $20. The dealer has $10000 and each player can have up to $1000. If dealer’s money is dropped to $2000 then it is filled in.
3. Deal two card to each user and two cards to the dealer.
4. If the sum of two cards is 21, which is black jack, then it is a winner. If both dealer and player have 21 with two cards then it is a tie.
5. User can hit and request for more cards as long as the sum is the than 21. If the sum is greater than 17 and less than 21 then your program informs the player the sum.
6. If the sum of cards is greater than 21 then the player is busted.
7. Dealer will get more cards as long as the sum is less than 17.
8. If user gets 21 with two cards only then dealer pays 50% more than player’s bet.
9. If neither player nor dealer are busted then whoever has higher number is the winner.
10. Shuffle the card after 2 deals.
11. Display the final amount left with all users at the end of each round.

## How to play:
1. All the players are asked to bet at the beginning of each round.
2. After the bet is put on table, the dealer deals two cards to all the players. Each player can see other players' cards.
3. Dealer(computer) then deals two cards to itself.
4. If any player gets 21 with two cards only, then that player is a 'BLACKJACK'. If dealer also gets 21 with 2 cards, then it is a tie. And if only the dealer gets 21 with two cards, everyone loses.
5. If a player is 'Blackjack', the player gets 1.5 times of its bet back. If it is a 'tie' then the 'Blackjack' player does not gain or lose. But all other players lose their bet money.
6. If a player gets more than 21, then player is 'BUSTED'. The player loses bet money and can't play for this round.
7. If the dealer gets more than 21, then dealer is 'BUSTED'. All the players get their money back.
8. Points 6 and 7 hold true for any point in the game.
9. If no one is a 'BlackJack' and dealer is not 'BUSTED', then dealer will deal more cards to itself while the sum is less than 17. If dealer gets more than 21, then dealer is busted. (Point 7)
10. If no one is a 'BlackJack' and dealer is not 'BUSTED', then players(who are not busted) will be asked if they want more cards while they are not busted. If they want more, they will be dealt one more card till they refuse to get more cards.
11. After the deal is over for all the players, the player who gets the maximum value wins. Winner gets 100% more than the bet.

## How to run the code
Since this is a C++ code, you will need a compiler.

If you are using an IDE, then simply run the code.

If you are not using any IDE and you are using 'g++',

### On MAC / Linux / Windows (Powershell)

Open the terminal/PowerShell and enter the code

For compiling - 
```
g++ main.cpp -o blackjack
```
For running - 
```
./blackjack
```

### On Windows (Command Prompt)

Open Command Prompt and enter the code

For compiling - 
```
g++ main.cpp -o blackjack
```
For running - 
```
blackjack
```
