#include "reader.h"
#include <iostream>
#include <cstring>

using namespace std;

// Initialize reader arrays
char readerIds[MAX_READERS][ID_LENGTH] = {};
char readerNames[MAX_READERS][MAX_NAME_LENGTH] = {};
char readerIdNumbers[MAX_READERS][ID_LENGTH] = {};
int readerBirthDays[MAX_READERS] = {};
int readerBirthMonths[MAX_READERS] = {};
int readerBirthYears[MAX_READERS] = {};
char readerGenders[MAX_READERS] = {};
char readerEmails[MAX_READERS][MAX_EMAIL_LENGTH] = {};
char readerAddresses[MAX_READERS][MAX_ADDRESS_LENGTH] = {};
int readerCardIssueDays[MAX_READERS] = {};
int readerCardIssueMonths[MAX_READERS] = {};
int readerCardIssueYears[MAX_READERS] = {};
int readerCardExpiryDays[MAX_READERS] = {};
int readerCardExpiryMonths[MAX_READERS] = {};
int readerCardExpiryYears[MAX_READERS] = {};
int readerCount = 0;

void readerManagementMenu() {
    int choice;
    do {
        cout << "\nREADER MANAGEMENT\n";
        cout << "1. Add Reader\n";
        cout << "2. Edit Reader\n";
        cout << "3. Delete Reader\n";
        cout << "4. View All Readers\n";
        cout << "5. Search by ID Number\n";
        cout << "6. Search by Name\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: addReader(); break;
            case 2: editReader(); break;
            case 3: deleteReader(); break;
            case 4: displayAllReaders(); break;
            case 5: searchReaderByIdNumber(); break;
            case 6: searchReaderByName(); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void addReader() {
    if (readerCount >= MAX_READERS) {
        cout << "Maximum number of readers reached.\n";
        return;
    }
    
    cout << "Enter reader ID: ";
    cin.getline(readerIds[readerCount], ID_LENGTH);
    
    cout << "Enter name: ";
    cin.getline(readerNames[readerCount], MAX_NAME_LENGTH);
    
    cout << "Enter ID number (CMND/CCCD): ";
    cin.getline(readerIdNumbers[readerCount], ID_LENGTH);
    
    cout << "Enter birth date (dd mm yyyy): ";
    cin >> readerBirthDays[readerCount] >> readerBirthMonths[readerCount] >> readerBirthYears[readerCount];
    cin.ignore();
    
    cout << "Enter gender (M/F): ";
    cin >> readerGenders[readerCount];
    cin.ignore();
    
    cout << "Enter email: ";
    cin.getline(readerEmails[readerCount], MAX_EMAIL_LENGTH);
    
    cout << "Enter address: ";
    cin.getline(readerAddresses[readerCount], MAX_ADDRESS_LENGTH);
    
    cout << "Enter card issue date (dd mm yyyy): ";
    cin >> readerCardIssueDays[readerCount] >> readerCardIssueMonths[readerCount] >> readerCardIssueYears[readerCount];
    cin.ignore();
    
    // Calculate expiry date (48 months later)
    readerCardExpiryDays[readerCount] = readerCardIssueDays[readerCount];
    readerCardExpiryMonths[readerCount] = readerCardIssueMonths[readerCount] + 4;
    readerCardExpiryYears[readerCount] = readerCardIssueYears[readerCount];
    
    if (readerCardExpiryMonths[readerCount] > 12) {
        readerCardExpiryMonths[readerCount] -= 12;
        readerCardExpiryYears[readerCount]++;
    }
    
    readerCount++;
    cout << "Reader added successfully.\n";
}

// Other reader functions implemented similarly...