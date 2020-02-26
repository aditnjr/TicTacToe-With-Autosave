#include "TicTacToe.h"

bool getUserWantToPlay();

int main(int argc, char** argv) {
	//Assumes no play unless user decides they want to play and initializes game variable to TicTacToe class
    bool play = false;
    TicTacToe game;
    game.loadBoard();
    game.playGame();

    //allows for multiple games to be played
    while (getUserWantToPlay())
    {
        game.playGame();
    }
    
	return 0;
}

bool getUserWantToPlay()
{

    char response;
    bool invalidResponse = true;
    bool play = false;

    while (invalidResponse == true)
    {

        cout << "Would you like to play a new game of TicTacToe? (y/n) " << std::endl;
        cin >> response;

        if (response == 'y')
        {
            invalidResponse = false;

            play = true;
        }
        else if (response == 'n')
        {
            cout << "No Problem!";
            invalidResponse = false;
        }
        else
        {
            cout << "Please input a proper response (y/n)" << std::endl;
        }

    }

    return play;
}
