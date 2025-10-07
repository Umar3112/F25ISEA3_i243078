#include<iostream>
#include<iomanip>  // for setw() to align numbers properly
using namespace std;

class TicTacToe
{
private:
    string* board;        // Dynamic array to hold board cells (as strings like "1", "2", "10")
    int gridSize;         // Size of the grid (e.g., 3 for 3x3, 4 for 4x4)
    char player1Symbol;   // Symbol used by Player 1
    char player2Symbol;   // Symbol used by Player 2
    int currentTurn;      // Keeps track of whose turn it is (1 or 2)

public:
    // Constructor — initializes board and game variables
    TicTacToe(int size = 3)
    {
        gridSize = size;
        board = new string[gridSize * gridSize];  // allocate space for grid cells

        // Fill board with numbers from 1 to n*n
        for(int i=0;i<gridSize * gridSize;i++)
        {
            board[i] = to_string(i + 1);
        }

        player1Symbol = 'X';
        player2Symbol = 'O';
        currentTurn = 1;
    }

    // Destructor — releases memory used by board
    ~TicTacToe()
    {
        delete[] board;
    }

    // Function to display the current board
    void displayBoard()
    {
        cout << endl;
        for(int row=0;row<gridSize;row++)
        {
            // print each cell of the row
            for(int col=0;col<gridSize;col++)
            {
                cout << setw(3) << board[row*gridSize + col]; // setw for proper spacing
                if(col < gridSize-1)
                    cout << " |";
            }
            cout << endl;

            // print separator line between rows
            if(row < gridSize-1)
            {
                for(int k=0;k<gridSize;k++)
                {
                    cout << "----";
                    if(k < gridSize-1)
                        cout << "+";
                }
                cout << endl;
            }
        }
        cout << endl;
    }

    // Function that performs one player's move
    bool makeMove(int position)
    {
        // Check if move is inside the valid range
        if(position < 1 || position > gridSize*gridSize)
        {
            cout << "Invalid move! Choose between 1 and " << gridSize*gridSize << "." << endl;
            return false;
        }

        // Check if the chosen cell is already occupied
        if(board[position-1] == "X" || board[position-1] == "O")
        {
            cout << "That position is already taken!" << endl;
            return false;
        }

        // Place symbol based on whose turn it is
        if(currentTurn == 1)
        {
            board[position-1] = "X";
            currentTurn = 2;   // switch turn to player 2
        }
        else
        {
            board[position-1] = "O";
            currentTurn = 1;   // switch turn to player 1
        }

        return true;
    }

    // Function to check if a player has won
    bool checkWinner(string symbol)
    {
        // Check all rows
        for(int row=0;row<gridSize;row++)
        {
            bool win = true;
            for(int col=0;col<gridSize;col++)
            {
                if(board[row*gridSize + col] != symbol)
                {
                    win = false;
                    break;
                }
            }
            if(win)
                return true;
        }

        // Check all columns
        for(int col=0;col<gridSize;col++)
        {
            bool win = true;
            for(int row=0;row<gridSize;row++)
            {
                if(board[row*gridSize + col] != symbol)
                {
                    win = false;
                    break;
                }
            }
            if(win)
                return true;
        }

        // Check main diagonal (top-left to bottom-right)
        bool mainDiag = true;
        for(int i=0;i<gridSize;i++)
        {
            if(board[i*gridSize + i] != symbol)
            {
                mainDiag = false;
                break;
            }
        }
        if(mainDiag)
            return true;

        // Check anti-diagonal (top-right to bottom-left)
        bool antiDiag = true;
        for(int i=0;i<gridSize;i++)
        {
            if(board[i*gridSize + (gridSize-1-i)] != symbol)
            {
                antiDiag = false;
                break;
            }
        }
        if(antiDiag)
            return true;

        return false;  // no win found
    }

    // Function to check if all cells are filled (for draw)
    bool isBoardFull()
    {
        for(int i=0;i<gridSize*gridSize;i++)
        {
            if(board[i] != "X" && board[i] != "O")
                return false;
        }
        return true;
    }

    // Function to control the full game flow
    void playGame()
    {
        int move;

        while(true)
        {
            displayBoard();  // show current board state

            // Ask the current player for input
            if(currentTurn == 1)
                cout << "Player 1 (X), enter your move: ";
            else
                cout << "Player 2 (O), enter your move: ";

            cin >> move;

            // Check if input is a valid number
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Please enter a number only." << endl;
                continue;
            }

            // If move is invalid or cell occupied, ask again
            if(!makeMove(move))
                continue;

            // Check for Player 1 win
            if(checkWinner("X"))
            {
                displayBoard();
                cout << "Player 1 (X) wins!" << endl;
                break;
            }

            // Check for Player 2 win
            else if(checkWinner("O"))
            {
                displayBoard();
                cout << "Player 2 (O) wins!" << endl;
                break;
            }

            // Check if the game is a draw
            else if(isBoardFull())
            {
                displayBoard();
                cout << "It's a draw!" << endl;
                break;
            }
        }
    }
};

int main()
{
	int size = 3;
    // Create game object and start the game
    TicTacToe game(size);
    game.playGame();

    return 0;
}

