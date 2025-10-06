#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// Utility class: Handles file reading
class WordLoader {
public:
    static int loadWordsFromFile(const string& filename, string words[], int maxWords) 
	{
        ifstream file(filename);
        if (!file) 
		{
            cerr << "Error: Could not open " << filename << endl;
            return 0;
        }

        int count = 0;
        while (count < maxWords && getline(file, words[count])) 
		{
            if (!words[count].empty()) 
			{
                // Convert to uppercase manually
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
        return count; // number of words loaded
    }
};

// Hangman Game Class
class Hangman {
private:
    string secretWord;
    string displayWord;
    int remainingMistakes;
    char guessedLetters[26];
    int guessedCount;

public:
    Hangman(const string& word, int maxMistakes = 7) 
	{
        secretWord = word;
        displayWord = string(secretWord.length(), '_');
        remainingMistakes = maxMistakes;
        guessedCount = 0;
    }

    // Show current game state
    void displayStatus() const 
	{
        cout << "\nWord: ";
        for (int i = 0; i < displayWord.length(); i++)
            cout << displayWord[i] << " ";
        cout << "\nRemaining Mistakes: " << remainingMistakes << endl;
        cout << "Guessed Letters: ";
        for (int i = 0; i < guessedCount; i++)
            cout << guessedLetters[i] << " ";
        cout << endl;
    }

    // Check if letter already guessed
    bool alreadyGuessed(char letter) const 
	{
        for (int i = 0; i < guessedCount; i++) 
		{
            if (guessedLetters[i] == letter)
                return true;
        }
        return false;
    }

    // Convert lowercase to uppercase manually
    char toUpperManual(char ch) 
	{
        if (ch >= 'a' && ch <= 'z')
            ch = ch - 'a' + 'A';
        return ch;
    }

    // Check if input is an alphabet letter
    bool isAlphabet(char ch) 
	{
        return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
    }

    // Handle guessing a letter
    void guessLetter(char letter) 
	{
        letter = toUpperManual(letter);

        if (!isAlphabet(letter)) 
		{
            cout << "Invalid input! Please enter an alphabet letter.\n";
            return;
        }

        if (alreadyGuessed(letter)) 
		{
            cout << "You already guessed '" << letter << "'. Try another letter.\n";
            return;
        }

        guessedLetters[guessedCount++] = letter;
        bool found = false;

        for (int i = 0; i < secretWord.length(); i++) 
		{
            if (secretWord[i] == letter) 
			{
                displayWord[i] = letter;
                found = true;
            }
        }

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

    // Check win condition
    bool isWordGuessed() const 
	{
        for (int i = 0; i < secretWord.length(); i++) 
		{
            if (displayWord[i] != secretWord[i])
                return false;
        }
        return true;
    }

    // Check lose condition
    bool isOutOfMistakes() const 
	{
        return remainingMistakes <= 0;
    }
};

// Game Controller: Manages full game flow
class GameController {
public:
    void startGame() 
	{
        const int MAX_WORDS = 100;
        string words[MAX_WORDS];
        int totalWords = WordLoader::loadWordsFromFile("words.txt", words, MAX_WORDS);

        if (totalWords == 0) 
		{
            cerr << "No words available. Please add words to 'words.txt'.\n";
            return;
        }

        srand(time(0));
        string selectedWord = words[rand() % totalWords];

        Hangman game(selectedWord);

        cout << "==============================\n";
        cout << "       Welcome to Hangman     \n";
        cout << "==============================\n";

        while (true) 
		{
            game.displayStatus();

            cout << "\nEnter a letter: ";
            char guess;
            cin >> guess;

            game.guessLetter(guess);

            if (game.isWordGuessed()) 
			{
                cout << "\nCongratulations! You guessed the word: " << selectedWord << endl;
                break;
            }

            if (game.isOutOfMistakes()) 
			{
                cout << "\nGame Over! The correct word was: " << selectedWord << endl;
                break;
            }
        }
    }
};

int main() {
    GameController controller;
    controller.startGame();
    return 0;
}

