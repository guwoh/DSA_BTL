#include<string.h>

struct BorrowSlip {
    string slipID;
    string readerID;
    string bookID;
    string borrowDate;
    string dueDate;
    string returnDate;
    bool isReturned;
    BorrowSlip* next;
};

void createBorrowSlip();
void returnBook();
void listBorrowSlips();
void listUnreturnedBooks();
void checkBorrowConditions();