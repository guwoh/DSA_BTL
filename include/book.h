#include<string.h>
/**
 * @brief lưu trữ thông tin liên quan đến sách
 * 
 */
void test_book();
typedef struct{
    char id;
    char name;
    char author;
    int year;
    int quantity;
    //Book* next;
}Book;

void addBook();
void editBook();
void deleteBook();
void searchByName();
void searchByID();
void searchByAuthor();
void searchByYear();
void sortBookByName();
//void