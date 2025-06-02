#ifndef UTILS_H
#define UTILS_H
#include<stdio.h>

typedef struct {
    Reader* reader;
    int borrowCount;
} TopReader; // Top độc giả mượn sách

typedef struct {
    Book* book;
    int count;
} TopBook; // Top sách mượn nhiều nhất

void test_utlis();

// HÀM liên quan đến thống kê
// Top 3 sách được mượn nhiều nhất
int countBookBorrowed();
void updateTop3Books();
void findTop3Books();

// Top 3 độc giả mượn nhiều sách nhất
int countBorrowedBooks(); // Hàm đếm số sách mượn của độc giả
void updateTop3(); // Cập nhật top 3 độc giả mượn sách
void findTop3Readers(); // Tìm kiếm top 3 độc giả mượn sách nhiều nhất

// Tổng số sách đang mượn 
void hienThiBorrowedBooks(); 

#endif