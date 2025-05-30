#ifndef BOOK_H
#define BOOK_H

// hold information about a single book
typedef struct { 
    char id[20];//ma sach
    char name[100];//ten sach
    char author[30];//tac gia
    int year;//nam xuat ban
    int quantity;//so luong
}Book;


// this define a node in a linked list of books
// -book: the actual book data
// -next: pointer to the next book node
// -so, multiple NodeBook can be connexted like a chain ( linked list)
typedef struct NodeBook {
    Book book;
    struct NodeBook* next;
}NodeBook;

// this defiles a linked list od topics
// - has a nameTopic
// - points to a linked list of books ( listBook)
// - points to the next topic ( next )
typedef struct NodeTopic{
    char nameTopic[100];
    struct NodeBook* listBook;
    struct NodeTopic* next;
}NodeTopic;


#endif


