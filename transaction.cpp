#include "transaction.h"
#include "reader.h"
#include "book.h"
#include <iostream>
#include <cstring>

using namespace std;

// Initialize transaction arrays
char transactionReaderIds[MAX_TRANSACTIONS][10] = {};
int transactionBorrowDays[MAX_TRANSACTIONS] = {};
int transactionBorrowMonths[MAX_TRANSACTIONS] = {};
int transactionBorrowYears[MAX_TRANSACTIONS] = {};
int transactionExpectedReturnDays[MAX_TRANSACTIONS] = {};
int transactionExpectedReturnMonths[MAX_TRANSACTIONS] = {};
int transactionExpectedReturnYears[MAX_TRANSACTIONS] = {};
int transactionActualReturnDays[MAX_TRANSACTIONS] = {};
int transactionActualReturnMonths[MAX_TRANSACTIONS] = {};
int transactionActualReturnYears[MAX_TRANSACTIONS] = {};
char transactionBookIsbns[MAX_TRANSACTIONS][MAX_BOOKS_PER_TRANSACTION][10] = {};
bool transactionBookReturned[MAX_TRANSACTIONS][MAX_BOOKS_PER_TRANSACTION] = {};
bool transactionBookLost[MAX_TRANSACTIONS][MAX_BOOKS_PER_TRANSACTION] = {};
int transactionBookCount[MAX_TRANSACTIONS] = {};
float transactionFines[MAX_TRANSACTIONS] = {};
int transactionCount = 0;

void transactionManagementMenu() {
    int choice;
    do {
        cout << "\nBORROW/RETURN MANAGEMENT\n";
        cout << "1. Borrow Books\n";
        cout << "2. Return Books\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: 
                borrowBooks();
                break;
            case 2: 
                returnBooks();
                break;
            case 0: 
                break;
            default: 
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void borrowBooks() {
    if (transactionCount >= MAX_TRANSACTIONS) {
        cout << "Maximum number of transactions reached.\n";
        return;
    }
    
    char readerId[ID_LENGTH];
    cout << "Enter reader ID: ";
    cin.getline(readerId, ID_LENGTH);
    
    // Verify reader exists
    bool readerFound = false;
    for (int i = 0; i < readerCount; i++) {
        if (strcmp(readerIds[i], readerId) == 0) {
            readerFound = true;
            break;
        }
    }
    
    if (!readerFound) {
        cout << "Reader not found.\n";
        return;
    }
    
    // Initialize new transaction
    strcpy(transactionReaderIds[transactionCount], readerId);
    transactionBookCount[transactionCount] = 0;
    transactionFines[transactionCount] = 0.0f;
    
    cout << "Enter borrow date (dd mm yyyy): ";
    cin >> transactionBorrowDays[transactionCount] 
        >> transactionBorrowMonths[transactionCount] 
        >> transactionBorrowYears[transactionCount];
    cin.ignore();
    
    // Calculate expected return date (7 days after borrow date)
    transactionExpectedReturnDays[transactionCount] = transactionBorrowDays[transactionCount] + 7;
    transactionExpectedReturnMonths[transactionCount] = transactionBorrowMonths[transactionCount];
    transactionExpectedReturnYears[transactionCount] = transactionBorrowYears[transactionCount];
    
    // Handle date overflow
    if (transactionExpectedReturnDays[transactionCount] > 31) {
        transactionExpectedReturnDays[transactionCount] -= 31;
        transactionExpectedReturnMonths[transactionCount]++;
    }
    if (transactionExpectedReturnMonths[transactionCount] > 12) {
        transactionExpectedReturnMonths[transactionCount] = 1;
        transactionExpectedReturnYears[transactionCount]++;
    }
    
    char choice;
    do {
        if (transactionBookCount[transactionCount] >= MAX_BOOKS_PER_TRANSACTION) {
            cout << "Maximum number of books per transaction reached.\n";
            break;
        }
        
        char isbn[ISBN_LENGTH];
        cout << "Enter ISBN of book to borrow: ";
        cin.getline(isbn, ISBN_LENGTH);
        
        // Verify book exists and is available
        bool bookFound = false;
        for (int i = 0; i < bookCount; i++) {
            if (strcmp(bookIsbns[i], isbn) == 0 && bookQuantities[i] > 0) {
                bookFound = true;
                
                // Add book to transaction
                strcpy(transactionBookIsbns[transactionCount][transactionBookCount[transactionCount]], isbn);
                transactionBookReturned[transactionCount][transactionBookCount[transactionCount]] = false;
                transactionBookLost[transactionCount][transactionBookCount[transactionCount]] = false;
                transactionBookCount[transactionCount]++;
                
                cout << "Book added to transaction.\n";
                break;
            }
        }
        
        if (!bookFound) {
            cout << "Book not found or not available.\n";
        }
        
        cout << "Add another book? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');
    
    if (transactionBookCount[transactionCount] > 0) {
        transactionCount++;
        cout << "Transaction recorded successfully.\n";
    } else {
        cout << "No books added. Transaction cancelled.\n";
    }
}

void returnBooks() {
    char readerId[ID_LENGTH];
    cout << "Enter reader ID: ";
    cin.getline(readerId, ID_LENGTH);
    
    bool foundTransactions = false;
    
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactionReaderIds[i], readerId) == 0) {
            // Check if transaction has unreturned books
            bool hasUnreturned = false;
            for (int j = 0; j < transactionBookCount[i]; j++) {
                if (!transactionBookReturned[i][j]) {
                    hasUnreturned = true;
                    break;
                }
            }
            
            if (hasUnreturned) {
                foundTransactions = true;
                cout << "\nTransaction found (Borrowed on: " 
                     << transactionBorrowDays[i] << "/"
                     << transactionBorrowMonths[i] << "/"
                     << transactionBorrowYears[i] << ")\n";
                
                cout << "Books borrowed:\n";
                for (int j = 0; j < transactionBookCount[i]; j++) {
                    if (!transactionBookReturned[i][j]) {
                        // Find book details
                        for (int k = 0; k < bookCount; k++) {
                            if (strcmp(bookIsbns[k], transactionBookIsbns[i][j]) == 0) {
                                cout << " - " << bookTitles[k] << " (ISBN: " << bookIsbns[k] << ")\n";
                                break;
                            }
                        }
                    }
                }
                
                cout << "Enter return date (dd mm yyyy): ";
                int returnDay, returnMonth, returnYear;
                cin >> returnDay >> returnMonth >> returnYear;
                cin.ignore();
                
                transactionActualReturnDays[i] = returnDay;
                transactionActualReturnMonths[i] = returnMonth;
                transactionActualReturnYears[i] = returnYear;
                
                // Calculate fine for each book
                float totalFine = 0;
                for (int j = 0; j < transactionBookCount[i]; j++) {
                    if (!transactionBookReturned[i][j]) {
                        char lost;
                        cout << "Is book " << transactionBookIsbns[i][j] << " lost? (y/n): ";
                        cin >> lost;
                        cin.ignore();
                        
                        if (lost == 'y' || lost == 'Y') {
                            transactionBookLost[i][j] = true;
                            // Find book price
                            for (int k = 0; k < bookCount; k++) {
                                if (strcmp(bookIsbns[k], transactionBookIsbns[i][j]) == 0) {
                                    totalFine += bookPrices[k] * 2; // 200% of price
                                    break;
                                }
                            }
                        } else {
                            // Calculate late days
                            int lateDays = 0;
                            if (returnYear > transactionExpectedReturnYears[i] ||
                                (returnYear == transactionExpectedReturnYears[i] && 
                                 returnMonth > transactionExpectedReturnMonths[i]) ||
                                (returnYear == transactionExpectedReturnYears[i] && 
                                 returnMonth == transactionExpectedReturnMonths[i] && 
                                 returnDay > transactionExpectedReturnDays[i])) {
                                // Simplified date difference calculation
                                lateDays = returnDay - transactionExpectedReturnDays[i];
                                if (lateDays < 0) lateDays = 0;
                            }
                            
                            if (lateDays > 0) {
                                totalFine += lateDays * 5000; // 5000 per day
                                cout << "Late return for book " << transactionBookIsbns[i][j] 
                                     << ": " << lateDays << " days, fine: " << lateDays * 5000 << " VND\n";
                            }
                        }
                        
                        transactionBookReturned[i][j] = true;
                    }
                }
                
                transactionFines[i] = totalFine;
                if (totalFine > 0) {
                    cout << "Total fine: " << totalFine << " VND\n";
                } else {
                    cout << "No fines applied.\n";
                }
                
                cout << "Return processed successfully.\n";
            }
        }
    }
    
    if (!foundTransactions) {
        cout << "No active borrowings found for this reader.\n";
    }
}