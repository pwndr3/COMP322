#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

/*
TODO:
    Validate input parameters
    Maybe C++ syntax for loops is better?
    Add comments
*/

void greetAndInstruct() {
    // Initialize pseudo-random number generator
    srand(time(0));

    // Greeting message
    cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer." << endl;
    cout << "The board is numbered from 1 to 27 as per the following:" << endl << endl;
    cout << "1 | 2 | 3          10 | 11 | 12          19 | 20 | 21" << endl;
    cout << "---------          ------------          ------------" << endl;
    cout << "4 | 5 | 6          13 | 14 | 15          22 | 23 | 24" << endl; 
    cout << "---------          ------------          ------------" << endl;
    cout << "7 | 8 | 9          16 | 17 | 18          25 | 26 | 27" << endl << endl;
    cout << "Player starts first. Simply input the number of the cell you want to occupy. Player’s move is marked with X. Computer’s move is marked with O." << endl;
    cout << "Start? (y/n): ";

    // Ask user if he/she wants to start. 'y' starts the program
    char answer;
    cin >> answer;

    if(answer == 'y')
        return;

    // Any key entered but 'y' quits the program
    exit(0);
}

// TODO make sure this works correctly
void displayBoard (char board[]) {
    string boardASCII[3][9]; // Matrix that will contain the ASCII board

    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 9; col++) {
            int idx = (col / 3) * 9 + (col % 3) + (row * 3) + 1;

            if(board[idx - 1] == 0)
                boardASCII[row][col] = to_string(idx); // Empty cell
            else
                boardASCII[row][col] = board[idx - 1];
        }
    }

    for(int row = 0; row < 3; row++) {
        cout << boardASCII[row][0] << " | " << boardASCII[row][1] << " | " << boardASCII[row][2] << "          ";
        cout << boardASCII[row][3] << " | " << boardASCII[row][4] << " | " << boardASCII[row][5] << "          ";
        cout << boardASCII[row][6] << " | " << boardASCII[row][7] << " | " << boardASCII[row][8] << endl;
    }
}

bool checkIfLegal(int cellNbre, char board[]) {
    // Verify cellNbre input range
    if(cellNbre < 1 || cellNbre > 27)
        return false; 

    // Check if already occupied
    if(board[cellNbre - 1] != 0)
        return false;

    return true;
}

char whosTheWinner(char board[]) {
    char winnerSymbol = 0;

    // Check row in same table
    if(winnerSymbol == 0) {
        for(int table = 0; table < 3 && winnerSymbol == 0; table++) {
            for(int row = 0; row < 3 && winnerSymbol == 0; row++) {
                int row_idx = table * 9 + row * 3;

                // If row has three same symbol, we have a winner
                if(board[row_idx] != 0) {
                    if(board[row_idx] == board[row_idx + 1] && board[row_idx] == board[row_idx + 2])
                        winnerSymbol = board[row_idx];
                }
            }
        }
    }

    // Check row across tables
    if(winnerSymbol == 0) {
        for(int row = 0; row < 3 && winnerSymbol == 0; row++) {
            if(board[3*row] != 0) {
                // x|.|.   .|x|.   .|.|x
                if(board[3*row] == board[3*row + 10] && board[3*row] == board[3*row + 20])
                    winnerSymbol = board[3*row];
            }
            if(board[3*row + 2] != 0) {
                // .|.|x   .|x|.   x|.|.
                if(board[3*row + 2] == board[3*row + 10] && board[3*row + 2] == board[3*row + 18])
                    winnerSymbol = board[3*row + 2];
            }
        }
    }
    
    // Check column in same table
    if(winnerSymbol == 0) {
        for(int table = 0; table < 3 && winnerSymbol == 0; table++) {
            for(int col = 0; col < 3 && winnerSymbol == 0; col++) {
                int col_idx = table * 9 + col;

                if(board[col_idx] != 0) {
                    // If col has three same symbol, we have a winner
                    if(board[col_idx] == board[col_idx + 3] && board[col_idx] == board[col_idx + 6])
                        winnerSymbol = board[col_idx];
                }
            }
        }
    }

    // Check column across tables
    if(winnerSymbol == 0) {
        for(int col = 0; col < 3 && winnerSymbol == 0; col++) {
            if(board[col] != 0) {
                // x|.|.   
                //           x|.|.
                //                       x|.|.
                if(board[col] == board[col + 12] && board[col] == board[col + 24])
                    winnerSymbol = board[col];
            }
            if(board[col+6] != 0) {
                //                       x|.|. 
                //           x|.|.
                // x|.|. 
                if(board[col+6] == board[col + 12] && board[col+6] == board[col + 18])
                    winnerSymbol = board[col+6];
            }
        }
    }

    // Check diagonal in same table
    if(winnerSymbol == 0) {
        for(int table = 0; table < 3 && winnerSymbol == 0; table++) {
            if(board[table * 9] != 0) {
                // x|.|.
                // .|x|. 
                // .|.|x
                if(board[table * 9] == board[table * 9 + 4] && board[table * 9] == board[table * 9 + 8])
                    winnerSymbol = board[table * 9];
            }
            if(board[table * 9 + 2] != 0) {
                // .|.|x
                // .|x|. 
                // x|.|.
                if(board[table * 9 + 2] == board[table * 9 + 4] && board[table * 9 + 2] == board[table * 9 + 6])
                    winnerSymbol = board[table * 9 + 2];
            }
        }
    }

    // Check diagonal across tables
    if(winnerSymbol == 0) {
        if(board[13] != 0) {
            // x|.|.   
            //           .|x|.
            //                       .|.|x
            if(board[0] == board[13] && board[0] == board[26])
                winnerSymbol = board[0];
            // .|.|x   
            //           .|x|.
            //                       x|.|.
            else if(board[2] == board[13] && board[2] == board[24])
                winnerSymbol = board[2];
            //                       x|.|. 
            //           .|x|.
            // .|.|x 
            else if(board[8] == board[13] && board[8] == board[18])
                winnerSymbol = board[8]; 
            //                       .|.|x 
            //           .|x|.
            // x|.|. 
            else if(board[6] == board[13] && board[6] == board[20])
                winnerSymbol = board[6]; 
        }    
    }

    // Check same space across tables
    if(winnerSymbol == 0) {
        for(int cell = 0; cell < 9 && winnerSymbol == 0; cell++) {
            if(board[cell] != 0) {
                if(board[cell] == board[cell + 9] && board[cell] == board[cell + 18])
                    winnerSymbol = board[cell];
            }
        }
    }

    return winnerSymbol;
}

bool checkWinner(char board[]) {
    char winnerSymbol = whosTheWinner(board);

    if(winnerSymbol != 0) {
        if(winnerSymbol == 'X')
            cout << "END! Player has won the game!" << endl; 
        else
            cout << "END! Computer has won the game!" << endl;

        return true;
    }

    return false;
}

void computerMove(char board[]) {
    int move = 0;
    int legalMoves[27] = {0};
    int legalMoveSize = 0;

    // Build legal moves array
    for(int i = 1; i <= 27; i++) {
        if(checkIfLegal(i, board)) {
            // Add to legal moves
            legalMoves[legalMoveSize++] = i;
        }
    }

    // Check if a move can make the computer win
    for(int i = 0; i < legalMoveSize; i++) {
        int idx = legalMoves[i];

        // Put O and see if computer wins
        board[idx-1] = 'O';

        if(whosTheWinner(board) == 'O') {
            move = idx;
            break;
        }

        board[idx-1] = 0;
    }

    // If not, check if a move can make the Player win
    if(move == 0) {
        for(int i = 0; i < legalMoveSize; i++) {
            int idx = legalMoves[i];

            // Put X and see if player wins
            board[idx-1] = 'X';

            if(whosTheWinner(board) == 'X') {
                move = idx;
                break;
            }

            board[idx-1] = 0;
        }
    }

    // If not, random move
    if(move == 0)
        move = legalMoves[(rand() % legalMoveSize)];

    board[move-1] = 'O';
}
