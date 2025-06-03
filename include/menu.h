#ifndef MENU_H
#define MENU_H
#include<stdio.h>
#include "book.h"
#include "loan.h"
#include "member.h"
#include "utils.h"
#include "io.h"

// MENU chính
void hienThiMenuChinh();

// Phần Book
void menuBook();
void choiceBook(NodeTopic* tp);

// Phần Member
void menuMember();
void choiceMember(Reader** head);

// Phần Loan
void menuLoan();
void choiceLoan(BorrowSlip** borrowList);

// Phần thống kê
void menuThongKe(); // Menu thống kê
void choiceThongKe(NodeTopic* topicList, BorrowSlip* slipList, Reader* readerList);
#endif