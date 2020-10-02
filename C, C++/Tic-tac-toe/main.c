#include <stdio.h>
#include <stdlib.h>

/********************************
function prototypes
********************************/
void displayBoard();
int verifySelection(int, int);
void checkForWin();
void startGamePlay();

/******************
global variables
******************/
char board[3][3];
char cWhoWon = ' ';
int iCurrentPlayer = 0;

/********************************************************
begin main function
*********************************************************/
int main()
{
    int x, y;
    for ( x = 0; x < 3; x++ ) {
        for ( y = 0; y < 3; y++ ) {
            board[x][y] = ' ';
        }
    }
    displayBoard();

    //takes input from the players and check if a player won
    startGamePlay();
    return 0;
} //end main function

void startGamePlay() {
    int iSquareNum = 0;
    while (cWhoWon == ' ')
    {
        if ( iCurrentPlayer == 1 || iCurrentPlayer == 0 )
        {
            printf("\nPLAYER X\n");
            printf("Enter an available square number (1-9): ");
            scanf("%d", &iSquareNum);
            if ( verifySelection(iSquareNum, iCurrentPlayer) == 1 )
                iCurrentPlayer = 1;
            else
                iCurrentPlayer = 2;
        }
        else
        {
            printf("\nPLAYER O\n");
            printf("Enter an available square number (1-9): ");
            scanf("%d", &iSquareNum);
            if ( verifySelection(iSquareNum, iCurrentPlayer) == 1 )
                iCurrentPlayer = 2;
            else
                iCurrentPlayer = 1;
        } // end if
        displayBoard();
        checkForWin();
        printf("\n%c\n", cWhoWon);
    } //end loop
}

void displayBoard() {
    int x, y;
    for ( x = 0; x < 3; x++ ) {
        for ( y = 0; y < 3; y++ ) {
            printf("%c, ", board[x][y]);
        }
        printf("\n");
    }
}

int verifySelection(int iSquareNum, int iCurrentPlayer) {
    int row = (iSquareNum - 1) / 3;
    int col = (iSquareNum - 1) % 3;
    if(board[row][col] == ' ') {
        if(iCurrentPlayer == 1 || iCurrentPlayer == 0) {
            board[row][col]='X';
        }
        else {
            board[row][col]='0';
        }
        return 0;
    }
    return 1;
}

void checkForWin() {
    int row = 0, col = 0;
    char text1, text2;

    // check each row
    // if we get same entries in each column of a row
    // then the player wins
    // but if entries are different or the cell is empty
    // then check the next row
    while (row < 3) {
        col = 0;
        while (col < 2) {
            text1 = board[row][col];
            text2 = board[row][col + 1];
            if (text1 != text2 || text1 == ' ') {
                break;
            }
            col++;
        }
        // if the loop did not break in between
        // then col will be 2 here
        if (col == 2) {
            if (text1 == 'X') {
                cWhoWon = 'X';
                return;
            } else {
                cWhoWon = '0';
                return;
            }
        }
        row++;
    }

    // similarly test inside cols
    col = 0;
    while (col < 3) {
        row = 0;
        while (row < 2) {
            text1 = board[row][col];
            text2 = board[row + 1][col];
            if (text1 != text2 || text1 == ' ') {
                break;
            }
            row++;
        }
        // if the loop did not break in between
        // then row will be 2 here
        if (row == 2) {
            if (text1 == 'X') {
                cWhoWon = 'X';
                return;
            } else {
                cWhoWon = '0';
                return;
            }
        }
        col++;
    }

    // check diagonal 1
    // in this diagonal, row == col
    col = 0;
    row = 0;
    while (col < 2) {
        text1 = board[row][col];
        text2 = board[row + 1][col + 1];
        if (text1 != text2 || text1 == ' ') {
            break;
        }
        col++;
        row++;
    }
    if (col == 2) {
        if (text1 == 'X') {
            cWhoWon = 'X';
            return;
        } else {
            cWhoWon = '0';
            return;
        }
    }

    // check diagonal 2
    col = 0;
    row = 2;
    while (col < 2) {
        text1 = board[row][col];
        text2 = board[row - 1][col + 1];
        if (text1 != text2 || text1 == ' ') {
            break;
        }
        col++;
        row--;
    }
    if (col == 2) {
        if (text1 == 'X') {
            cWhoWon = 'X';
            return;
        } else {
            cWhoWon = '0';
            return;
        }
    }

    // Check if game is incomplete
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            text1 = board[row][col];
            if (text1 == ' ') {
                // game is incomplete
                return;
            }
        }
    }

    // if control reaches here, that means tie;
    cWhoWon = '-';
}

