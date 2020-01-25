#include <iostream>

/* Functions from functions.cpp */
void greetAndInstruct();
void displayBoard (char board[]);
/**/

int main(int argc, char **argv) {
    //greetAndInstruct();
    
    char board[27] = {0};
    board[8] = 'X';
    board[20] = 'O';
    displayBoard(board);

    return 0;
}