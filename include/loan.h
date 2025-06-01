#ifndef LOAN_H
#define LOAN_H

#include "book.h"
#include "member.h"

#define MAX_BORROWED_BOOKS 5
#define DATE_LEN 11

typedef struct BorrowSlip {
    char readerID[MAX_ID_LEN];        // ID người mượn
    char bookID[20];                  // ID sách mượn
    char borrowDate[DATE_LEN];       // Ngày mượn
    char returnDate[DATE_LEN];       // Ngày trả (nếu có)
    int isReturned;                  // Trạng thái trả sách: 0 = chưa, 1 = đã trả
    struct BorrowSlip* next;
} BorrowSlip;

// Quản lý phiếu mượn
void createBorrowSlip(BorrowSlip** head, Reader* readerList, NodeTopic* topicList);
void returnBook(BorrowSlip* head);
void listBorrowSlips(BorrowSlip* head);
void listUnreturnedBooks(BorrowSlip* head);
void checkBorrowConditions(BorrowSlip* head, Reader* readerList);

// Hàm kiểm thử
void test_loan();

#endif
