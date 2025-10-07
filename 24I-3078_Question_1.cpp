#include <iostream>
#include <conio.h>   // For _getch() to detect keys without pressing Enter
using namespace std;

// Node structure for linked list
struct Node {
    char data;       // Stores a single character
    Node* next;      // Pointer to the next node in the list
    Node(char ch) {
        data = ch;
        next = NULL;
    }
};

// LinkedList class for storing characters and checking palindrome
class LinkedList {
private:
    Node* head;      // Pointer to the first node of the list

public:
    // Constructor initializes an empty list
    LinkedList() 
	{
        head = NULL;
    }

    // Function to insert a new character at the end of the list
    void insertChar(char ch) 
	{
        Node* newNode = new Node(ch);
        if (head == NULL)               // If list is empty, new node becomes the head
            head = newNode;
        else 
		{
            Node* temp = head;
            while (temp->next != NULL)  // Traverse to the end of the list
                temp = temp->next;
            temp->next = newNode;       // Link new node at the end
        }
    }

    // Function to check if the linked list forms a palindrome
    bool isPalindrome() 
	{
        int length = 0;
        Node* temp = head;

        // Count total number of nodes in the list
        while (temp != NULL) 
		{
            length++;
            temp = temp->next;
        }

        // A single letter or empty word is always a palindrome
        if (length <= 1) return true;

        // Create a dynamic array to store all characters for comparison
        char* arr = new char[length];
        temp = head;

        // Copy all characters from the list into the array
        for (int i = 0; i < length; i++) 
		{
            arr[i] = temp->data;
            temp = temp->next;
        }

        // Compare characters from both ends to check palindrome property
        bool palindrome = true;
        for (int i = 0; i < length / 2; i++) 
		{
            if (arr[i] != arr[length - 1 - i]) 
			{
                palindrome = false;
                break;
            }
        }

        delete[] arr;  // Free allocated memory
        return palindrome;  // Return true if palindrome, false otherwise
    }

    // Function to clear all nodes and free memory
    void clear() 
	{
        Node* temp;
        while (head != NULL) 
		{
            temp = head;
            head = head->next;
            delete temp;  // Delete each node one by one
        }
    }

    // Destructor automatically clears memory when object is destroyed
    ~LinkedList() 
	{
        clear();
    }
};

// Function to check whether a character is an alphabet (A-Z or a-z)
bool isAlphabet(char ch) 
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

int main() 
{
    cout << "=== Palindrome Checker ===\n";
    cout << "Press 'Esc' anytime to quit.\n\n";

    while (true) 
	{
        cout << "Enter a word: ";

        LinkedList list;          // Create a linked list to store characters
        char ch;
        bool invalidInput = false;

        // Take input character by character using _getch()
        while (true) 
		{
            ch = _getch();        // Reads a single character from keyboard (no Enter needed)

            if (ch == 27) 
			{ // ESC key pressed
                cout << "\nExiting program. Goodbye!\n";
                return 0;         // End the program
            } 
			else if (ch == 13) 
			{ // ENTER key pressed
                cout << endl;     // Move to next line
                break;            // End input for this word
            } 
            else 
			{
                // Allow only alphabetic characters
                if (!isAlphabet(ch)) 
				{
                    cout << "\nInvalid input! Only letters are allowed.\n";
                    invalidInput = true;
                    break;        // Stop reading this word
                }

                cout << ch;       // Display the typed character
                list.insertChar(ch); // Store character in linked list
            }
        }

        // If user entered invalid input, skip checking
        if (invalidInput) 
		{
            cout << "Please try again with letters only.\n\n";
            continue; // Restart input loop
        }

        // Check and display whether input is palindrome
        if (list.isPalindrome())
            cout << "Result: Palindrome\n\n";
        else
            cout << "Result: Not Palindrome\n\n";
    }

    return 0;
}

