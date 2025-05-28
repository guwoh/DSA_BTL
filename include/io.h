#ifndef IO_H
#define IO_H

// xuat nhap du lieu

/*khai bao mock struct*/
// làm việc với linkedList
typedef struct // struct book
{
    int id; // ma so sach
    char name[30]; // ten sach
    int year; // nam suat ban

}book;

typedef struct bookNode // struct node
{
    Book data;
    struct bookNode *next;
}bookNode;

// thêm sách vào đầu danh sách
void addBookAtHead();

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






#endif