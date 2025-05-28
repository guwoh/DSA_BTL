#ifndef BOOK_H
#define BOOK_H

typedef struct { 
    char id[20];//ma sach
    char name[100];//ten sach
    char author[30];//tac gia
    int year;//nam xuat ban
    int quantity;//so luong
}Book;

typedef struct NodeBook {
    Book book;
    struct NodeBook* next;
}NodeBook;

typedef struct NodeTopic{
    char nameTopic[100];
    struct NodeBook* listBook;
    struct NodeTopic* next;
}NodeTopic;


#endif


