/*
định nghĩa các hàm 
*/
#include<stdio.h>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"

void test_utlis();

// HÀM liên quan đến thống kê
// Hiển thị các loại thống kế
void showStats();
// Sách được mượn nhiều nhất
//Book* mostBorrowedBook(); 
// Độc giả mượn nhiều sách nhất
//Reader* topReader(); 
// Tổng số sách đang mượn 
int booksBorrowed(); 

// MENU
void menu(); // Menu chính