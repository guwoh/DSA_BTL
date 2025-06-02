#ifndef BORROW_H
#define BORROW_H

#include "book.h"
#include "member.h"

#define MAX_BORROWED_BOOKS 5
#define DATE_LEN 11

struct BorrowedBook {
    char bookId[20];                  // ID sách mượn
    int quantity;                     // số lượng sách mượn
};

typedef struct BorrowSlip {
    char readerID[MAX_ID_LEN];        // ID người mượn            
    BorrowedBook books[MAX_BORROWED_BOOKS];           
    char borrowDate[DATE_LEN];       // Ngày mượn
    char returnDate[DATE_LEN];       // Ngày trả (nếu có)
    int numBorrowed;
    bool isReturned[MAX_BORROWED_BOOKS];             // Trạng thái trả sách: 0 = chưa, 1 = đã trả
    struct BorrowSlip* next;
} BorrowSlip;

// Quản lý phiếu mượn
void createBorrowSlip(BorrowSlip** head, Reader* readerList, NodeTopic* topicList);
void returnBook(BorrowSlip* head);
void listBorrowSlips(BorrowSlip* head);
void listUnreturnedBooks(BorrowSlip* head, const char* readerId);
void checkBorrowStatus(BorrowSlip* head, const char* readerId, int* result);

// Hàm kiểm thử
void test_loan();

#endif
