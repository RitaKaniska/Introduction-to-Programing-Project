#include <iostream>
#include "reader.h"
#include "book.h"
#include "transaction.h"
#include "stats.h"

using namespace std;

void showMainMenu() {
    cout << "\nLIBRARY MANAGEMENT SYSTEM\n";
    cout << "1. Reader Management\n";
    cout << "2. Book Management\n";
    cout << "3. Borrow/Return Books\n";
    cout << "4. Statistics\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMainMenu();
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: readerManagementMenu(); break;
            case 2: bookManagementMenu(); break;
            case 3: transactionManagementMenu(); break;
            case 4: statisticsMenu(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
    
    return 0;
}