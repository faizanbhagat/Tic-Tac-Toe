//
//  tictactoe.cpp
//  TicTacToe
//
//  Created by Faizan Bhagat on 12/17/21.
//

#include <iostream>
#include <string.h>

using namespace std;

void printMenu();
void printBoard();
void printWinCondition();
void returnMenu();

void player1Move();
void player2Move();
void AIMove();

int checkWin();
int checkTwo(char x, char y, char z);

void resetBoard();

void game(int selection);
void playEntireGame();

char board[10] = {'-', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char constBoard[10] = {'-', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int gameStyle = 0;

int main() {
    playEntireGame();
}

void printMenu(){
    cout << "Tic Tac Toe" << endl
         << "-----------" << endl << endl;
    cout << "Press 1 for 1 player, press 2 for 2 player: ";
    
    cin >> gameStyle;
    cout << endl;
    
    // checks that user inputted a valid value, prompts user to reenter if invalid
    while (gameStyle != 1 && gameStyle != 2){
        cout << "Error, please enter 1 for 1 player, or 2 for 2 player: ";
        cin >> gameStyle;
        cout << endl;
    }
    
    cout << endl << "Player 1 : X" << endl << "Player 2 : O" << endl << endl;
}

void printBoard(){
    cout << "     |     |     " << endl;
    cout << "  " << board[1] << "  |  " << board[2] << "  |  " << board[3] << endl;
    cout << "     |     |     " << endl;
    cout << "-----|-----|-----" << endl << "     |     |     " << endl;
    cout << "  " << board[4] << "  |  " << board[5] << "  |  " << board[6] << endl;
    cout << "     |     |     " << endl << "-----|-----|-----" << endl << "     |     |     " << endl;
    cout << "  " << board[7] << "  |  " << board[8] << "  |  " << board[9] << endl;
    cout << "     |     |     " << endl << endl;
}

void printWinCondition(){
    if (checkWin() == 1){
        cout << "Player 1 Wins!";
    }
    else if (checkWin() == 2){
        cout << "Player 2 Wins!";
    }
    else if (checkWin() == 0){
        cout << "Game ended in a draw!";
    }
    cout << endl << endl;
}

void returnMenu(){
    int response = 0;
    
    cout << "Would you like to play again?" << endl << endl << "Press 1 to play again, press 2 to exit: ";
    cin >> response;
    cout << endl << endl;
    
    // checks that user inputted a valid value, prompts user to reenter if invalid
    while (response != 1 && response != 2){
        cout << "Error, please enter 1 to play agian or 2 to exit: ";
        cin >> response;
        cout << endl << endl;
    }
    
    
    if (response == 1){
        resetBoard();
        playEntireGame();
    }
    else if (response == 2){
        exit(0);
    }
}

void player1Move(){
    char userMove;
    
    cout << "Player 1 (X): Where would you like to play: ";
    
    cin >> userMove;
    cout << endl;
    
    int userMoveInt = userMove - '0';
    
    // checks if user inputted a square that doesn't already have a move played there, prompts user to reenter if it is invalid
    while (board[userMoveInt] != userMove){
        cout << "Error, please select an available square to play: ";
        cin >> userMove;
        userMoveInt = userMove - '0';
        cout << endl;
    }
    
    board[userMoveInt] = 'X';
}

void player2Move(){
    char userMove;
    
    cout << "Player 2 (O): Where would you like to play: ";
    cin >> userMove;
    cout << endl;
    
    int userMoveInt = userMove - '0';

    // checks if user inputted a square that doesn't already have a move played there, prompts user to reenter if it is invalid
    while (board[userMoveInt] != userMove){
        cout << "Error, please select an available square to play: ";
        cin >> userMove;
        userMoveInt = userMove - '0';
        cout << endl;
    }
    
    board[userMoveInt] = 'O';
}

void AIMove(){
    char boardCorners[4] = {'1', '3', '7', '9'};
    char boardEdges[4] = {'2', '4', '6', '8'};
    
    bool turnPlayed = false;
    
    // if there is two in a row and the third spot is open, computer plays there.
    // this is either good defense if opponent is about to win, or good offense as it wins the
    // game if the two in the row are also AI moves.
    
    if (checkTwo(constBoard[1], constBoard[2], constBoard[3]) != 0){
        board[checkTwo(board[1], board[2], board[3])] = 'O';
    }
    else if (checkTwo(constBoard[4], constBoard[5], constBoard[6]) != 0){
        board[checkTwo(constBoard[4], constBoard[5], constBoard[6])] = 'O';
    }
    else if (checkTwo(constBoard[7], constBoard[8], constBoard[9]) != 0){
        board[checkTwo(constBoard[7], constBoard[8], constBoard[9])] = 'O';
    }
    else if (checkTwo(constBoard[1], constBoard[4], constBoard[7]) != 0){
        board[checkTwo(constBoard[1], constBoard[4], constBoard[7])] = 'O';
    }
    else if (checkTwo(constBoard[2], constBoard[5], constBoard[8]) != 0){
        board[checkTwo(constBoard[2], constBoard[5], constBoard[8])] = 'O';
    }
    else if (checkTwo(constBoard[3], constBoard[6], constBoard[9]) != 0){
        board[checkTwo(constBoard[3], constBoard[6], constBoard[9])] = 'O';
    }
    else if (checkTwo(constBoard[1], constBoard[5], constBoard[9]) != 0){
        board[checkTwo(constBoard[1], constBoard[5], constBoard[9])] = 'O';
    }
    else if (checkTwo(constBoard[3], constBoard[5], constBoard[7]) != 0){
        board[checkTwo(constBoard[3], constBoard[5], constBoard[7])] = 'O';
    }
    // if there are no two in a rows, AI plays in the center
    else if (board[5] == '5'){
        board[5] = 'O';
    }
    else {
        // if there are no two in a rows and the center is filled, AI plays one of the open corners at random (statistically corners are better than edges)
        while (!turnPlayed){
            srand((unsigned) time(0));
            int randCorner;
            int actualCorner;

            randCorner = (rand() % 4) + 1;
            actualCorner = boardCorners[randCorner] - '0';
            
            // checks if randomly selected corner is available, plays if it is, randomly selects another number if not.
            if ((board[actualCorner] == '1' || board[actualCorner] == '3') || (board[actualCorner] == '7' || board[actualCorner] == '9')){
                board[actualCorner] = 'O';
                turnPlayed = true;
            }
        }
        // if there are no two in a rows, all corners and center are filled, AI plays one of the open edges at random
        while (!turnPlayed){
            srand((unsigned) time(0));
            int randEdge;
            int actualEdge;
            
            randEdge = (rand() % 4) + 1;
            actualEdge = boardEdges[randEdge] - '0';
            
            // checks if randomly selected edge is available, plays if it is, randomly selects another number if not.
            if ((board[actualEdge] == '2' || board[actualEdge] == '4') || (board[actualEdge] == '6' || board[actualEdge] == '8')){
                board[actualEdge] = 'O';
                turnPlayed = true;
            }
        }
    }
}

int checkWin(){
    // checks all possible win conditions and returns 1 if player 1 wins, 2 if player 2 wins, 0 if it is a draw, and -1 if game is still being played
    if (board[1] == board[2] && board[2] == board[3]){
        if (board[1] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
    
    else if (board[4] == board[5] && board[5] == board[6]){
        if (board[4] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
        
    else if (board[7] == board[8] && board[8] == board[9]){
        if (board[7] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
    
    else if (board[1] == board[4] && board[4] == board[7]){
        if (board[1] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
    
    else if (board[2] == board[5] && board[5] == board[8]){
        if (board[2] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
    
    else if (board[3] == board[6] && board[6] == board[9]){
        if (board[3] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
    
    else if (board[1] == board[5] && board[5] == board[9]){
        if (board[1] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
    
    else if (board[3] == board[5] && board[5] == board[7]){
        if (board[3] == 'X'){
            return 1;
        }
        else {
            return 2;
        }
    }
    
    else if (board[1] != '1' && board[2] != '2' && board[3] != '3' &&
             board[4] != '4' && board[5] != '5' && board[6] != '6' &&
             board[7] != '7' && board[8] != '8' && board[9] != '9'){
        return 0;
    }
    
    else{
        return -1;
    }
}

int checkTwo(char x, char y, char z){
    // function that checks if inputted row has two of the three filled with the third one open. If third one is open,
    // that index is returned. If not, 0 is returned.
    int returnVal = 0;
    
    int intx = x - '0';
    int inty = y - '0';
    int intz = z - '0';
    
    if (board[intx] == board[inty] && board[intz] == z){
        return intz;
    }
    
    else if (board[inty] == board[intz] && board[intx] == x){
        return intx;
    }
    
    else if (board[intx] == board[intz] && board[inty] == y){
        return inty;
    }
    else {
        return returnVal;
    }
}

void resetBoard(){
    // resets board after game in case user selects to play anotehr game after
    board[0] = '-';
    for (int i = 1; i < 10; i++){
        char temp = i + '0';
        board[i] = temp;
    }
}

void game(int selection){
    // runs the game based on user selection of 1 player or 2 player
    // game alternates turns, prompts user, and prints board after each move
    int currentTurn = 0;
    
    if (selection == 1){
    while (checkWin() != 1 && checkWin() != 2 && checkWin() != 0){
        if (currentTurn % 2 == 0){
            player1Move();
        }
        else {
            AIMove();
            printBoard();
        }
        currentTurn++;
    }
    }
    else if (selection == 2){
        while (checkWin() != 1 && checkWin() != 2 && checkWin() != 0){
            if (currentTurn % 2 == 0){
                player1Move();
            }
            else {
                player2Move();
            }
            currentTurn++;
            printBoard();
        }
    }
}

void playEntireGame(){
    // combination of other fucntions to create one fucntion that runs the entire program
    printMenu();
    printBoard();
    game(gameStyle);
    printWinCondition();
    returnMenu();
}


