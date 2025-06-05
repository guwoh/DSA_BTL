#include <string.h>
#include <stdbool.h>
#include "member.h"
#include "book.h"
#ifndef BORROW_H
#define BORROW_H

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
void createBorrowSlip(BorrowSlip** head, Reader* readerList, NodeTopic* topicList);
void addBorrowSlip(BorrowSlip** head, Reader* readerList, NodeTopic* topicList);
void deleteBorrowSlip(BorrowSlip** head);
void returnBook(BorrowSlip* head);
void listBorrowSlips(BorrowSlip* head);
void listUnreturnedBooks(BorrowSlip* head);
void checkBorrowConditions(BorrowSlip* head);
bool readerExists(const char* readerID, Reader* readerList);
bool bookExists(const char* bookID, NodeTopic* topicList);
void searchSlipByReader(BorrowSlip* head);


#endif

