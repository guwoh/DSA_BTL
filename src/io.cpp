#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/io.h"


// thêm sách vào đầu danh sách
void addBookAtHead(bookNode** head, book books) // 
{
    bookNode* newNode = (bookNode*)malloc(sizeof(bookNode));
    newNode->data = books;
    newNode->next = *head;
    *head = newNode;
}

// thêm sách vào cuối danh sách 
void addBookAtTail();

// in danh sách
void printBook();

// xóa sách theo tiêu đề 
void deleteBookByTitle();



/*ra file*/
// ra file text
void writeText();

// ra file bin
void writeBin();


/*vao file*/
// vao file bin
void readBin();

// hiu is here
// hhhhh
