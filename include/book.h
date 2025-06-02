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


void initTopic(NodeTopic** nb); //Khoi tao 
NodeBook* creNodeBook(char Id[], char Name[], char Author[], int Year, int Quantity); //Tao NodeBook
void addBook(NodeBook** listBook, Book book); //Them sach vao danh sach sach
void addTopic(NodeTopic** listTopic, const char NameTopic[], Book book[], int c); //Them chu de
void addNew(NodeTopic** listTopic);  //Nhap cac thong tin de ve chu de va sach de tien hanh them vao

NodeTopic* searchTopic(NodeTopic* listTopic, const char s[]); //Tim kiem chu de
void editBook(NodeTopic** listTopic); // sua thong tin cua sach
void deleteBookOrTopic(NodeTopic** listTopic);//xoa chu de hoac xoa sach bat ky
NodeBook* searchByID1(NodeTopic** listTopic); 
void display(NodeBook* listBook); //Hien thi danh sach sach cua 1 chu de
void display2(NodeTopic* listTP); //Hien thi tat ca thu vien
void display3(NodeBook* listBook); //Hien thi 1 sach cu the
#endif


