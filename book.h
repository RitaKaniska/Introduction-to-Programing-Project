#ifndef BOOK_H
#define BOOK_H

const int MAX_BOOKS = 1000;
const int MAX_TITLE_LENGTH = 100;
const int MAX_AUTHOR_LENGTH = 50;
const int MAX_PUBLISHER_LENGTH = 50;
const int MAX_GENRE_LENGTH = 30;
const int ISBN_LENGTH = 13;

// Book data stored in parallel arrays
extern char bookIsbns[MAX_BOOKS][ISBN_LENGTH];
extern char bookTitles[MAX_BOOKS][MAX_TITLE_LENGTH];
extern char bookAuthors[MAX_BOOKS][MAX_AUTHOR_LENGTH];
extern char bookPublishers[MAX_BOOKS][MAX_PUBLISHER_LENGTH];
extern int bookYears[MAX_BOOKS];
extern char bookGenres[MAX_BOOKS][MAX_GENRE_LENGTH];
extern float bookPrices[MAX_BOOKS];
extern int bookQuantities[MAX_BOOKS];
extern int bookCount;

void bookManagementMenu();
void addBook();
void editBook();
void deleteBook();
void displayAllBooks();
void searchBookByISBN();
void searchBookByTitle();

#endif