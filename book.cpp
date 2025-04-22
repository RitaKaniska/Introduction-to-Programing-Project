#include "book.h"
#include <iostream>
#include <cstring>

using namespace std;

// Initialize book arrays
char bookIsbns[MAX_BOOKS][ISBN_LENGTH] = {};
char bookTitles[MAX_BOOKS][MAX_TITLE_LENGTH] = {};
char bookAuthors[MAX_BOOKS][MAX_AUTHOR_LENGTH] = {};
char bookPublishers[MAX_BOOKS][MAX_PUBLISHER_LENGTH] = {};
int bookYears[MAX_BOOKS] = {};
char bookGenres[MAX_BOOKS][MAX_GENRE_LENGTH] = {};
float bookPrices[MAX_BOOKS] = {};
int bookQuantities[MAX_BOOKS] = {};
int bookCount = 0;

void bookManagementMenu() {
    int choice;
    do {
        cout << "\nBOOK MANAGEMENT\n";
        cout << "1. Add Book\n";
        cout << "2. Edit Book\n";
        cout << "3. Delete Book\n";
        cout << "4. View All Books\n";
        cout << "5. Search by ISBN\n";
        cout << "6. Search by Title\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: addBook(); break;
            case 2: editBook(); break;
            case 3: deleteBook(); break;
            case 4: displayAllBooks(); break;
            case 5: searchBookByISBN(); break;
            case 6: searchBookByTitle(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}



void addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "Maximum number of books reached.\n";
        return;
    }
    
    cout << "Enter ISBN: ";
    cin.getline(bookIsbns[bookCount], ISBN_LENGTH);
    
    // Check for duplicate ISBN
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(bookIsbns[i], bookIsbns[bookCount]) == 0) {
            cout << "Book with this ISBN already exists.\n";
            return;
        }
    }
    
    cout << "Enter title: ";
    cin.getline(bookTitles[bookCount], MAX_TITLE_LENGTH);
    
    cout << "Enter author: ";
    cin.getline(bookAuthors[bookCount], MAX_AUTHOR_LENGTH);
    
    cout << "Enter publisher: ";
    cin.getline(bookPublishers[bookCount], MAX_PUBLISHER_LENGTH);
    
    cout << "Enter publication year: ";
    cin >> bookYears[bookCount];
    cin.ignore();
    
    cout << "Enter genre: ";
    cin.getline(bookGenres[bookCount], MAX_GENRE_LENGTH);
    
    cout << "Enter price: ";
    cin >> bookPrices[bookCount];
    cin.ignore();
    
    cout << "Enter quantity: ";
    cin >> bookQuantities[bookCount];
    cin.ignore();
    
    bookCount++;
    cout << "Book added successfully.\n";
}

void editBook() {
    char isbn[ISBN_LENGTH];
    cout << "Enter ISBN of book to edit: ";
    cin.getline(isbn, ISBN_LENGTH);
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(bookIsbns[i], isbn) == 0) {
            cout << "Editing book: " << bookTitles[i] << endl;
            
            cout << "Enter new title (current: " << bookTitles[i] << "): ";
            cin.getline(bookTitles[i], MAX_TITLE_LENGTH);
            
            cout << "Enter new author (current: " << bookAuthors[i] << "): ";
            cin.getline(bookAuthors[i], MAX_AUTHOR_LENGTH);
            
            cout << "Enter new publisher (current: " << bookPublishers[i] << "): ";
            cin.getline(bookPublishers[i], MAX_PUBLISHER_LENGTH);
            
            cout << "Enter new publication year (current: " << bookYears[i] << "): ";
            cin >> bookYears[i];
            cin.ignore();
            
            cout << "Enter new genre (current: " << bookGenres[i] << "): ";
            cin.getline(bookGenres[i], MAX_GENRE_LENGTH);
            
            cout << "Enter new price (current: " << bookPrices[i] << "): ";
            cin >> bookPrices[i];
            cin.ignore();
            
            cout << "Enter new quantity (current: " << bookQuantities[i] << "): ";
            cin >> bookQuantities[i];
            cin.ignore();
            
            cout << "Book information updated.\n";
            return;
        }
    }
    
    cout << "Book not found.\n";
}

void deleteBook() {
    char isbn[ISBN_LENGTH];
    cout << "Enter ISBN of book to delete: ";
    cin.getline(isbn, ISBN_LENGTH);
    
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(bookIsbns[i], isbn) == 0) {
            // Shift all elements after i one position left
            for (int j = i; j < bookCount - 1; j++) {
                strcpy(bookIsbns[j], bookIsbns[j+1]);
                strcpy(bookTitles[j], bookTitles[j+1]);
                strcpy(bookAuthors[j], bookAuthors[j+1]);
                strcpy(bookPublishers[j], bookPublishers[j+1]);
                bookYears[j] = bookYears[j+1];
                strcpy(bookGenres[j], bookGenres[j+1]);
                bookPrices[j] = bookPrices[j+1];
                bookQuantities[j] = bookQuantities[j+1];
            }
            bookCount--;
            cout << "Book deleted successfully.\n";
            return;
        }
    }
    
    cout << "Book not found.\n";
}

void displayAllBooks() {
    if (bookCount == 0) {
        cout << "No books in the system.\n";
        return;
    }
    
    cout << "\nLIST OF BOOKS\n";
    for (int i = 0; i < bookCount; i++) {
        cout << "ISBN: " << bookIsbns[i] << "\n";
        cout << "Title: " << bookTitles[i] << "\n";
        cout << "Author: " << bookAuthors[i] << "\n";
        cout << "Publisher: " << bookPublishers[i] << "\n";
        cout << "Year: " << bookYears[i] << "\n";
        cout << "Genre: " << bookGenres[i] << "\n";
        cout << "Price: " << bookPrices[i] << "\n";
        cout << "Quantity: " << bookQuantities[i] << "\n";
        cout << "----------------------------\n";
    }
}

void searchBookByISBN() {
    char isbn[ISBN_LENGTH];
    cout << "Enter ISBN to search: ";
    cin.getline(isbn, ISBN_LENGTH);
    
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(bookIsbns[i], isbn) == 0) {
            cout << "Book found:\n";
            cout << "ISBN: " << bookIsbns[i] << "\n";
            cout << "Title: " << bookTitles[i] << "\n";
            cout << "Author: " << bookAuthors[i] << "\n";
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "No book found with that ISBN.\n";
    }
}

void searchBookByTitle() {
    char title[MAX_TITLE_LENGTH];
    cout << "Enter title to search: ";
    cin.getline(title, MAX_TITLE_LENGTH);
    
    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(bookTitles[i], title) != nullptr) {
            cout << "ISBN: " << bookIsbns[i] << "\n";
            cout << "Title: " << bookTitles[i] << "\n";
            cout << "Author: " << bookAuthors[i] << "\n";
            cout << "----------------------------\n";
            found = true;
        }
    }
    
    if (!found) {
        cout << "No books found with that title.\n";
    }
}