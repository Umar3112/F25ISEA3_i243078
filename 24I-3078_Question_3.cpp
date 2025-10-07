#include <iostream>
using namespace std;

class TicTacToe {
private:
    char board[9];         // 3x3 game board stored in a single array
    char player1Symbol;    // Symbol used by Player 1
    char player2Symbol;    // Symbol used by Player 2
    int currentTurn;       // Indicates whose turn it is (1 or 2)

public:
    // Constructor initializes the board and players' symbols
    TicTacToe() 
	{
        for (int i = 0; i < 9; i++)
            board[i] = '1' + i;  // Fill board with numbers 1–9 to show positions

        player1Symbol = 'X';
        player2Symbol = 'O';
        currentTurn = 1;   // Player 1 starts first
    }

    // Displays the current game board
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

    // Checks if the given symbol has won the game
    bool checkWinner(char symbol) const 
	{
        // All possible winning combinations (rows, columns, diagonals)
        int wins[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
            {0, 4, 8}, {2, 4, 6}             // Diagonals
        };

        // Check each possible winning combination
        for (int i = 0; i < 8; i++) 
		{
            if (board[wins[i][0]] == symbol &&
                board[wins[i][1]] == symbol &&
                board[wins[i][2]] == symbol)
                return true;  // Winning pattern found
        }
        return false;  // No winner yet
    }

    // Checks if all positions on the board are filled
    bool isBoardFull() const 
	{
        for (int i = 0; i < 9; i++) 
		{
            if (board[i] != 'X' && board[i] != 'O')
                return false;  // Found an empty cell
        }
        return true;  // All cells filled
    }

    // Handles the input and move of the current player
    void playerMove() 
    { 
   		char currentSymbol = (currentTurn == 1) ? player1Symbol : player2Symbol; 
		int position; 
		while (true) 
		{ 
			cout << "\nPlayer " << currentTurn << " (" << currentSymbol << ") - Enter position (1-9): "; 
			cin >> position; 
			
			// Check for valid input between 1 and 9
			if (cin.fail() || position < 1 || position > 9) 
			{ 
				cin.clear(); 
				cin.ignore(1000, '\n'); 
				cout << "Invalid input! Please enter a number from 1 to 9.\n"; 
				continue; 
			} 
			
			// Check if the chosen position is already taken
			if (board[position - 1] == 'X' || board[position - 1] == 'O') 
			{ 
				cout << "This cell is already occupied! Try again.\n"; 
			} 
			else 
			{ 
				board[position - 1] = currentSymbol; // Place the player's symbol
				break; 
			} 
		} 
	}

    // Switches turn between Player 1 and Player 2
    void switchTurn() 
	{
        currentTurn = (currentTurn == 1) ? 2 : 1;
    }

    // Starts and controls the overall game flow
    void playGame() 
	{
        cout << "=========== TIC TAC TOE ===========\n";
        cout << "Player 1 = X\nPlayer 2 = O\n\n";

        while (true) 
		{
            displayBoard();       // Show current board
            playerMove();         // Take player's move

            char currentSymbol = (currentTurn == 1) ? player1Symbol : player2Symbol;

            // Check if the current player has won
            if (checkWinner(currentSymbol)) 
			{
                displayBoard();
                cout << "\nPlayer " << currentTurn << " (" << currentSymbol << ") Wins!\n";
                break;
            }

            // Check if board is full and it's a draw
            if (isBoardFull()) 
			{
                displayBoard();
                cout << "\nIt's a Draw!\n";
                break;
            }

            switchTurn();  // Change player's turn
        }
    }
};

int main() {
    TicTacToe game;  // Create game object
    game.playGame(); // Start the game
    return 0;
}

