#include <iostream>

/* Functions from functions.cpp */
void greetAndInstruct();
void displayBoard (char board[]);
bool checkIfLegal(int cellNbre, char board[]);
/**/

int main(int argc, char **argv) {
    //greetAndInstruct();
    
    char board[27] = {0};
    displayBoard(board);

    return 0;
}