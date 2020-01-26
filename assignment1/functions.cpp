#include <iostream>
#include <string>

#define NUMBER_OF_ROWS (3)
#define NUMBER_OF_COLS (9)
#define NUMBER_OF_CELLS (NUMBER_OF_ROWS * NUMBER_OF_COLS)

using namespace std;

/*
TODO:
    Validate input parameters
*/

void greetAndInstruct() {
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

void displayBoard (char board[]) {
    string boardASCII[NUMBER_OF_ROWS][NUMBER_OF_COLS]; // Matrix that will contain the ASCII board

    for(int row = 0; row < NUMBER_OF_ROWS; row++) {
        for(int col = 0; col < NUMBER_OF_COLS; col++) {
            int idx = (col / NUMBER_OF_ROWS) * NUMBER_OF_COLS + (col % NUMBER_OF_ROWS) + (row * NUMBER_OF_ROWS) + 1;

            if(board[idx] == 0)
                boardASCII[row][col] = to_string(idx); // Empty cell
            else
                boardASCII[row][col] = board[idx];
        }
    }

    for(int row = 0; row < NUMBER_OF_ROWS; row++) {
        cout << boardASCII[row][0] << " | " << boardASCII[row][1] << " | " << boardASCII[row][2] << "          ";
        cout << boardASCII[row][3] << " | " << boardASCII[row][4] << " | " << boardASCII[row][5] << "          ";
        cout << boardASCII[row][6] << " | " << boardASCII[row][7] << " | " << boardASCII[row][8] << endl;
    }
}

bool checkIfLegal(int cellNbre, char board[]) {
    // Verify cellNbre input range
    if(cellNbre < 1 || cellNbre > NUMBER_OF_CELLS)
        return false; 

    // Check if already occupied
    if(board[cellNbre - 1] != 0)
        return false;

    return true;
}

bool checkWinner(char board[]) {
    // Check row in same table


    // Check row across tables

    
    // Check column in same table


    // Check column across tables


    // Check diagonal in same table


    // Check diagonal across tables
    
}