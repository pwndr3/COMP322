#include <iostream>

using namespace std;

/* Functions from functions.cpp */
void greetAndInstruct();
void displayBoard (char board[]);
bool checkIfLegal(int cellNbre, char board[]);
bool checkWinner(char board[]);
void computerMove(char board[]);
/**/

int main(int argc, char **argv) {
    greetAndInstruct();
    
    char board[27] = {0};

    int turnNumber = 1;
    while(!checkWinner(board) && turnNumber++ <= 27) {
        // Display board for player
        displayBoard(board);

        // Player move
        string playerMove;
        cout << "Pick your move: ";
        cin >> playerMove;

        while(!checkIfLegal(stoi(playerMove), board)) {
            cout << "Invalid move: " << playerMove << endl;
            cout << "Pick your move: ";
            cin >> playerMove;
        } 
        board[stoi(playerMove) - 1] = 'X';

        if(checkWinner(board))
            break; // If player won the game, break now

        // Computer move
        computerMove(board);
    } 

    if(turnNumber == 27)
        cout << "END! It's a TIE!" << endl;

    return 0;
}