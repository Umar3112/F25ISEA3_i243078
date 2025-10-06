#include <iostream>
using namespace std;

class TicTacToe {
private:
    char board[9];         // Represents 3x3 grid
    char player1Symbol;    // Symbol for Player 1
    char player2Symbol;    // Symbol for Player 2
    int currentTurn;       // 1 = Player 1, 2 = Player 2

public:
    // Constructor to initialize board and players
    TicTacToe() 
	{
        for (int i = 0; i < 9; i++)
            board[i] = '1' + i;  // Fill with numbers 1-9

        player1Symbol = 'X';
        player2Symbol = 'O';
        currentTurn = 1;
    }

    // Function to display the game board
    void displayBoard() const 
	{
        cout << "_________________________" << endl;
        for (int row = 0; row < 3; row++) {
            cout << "|       |       |       |" << endl;
            cout << "|   " << board[row * 3] << "   |   "
                 << board[row * 3 + 1] << "   |   "
                 << board[row * 3 + 2] << "   |" << endl;
            cout << "|_______|_______|_______|" << endl;
        }
    }

    // Function to check if a player has won
    bool checkWinner(char symbol) const 
	{
        int wins[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
            {0, 4, 8}, {2, 4, 6}             // Diagonals
        };

        for (int i = 0; i < 8; i++) 
		{
            if (board[wins[i][0]] == symbol &&
                board[wins[i][1]] == symbol &&
                board[wins[i][2]] == symbol)
                return true;
        }
        return false;
    }

    // Function to check if the board is full (for draw)
    bool isBoardFull() const 
	{
        for (int i = 0; i < 9; i++) 
		{
            if (board[i] != 'X' && board[i] != 'O')
                return false;
        }
        return true;
    }

    // Function to handle one player's move
    void playerMove() 
	{
        char currentSymbol = (currentTurn == 1) ? player1Symbol : player2Symbol;
        int position;

        while (true) 
		{
            cout << "\nPlayer " << currentTurn << " (" << currentSymbol << ") - Enter position (1-9): ";
            cin >> position;

            // Input validation
            if (cin.fail() || position < 1 || position > 9) 
			{
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a number from 1 to 9.\n";
                continue;
            }

            // Check if position is free
            if (board[position - 1] == 'X' || board[position - 1] == 'O') 
			{
                cout << "This cell is already occupied! Try again.\n";
            } 
			else 
			{
                board[position - 1] = currentSymbol;
                break;
            }
        }
    }

    // Function to switch turns
    void switchTurn() 
	{
        currentTurn = (currentTurn == 1) ? 2 : 1;
    }

    // Function to start the game
    void playGame() 
	{
        cout << "=========== TIC TAC TOE ===========\n";
        cout << "Player 1 = X\nPlayer 2 = O\n\n";

        while (true) 
		{
            displayBoard();
            playerMove();

            char currentSymbol = (currentTurn == 1) ? player1Symbol : player2Symbol;

            if (checkWinner(currentSymbol)) 
			{
                displayBoard();
                cout << "\nPlayer " << currentTurn << " (" << currentSymbol << ") Wins!\n";
                break;
            }

            if (isBoardFull()) 
			{
                displayBoard();
                cout << "\nIt's a Draw!\n";
                break;
            }

            switchTurn();
        }
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}

