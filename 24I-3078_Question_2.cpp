#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>   // For _getch() to read keys without pressing Enter
using namespace std;

// Class: WordLoader
// Purpose: Load words from a file into an array
class WordLoader {
public:
    static int loadWordsFromFile(const string& filename, string words[], int maxWords) 
	{
        ifstream file(filename);
        if (!file) 
		{
            cerr << "Error: Could not open " << filename << endl;
            return 0;   // No words loaded if file not found
        }

        int count = 0;
        // Read each line from file and store as a word
        while (count < maxWords && getline(file, words[count])) 
		{
            if (!words[count].empty()) 
			{
                // Convert all letters to uppercase manually
                for (int i = 0; i < words[count].length(); i++) 
				{
                    if (words[count][i] >= 'a' && words[count][i] <= 'z') 
					{
                        words[count][i] = words[count][i] - 'a' + 'A';
                    }
                }
                count++;
            }
        }

        file.close();
        return count; // Return number of words successfully loaded
    }
};


// Class: Hangman
// Purpose: Handle the logic of guessing, mistakes, and word checking
class Hangman {
private:
    string secretWord;        // The actual word to be guessed
    string displayWord;       // The word shown to player with hidden letters
    int remainingMistakes;    // How many wrong guesses allowed
    char guessedLetters[26];  // Store already guessed letters
    int guessedCount;         // Number of guessed letters so far

public:
    // Constructor initializes game with secret word and max mistakes
    Hangman(const string& word, int maxMistakes = 7) 
	{
        secretWord = word;
        displayWord = string(secretWord.length(), '_'); // Hide all letters initially
        remainingMistakes = maxMistakes;
        guessedCount = 0;
    }

    // Display current game progress
    void displayStatus() const 
	{
        cout << "\nWord: ";
        for (int i = 0; i < displayWord.length(); i++)
            cout << displayWord[i] << " ";
        cout << "\nRemaining Mistakes: " << remainingMistakes << endl;

        // Show all guessed letters so far
        cout << "Guessed Letters: ";
        for (int i = 0; i < guessedCount; i++)
            cout << guessedLetters[i] << " ";
        cout << endl;
    }

    // Check if letter has already been guessed
    bool alreadyGuessed(char letter) const 
	{
        for (int i = 0; i < guessedCount; i++) 
		{
            if (guessedLetters[i] == letter)
                return true;
        }
        return false;
    }

    // Convert lowercase letters to uppercase manually
    char toUpperManual(char ch) 
	{
        if (ch >= 'a' && ch <= 'z')
            ch = ch - 'a' + 'A';
        return ch;
    }

    // Check if a character is an alphabet letter
    bool isAlphabet(char ch) 
	{
        return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
    }

    // Function to process player's guessed letter
    void guessLetter(char letter) 
	{
        letter = toUpperManual(letter);  // Convert input to uppercase

        // Validate input
        if (!isAlphabet(letter)) 
		{
            cout << "Invalid input! Please enter an alphabet letter.\n";
            return;
        }

        // Check if player already guessed this letter
        if (alreadyGuessed(letter)) 
		{
            cout << "You already guessed '" << letter << "'. Try another letter.\n";
            return;
        }

        guessedLetters[guessedCount++] = letter; // Store guessed letter
        bool found = false;

        // Reveal the letter in displayWord if it exists in secretWord
        for (int i = 0; i < secretWord.length(); i++) 
		{
            if (secretWord[i] == letter) 
			{
                displayWord[i] = letter;
                found = true;
            }
        }

        // If guess was incorrect, reduce remaining chances
        if (!found) 
		{
            remainingMistakes--;
            cout << "Incorrect guess! Remaining mistakes: " << remainingMistakes << endl;
        } 
		else 
		{
            cout << "Good job! '" << letter << "' is in the word.\n";
        }
    }

    // Check if player has guessed all letters correctly
    bool isWordGuessed() const 
	{
        for (int i = 0; i < secretWord.length(); i++) 
		{
            if (displayWord[i] != secretWord[i])
                return false;
        }
        return true;
    }

    // Check if player has run out of mistakes
    bool isOutOfMistakes() const 
	{
        return remainingMistakes <= 0;
    }
};


// Class: GameController
// Purpose: Manages the complete game flow
class GameController {
public:
    void startGame() 
	{
        const int MAX_WORDS = 100;         // Max words that can be loaded
        string words[MAX_WORDS];
        int totalWords = WordLoader::loadWordsFromFile("words.txt", words, MAX_WORDS);

        // If file is empty or missing
        if (totalWords == 0) 
		{
            cerr << "No words available. Please add words to 'words.txt'.\n";
            return;
        }

        // Randomly select one word from loaded list
        srand(time(0));
        string selectedWord = words[rand() % totalWords];

        // Create Hangman game object with chosen word
        Hangman game(selectedWord);
		char ch;
        bool invalidInput = false;

        cout << "==============================\n";
        cout << "       Welcome to Hangman     \n";
        cout << "==============================\n";

        // Main game loop
        while (true) 
		{
            game.displayStatus();  // Show current progress

            cout << "\nEnter a letter: ";
            char guess = _getch();  // Get a single character input

			// Allow player to quit at any time using ESC key
			if (guess == 27) 
			{
			    cout << "\nLeaving Game. Goodbye!\n";
			    return;
			}

			cout << guess << endl;  // Display guessed letter on screen
			
            // Process guessed letter
            game.guessLetter(guess);
			
            // Check if player has won
            if (game.isWordGuessed()) 
			{
                cout << "\nCongratulations! You guessed the word: " << selectedWord << endl;
                break;
            }

            // Check if player has lost
            if (game.isOutOfMistakes()) 
			{
                cout << "\nGame Over! The correct word was: " << selectedWord << endl;
                break;
            }
        }
    }
};

// Main Function

int main() {
    GameController controller;  // Create game controller object
    controller.startGame();     // Start the game
    return 0;
}

