#include <fstream>
#include "TicTacToe.h"

static const int MinMovesNeededToWin = 5;
static const int MaxMovesInGame = 9;

TicTacToe::TicTacToe()
    : squareArray{ '1','2','3','4','5','6','7','8','9' },
    moveCounter(0)
{
}


void TicTacToe::drawBoard()
{
    //draws the game board with updated characters for each player
    cout << "Player 1 (X) - Player 2 (O)" << endl << endl;

    cout << "    |     |" << endl;
    cout << " " << squareArray[0] << "  |  " << squareArray[1] << "  |  " << squareArray[2] << endl;

    cout << "____|_____|____" << endl;
    cout << "    |     |    " << endl;

    cout << " " << squareArray[3] << "  |  " << squareArray[4] << "  |  " << squareArray[5] << endl;

    cout << "____|_____|____" << endl;
    cout << "    |     |    " << endl;

    cout << " " << squareArray[6] << "  |  " << squareArray[7] << "  |  " << squareArray[8] << endl;
    cout << endl;

}

void TicTacToe::getPlayerMove(char player)
{
    //Gets player move and stores in board array for display through next iteration
    bool playerMoveFound = false;
    char playerTurn = '0';
    char playerMove = '0';

    if (player == 'X')
    {
        playerTurn = '1';
    }
    else
    {
        playerTurn = '2';
    }


    while (playerMoveFound == false)
    {
        cout << "Player " << playerTurn << " please make a move" << endl;
        cin >> playerMove;

        for (int counter = 0; counter < 9; counter++)
        {
            //If finds the array number makes the change to the iteration...prevents x or o movement
            if (playerMove == squareArray[counter] && playerMove != 'X' && playerMove != 'O')
            {
                squareArray[counter] = player;

                playerMoveFound = true;

                //Move counter implemented to streamline check for win/check for tie
                moveCounter++;
            }

        }
        if (playerMoveFound == false)
        {
            cout << "Invalid player move..." << endl;
        }
    }
}

bool TicTacToe::checkLineForWin(int square1, int square2, int square3, char player) {
    return squareArray[square1] == player &&
           squareArray[square2] == player &&
           squareArray[square3] == player;
}

bool TicTacToe::checkForWin(char player)
{
    bool playerWin = false;

    if (moveCounter >= MinMovesNeededToWin)
    {
        // Only need to check for current player
        // Only need to check until we have a win
        for (int rowCounter = 0; !playerWin && rowCounter < 8; rowCounter += 3)
        {           
            playerWin = checkLineForWin(rowCounter, rowCounter + 1, rowCounter + 2, player);
        }

        //Tests columns for win
        for (int columnCounter = 0; !playerWin && columnCounter < 3; columnCounter++)
        {
            playerWin = checkLineForWin(columnCounter, columnCounter + 3, columnCounter + 6, player);
        }

        //Tests both diagnols
        playerWin |= (checkLineForWin(0, 4, 8, player) | checkLineForWin(2, 4, 6, player));
    }

    return playerWin;
}

bool TicTacToe::checkForTie() {
    return moveCounter == MaxMovesInGame;
}

void TicTacToe::playGame() {
    char playerWinner = 'n';
    
    char player = 'X';
    bool gameOver = false;
    
    if(recentPlayer == 'X' || recentPlayer == 'O') {
    	player = recentPlayer;
	}

    //single game iteration
    do{
    	system("cls");
        drawBoard();
        getPlayerMove(player);

        if (checkForWin(player)) {
        	system("cls");
            cout << endl << "Congratulations player " << player << "! You Win!" << endl << endl;
            
            if(player == 'X') {
            	players[0].addPlayerScore(1);
			} else {
				players[1].addPlayerScore(1);
			}
            
            gameOver = true;
        } else  if (checkForTie()) {
        	system("cls");
            cout << "Tie! You should play again to settle the duel!" << endl << endl;
            gameOver = true;
        }
        player = togglePlayer(player);
        saveBoard(player);
    } while (!gameOver);

    drawBoard();
    showScore();
    reset();
}

char TicTacToe::togglePlayer(char player)
{

    player = player == 'X' ? 'O' : 'X';

    return(player);

}

void TicTacToe::reset()
{
	squareArray[0] = '1';
	squareArray[1] = '2';
	squareArray[2] = '3';
	squareArray[3] = '4';
	squareArray[4] = '5';
	squareArray[5] = '6';
	squareArray[6] = '7';
	squareArray[7] = '8';
	squareArray[8] = '9';
	moveCounter = 0;
	saveBoard('X');
}

void TicTacToe::showScore()
{
	cout << endl;
	cout << "History : Player 1 wins " << players[0].getPlayerScore() << "x, Player 2 wins " << players[1].getPlayerScore() << "x" << endl;
	cout << endl;
}

void TicTacToe::saveBoard(char player){
	ofstream myfile;
  	
	myfile.open ("saveData.txt");
  	myfile << player << endl;
  	myfile << moveCounter << endl;
  	for(int i = 0; i < 9; i++){
		myfile << squareArray[i] << endl;
	}
  	for(int i = 0; i < 2; i++){
		myfile << players[i].getPlayerScore() << endl;
	}
  	myfile.close();
}

void TicTacToe::loadBoard(){
	ifstream loadFile;
	loadFile.open("saveData.txt");
	if(loadFile.is_open()){
		loadFile >> recentPlayer;
		loadFile >> moveCounter;
		char charData;
		for(int i=0;i<9;i++){
			loadFile>> charData;
			squareArray[i] = charData;
		}
		int intData;
		for(int i=0;i<2;i++){
			loadFile>> intData;
			players[i].setPlayerScore(intData);
		}
		loadFile.close();
	}
}
