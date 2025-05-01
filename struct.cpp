#include<iostream>
using namespace std;

struct Book {
    string id;
    string name;
    string author;
    int year;
    int quantity;
    Book* next;
};

void addBook();
void editBook();
void deleteBook();
void searchByName();
void searchByID();
void searchByAuthor();
void searchByYear();
void sortBookByName();
void sortBookByYear();
