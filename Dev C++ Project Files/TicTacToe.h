#ifndef TICTACTOE_H_
#define TICTACTOE_H_

#include "Player.h"
#include <iostream>
using namespace std;

class TicTacToe
{

public:
    TicTacToe();

    void playGame();
    void loadBoard();

private:
	Player players[2];
	
    void drawBoard();
    void saveBoard(char player);
    void showScore();
    void reset();
    void getPlayerMove(char player);
    char togglePlayer(char player);

    bool checkForWin(char player);
    bool checkLineForWin(int square1, int square2, int square3, char player);
    bool checkForTie();

    char squareArray[9];
    
    int moveCounter;
    char recentPlayer;
};

#endif /* TICTACTOE_H_ */
