#ifndef READER_H
#define READER_H

const int MAX_READERS = 100;
const int MAX_NAME_LENGTH = 50;
const int MAX_EMAIL_LENGTH = 50;
const int MAX_ADDRESS_LENGTH = 100;
const int ID_LENGTH = 10;

// Reader data stored in parallel arrays
extern char readerIds[MAX_READERS][ID_LENGTH];
extern char readerNames[MAX_READERS][MAX_NAME_LENGTH];
extern char readerIdNumbers[MAX_READERS][ID_LENGTH];
extern int readerBirthDays[MAX_READERS];
extern int readerBirthMonths[MAX_READERS];
extern int readerBirthYears[MAX_READERS];
extern char readerGenders[MAX_READERS];
extern char readerEmails[MAX_READERS][MAX_EMAIL_LENGTH];
extern char readerAddresses[MAX_READERS][MAX_ADDRESS_LENGTH];
extern int readerCardIssueDays[MAX_READERS];
extern int readerCardIssueMonths[MAX_READERS];
extern int readerCardIssueYears[MAX_READERS];
extern int readerCardExpiryDays[MAX_READERS];
extern int readerCardExpiryMonths[MAX_READERS];
extern int readerCardExpiryYears[MAX_READERS];
extern int readerCount;

void readerManagementMenu();
void addReader();
void editReader();
void deleteReader();
void displayAllReaders();
void searchReaderByIdNumber();
void searchReaderByName();

#endif