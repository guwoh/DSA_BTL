#ifndef UTLIS_H
#define UTLIS_H
#include<stdio.h>
#include "book.h"
#include "loan.h"
#include "member.h"

void test_utlis();

// HÀM liên quan đến thống kê
// Hiển thị các loại thống kế
void showStats();
// Sách được mượn nhiều nhất
void mostBorrowedBook(); 
// Độc giả mượn nhiều sách nhất
//Reader* topReader(); 
// Tổng số sách đang mượn 
int booksBorrowed(); 

// MENU
void menu(); // Menu chính



#endif