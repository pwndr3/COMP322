#include <iostream>
#include <string>

using namespace std;

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
    string boardASCII[3][9]; // Matrix that will contain the ASCII board

    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 9; col++) {
            int idx = (col / 3) * 9 + (col % 3) + (row * 3) + 1;

            if(board[idx] == 0)
                boardASCII[row][col] = to_string(idx); // Empty cell
            else
                boardASCII[row][col] = board[idx];
        }
    }

    for(int row = 0; row < 3; row++) {
        cout << boardASCII[row][0] << " | " << boardASCII[row][1] << " | " << boardASCII[row][2] << "          ";
        cout << boardASCII[row][3] << " | " << boardASCII[row][4] << " | " << boardASCII[row][5] << "          ";
        cout << boardASCII[row][6] << " | " << boardASCII[row][7] << " | " << boardASCII[row][8] << endl;
    }
}