#include <iostream>
#include <conio.h>   // For _getch() to detect keys
using namespace std;

// Node structure for linked list
struct Node {
    char data;
    Node* next;
    Node(char ch) {
        data = ch;
        next = NULL;
    }
};

// LinkedList class for storing and checking palindrome
class LinkedList {
private:
    Node* head;

public:
    LinkedList() 
	{
        head = NULL;
    }

    void insertChar(char ch) 
	{
        Node* newNode = new Node(ch);
        if (head == NULL)
            head = newNode;
        else 
		{
            Node* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    bool isPalindrome() 
	{
        int length = 0;
        Node* temp = head;
        while (temp != NULL) 
		{
            length++;
            temp = temp->next;
        }

        if (length <= 1) return true;

        char* arr = new char[length];
        temp = head;
        for (int i = 0; i < length; i++) 
		{
            arr[i] = temp->data;
            temp = temp->next;
        }

        bool palindrome = true;
        for (int i = 0; i < length / 2; i++) 
		{
            if (arr[i] != arr[length - 1 - i]) 
			{
                palindrome = false;
                break;
            }
        }

        delete[] arr;
        return palindrome;
    }

    void clear() 
	{
        Node* temp;
        while (head != NULL) 
		{
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    ~LinkedList() 
	{
        clear();
    }
};

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

        LinkedList list;
        char ch;
        bool invalidInput = false;

        while (true) 
		{
            ch = _getch();

            if (ch == 27) 
			{ // ESC key
                cout << "\nExiting program. Goodbye!\n";
                return 0;
            } 
			else if (ch == 13) 
			{ // ENTER key
                cout << endl;
                break;
            } 
            else 
			{
                // Validate input
                if (!isAlphabet(ch)) 
				{
                    cout << "\nInvalid input! Only letters are allowed.\n";
                    invalidInput = true;
                    break;
                }
                cout << ch; 
                list.insertChar(ch);
            }
        }

        // Skip palindrome check if invalid input was detected
        if (invalidInput) 
		{
            cout << "Please try again with letters only.\n\n";
            continue;
        }

        // Check palindrome
        if (list.isPalindrome())
            cout << "Result: Palindrome\n\n";
        else
            cout << "Result: Not Palindrome\n\n";
    }

    return 0;
}

