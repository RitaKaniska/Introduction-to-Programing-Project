#include "stats.h"
#include "reader.h"
#include "book.h"
#include "transaction.h"
#include <iostream>
#include <cstring>

using namespace std;

void statisticsMenu() {
    int choice;
    do {
        cout << "\nSTATISTICS MENU\n";
        cout << "1. Total Books\n";
        cout << "2. Books by Genre\n";
        cout << "3. Total Readers\n";
        cout << "4. Readers by Gender\n";
        cout << "5. Currently Borrowed Books\n";
        cout << "6. Overdue Readers\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: displayBookCount(); break;
            case 2: displayBooksByGenre(); break;
            case 3: displayReaderCount(); break;
            case 4: displayReadersByGender(); break;
            case 5: displayBorrowedBooks(); break;
            case 6: displayOverdueReaders(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void displayBookCount() {
    int totalBooks = 0;
    for (int i = 0; i < bookCount; i++) {
        totalBooks += bookQuantities[i];
    }
    
    cout << "Total books in library: " << totalBooks << "\n";
    cout << "Unique titles: " << bookCount << "\n";
}

void displayBooksByGenre() {
    if (bookCount == 0) {
        cout << "No books in the system.\n";
        return;
    }
    
    const int MAX_GENRES = 10;
    char genres[MAX_GENRES][MAX_GENRE_LENGTH] = {};
    int genreCounts[MAX_GENRES] = {};
    int genreCount = 0;
    
    for (int i = 0; i < bookCount; i++) {
        bool genreExists = false;
        for (int j = 0; j < genreCount; j++) {
            if (strcmp(bookGenres[i], genres[j]) == 0) {
                genreCounts[j] += bookQuantities[i];
                genreExists = true;
                break;
            }
        }
        
        if (!genreExists && genreCount < MAX_GENRES) {
            strcpy(genres[genreCount], bookGenres[i]);
            genreCounts[genreCount] = bookQuantities[i];
            genreCount++;
        }
    }
    
    cout << "Books by genre:\n";
    for (int i = 0; i < genreCount; i++) {
        cout << " - " << genres[i] << ": " << genreCounts[i] << " books\n";
    }
}

void displayReaderCount() {
    cout << "Total readers: " << readerCount << "\n";
}

void displayReadersByGender() {
    int maleCount = 0, femaleCount = 0;
    for (int i = 0; i < readerCount; i++) {
        if (readerGenders[i] == 'M' || readerGenders[i] == 'm') {
            maleCount++;
        } else {
            femaleCount++;
        }
    }
    
    cout << "Male readers: " << maleCount << "\n";
    cout << "Female readers: " << femaleCount << "\n";
}

void displayBorrowedBooks() {
    int totalBorrowed = 0;
    
    cout << "Currently borrowed books:\n";
    for (int i = 0; i < transactionCount; i++) {
        for (int j = 0; j < transactionBookCount[i]; j++) {
            if (!transactionBookReturned[i][j]) {
                totalBorrowed++;
                // Find book title
                for (int k = 0; k < bookCount; k++) {
                    if (strcmp(bookIsbns[k], transactionBookIsbns[i][j]) == 0) {
                        cout << " - " << bookTitles[k] << " (ISBN: " << bookIsbns[k] 
                             << ") borrowed by reader ID: " << transactionReaderIds[i] << "\n";
                        break;
                    }
                }
            }
        }
    }
    
    if (totalBorrowed == 0) {
        cout << "No books currently borrowed.\n";
    } else {
        cout << "Total borrowed books: " << totalBorrowed << "\n";
    }
}

void displayOverdueReaders() {
    int currentDay, currentMonth, currentYear;
    cout << "Enter current date (dd mm yyyy): ";
    cin >> currentDay >> currentMonth >> currentYear;
    cin.ignore();
    
    cout << "Readers with overdue books:\n";
    bool foundOverdue = false;
    
    for (int i = 0; i < transactionCount; i++) {
        bool isOverdue = false;
        
        // Check if transaction has unreturned books
        for (int j = 0; j < transactionBookCount[i]; j++) {
            if (!transactionBookReturned[i][j]) {
                // Check if expected return date is before current date
                if (transactionExpectedReturnYears[i] < currentYear ||
                    (transactionExpectedReturnYears[i] == currentYear && 
                     transactionExpectedReturnMonths[i] < currentMonth) ||
                    (transactionExpectedReturnYears[i] == currentYear && 
                     transactionExpectedReturnMonths[i] == currentMonth && 
                     transactionExpectedReturnDays[i] < currentDay)) {
                    isOverdue = true;
                    break;
                }
            }
        }
        
        if (isOverdue) {
            foundOverdue = true;
            // Find reader name
            for (int k = 0; k < readerCount; k++) {
                if (strcmp(readerIds[k], transactionReaderIds[i]) == 0) {
                    cout << " - " << readerNames[k] << " (ID: " << readerIds[k] 
                         << "), expected return: " << transactionExpectedReturnDays[i] << "/"
                         << transactionExpectedReturnMonths[i] << "/"
                         << transactionExpectedReturnYears[i] << "\n";
                    break;
                }
            }
        }
    }
    
    if (!foundOverdue) {
        cout << "No readers with overdue books.\n";
    }
}