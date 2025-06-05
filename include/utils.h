#ifndef UTILS_H
#define UTILS_H
#include<stdio.h>
#include "member.h" // struct reader        
#include "book.h" // struct book    
#include "loan.h" // struct borrow slip

typedef struct {
    Reader* reader;
    int borrowCount;
} TopReader; // Top độc giả mượn sách

typedef struct {
    Book* book;
    int count;
} TopBook; // Top sách mượn nhiều nhất



// HÀM liên quan đến thống kê
// Top 3 sách được mượn nhiều nhất
int countBookBorrowed(BorrowSlip* slipList, const char* bookID);
void updateTop3Books(TopBook top3[], Book* book, int count);
void findTop3Books(NodeTopic* topicList, BorrowSlip* slipList);

// Top 3 độc giả mượn nhiều sách nhất
int countBorrowedBooks(BorrowSlip* slipList, const char* readerID); // Hàm đếm số sách mượn của độc giả
void updateTop3(TopReader top3[], Reader* reader, int count); // Cập nhật top 3 độc giả mượn sách
void findTop3Readers(Reader* readerList, BorrowSlip* slipList); // Tìm kiếm top 3 độc giả mượn sách nhiều nhất

// Tổng số sách đang mượn 
void hienThiBorrowedBooks(BorrowSlip* head); 

#endif