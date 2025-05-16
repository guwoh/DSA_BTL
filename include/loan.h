/**
 * @brief  lưu trữ thông tin đến sách được mượn và người mượn sách 

 */
#include<string.h>
void test_loan();

typedef struct{
    char slipID;
    char bookID;
    char readerID;
    char borrowDate;
    char dueDate;
    char returnDate;
    //bool isReturned;
    BorrowSlip* next;
}BorrowSlip;

void createBorrowSlip();
void returnBook();
void listBorrowSlips();
void listUnreturnedBooks();
void checkBorrowConditions();