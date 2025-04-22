#ifndef TRANSACTION_H
#define TRANSACTION_H

const int MAX_TRANSACTIONS = 1000;
const int MAX_BOOKS_PER_TRANSACTION = 5;

// Transaction data stored in parallel arrays
extern char transactionReaderIds[MAX_TRANSACTIONS][10];
extern int transactionBorrowDays[MAX_TRANSACTIONS];
extern int transactionBorrowMonths[MAX_TRANSACTIONS];
extern int transactionBorrowYears[MAX_TRANSACTIONS];
extern int transactionExpectedReturnDays[MAX_TRANSACTIONS];
extern int transactionExpectedReturnMonths[MAX_TRANSACTIONS];
extern int transactionExpectedReturnYears[MAX_TRANSACTIONS];
extern int transactionActualReturnDays[MAX_TRANSACTIONS];
extern int transactionActualReturnMonths[MAX_TRANSACTIONS];
extern int transactionActualReturnYears[MAX_TRANSACTIONS];
extern char transactionBookIsbns[MAX_TRANSACTIONS][MAX_BOOKS_PER_TRANSACTION][13];
extern bool transactionBookReturned[MAX_TRANSACTIONS][MAX_BOOKS_PER_TRANSACTION];
extern bool transactionBookLost[MAX_TRANSACTIONS][MAX_BOOKS_PER_TRANSACTION];
extern int transactionBookCount[MAX_TRANSACTIONS];
extern float transactionFines[MAX_TRANSACTIONS];
extern int transactionCount;

void transactionManagementMenu();
void borrowBooks();
void returnBooks();

#endif