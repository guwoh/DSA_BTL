#include <string.h>
#include <stdbool.h>

#ifndef LOAN_H
#define LOAN_H

#define MAX_ID_LEN 20
#define MAX_DATE_LEN 11

typedef struct BorrowSlip {
    char slipID[MAX_ID_LEN];
    char bookID[MAX_ID_LEN];
    char readerID[MAX_ID_LEN];
    char borrowDate[MAX_DATE_LEN];
    char dueDate[MAX_DATE_LEN];
    char returnDate[MAX_DATE_LEN]; // nếu chưa trả thì để rỗng
    struct BorrowSlip* next;
} BorrowSlip;

// Quản lý phiếu mượn
void createBorrowSlip(BorrowSlip** head);
void returnBook(BorrowSlip* head);
void listBorrowSlips(BorrowSlip* head);
void listUnreturnedBooks(BorrowSlip* head);
void checkBorrowConditions(BorrowSlip* head);

// Hàm kiểm thử
void test_loan();

#endif

