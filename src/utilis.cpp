#include<stdio.h>
#include<string.h>

#include "book.h"
#include "loan.h"
#include "member.h"
#include "utils.h"

void test_utlis()
{
    printf("utlis.h is working");
}

// HÀM liên quan đến thống kê
// Hiển thị các loại thống kế
// void showStats();
// Sách được mượn nhiều nhất
/* 
Tổng quan ý tưởng:
Duyệt từng phần tử trong danh sách Book và với mỗi phần tử, duyệt toàn bộ danh sách BorrowSlip để đếm số lần mượn của sách đó.
*/ 
void mostBorrowedBook(Book* bookHead, BorrowSlip* borrowHead) {
    Book* maxBook = NULL; // con trở trỏ đến sách được mượn nhiều nhất
    int maxCount = 0; // biến đếm số lần mượn nhiều nhất

    // Duyệt từng sách trong danh sách
    for (Book* b = bookHead; b != NULL; b = b->next) {
        int count = 0;

        // Duyệt toàn bộ danh sách phiếu mượn để đếm số lần mượn của sách b
        for (BorrowSlip* slip = borrowHead; slip != NULL; slip = slip->next) {
            if (strcmp(b->id, slip->bookID) == 0) { // So sánh id trong Book và bookID trong BorrowSlip
                count++;
            }
        }

        // Nếu số lần mượn của sách này nhiều hơn max trước đó, cập nhật
        if (count > maxCount) {
            maxCount = count;
            maxBook = b;
        }
    }

    // Hiển thị 
    if (maxBook != NULL) {
        printf("Sach duoc muon nhieu nhat:\n");
        printf("ID: %s - Ten: %s - Tac gia: %s - So lan muon: %d\n",
               maxBook->id, maxBook->name, maxBook->author, maxCount);
    } else {
        printf("Khong co du lieu muon sach.\n");
    }
}

// Độc giả mượn nhiều sách nhất
//Reader* topReader();

// Tổng số sách đang mượn
/*
Nâng cấp:
Với struct BorrowSlip hiện tại, thì mỗi phiếu mượn chỉ mượn được 1 sách
Trường hợp mượn nhiều sách một lần thì có thể sử dụng struct lổng
Cx nên tính đến trường hợp mượn nhiều sách một lần, một sách nhiều quyển nhma trả rải rác 
Ví dụ:
typedef struct BorrowedBook {
    char bookID[20];
    int quantity;
    int quantityReturned;  // số lượng đã trả (0 nếu chưa trả)
    struct BorrowedBook* next;
} BorrowedBook;

typedef struct BorrowSlip {
    char slipID[20];
    char readerID[20];
    char borrowDate[11];
    char dueDate[11];
    int isReturned;             // 0 = còn sách chưa trả, 1 = trả hết
    BorrowedBook* borrowedBooks;
    struct BorrowSlip* next;
} BorrowSlip;
Khi này hàm đếm tổng số sách đang mượn sẽ là:
int countBorrowedBooks(BorrowSlip* borrowHead) {
    int total = 0;

    for (BorrowSlip* slip = borrowHead; slip != NULL; slip = slip->next) {
        if (slip->isReturned == 1) continue; // Nếu phiếu đã trả hết thì bỏ qua

        BorrowedBook* bbook = slip->borrowedBooks;
        while (bbook != NULL) {
            int notReturned = bbook->quantity - bbook->quantityReturned;
            if (notReturned > 0) {
                total += notReturned;
            }
            bbook = bbook->next;
        }
    }
    return total;
}
*/ 
int booksBorrowed(BorrowSlip* borrowHead) {
    int count = 0;
    for (BorrowSlip* p = borrowHead; p != NULL; p = p->next) {
        if (p->isReturned == 0) {  // Chưa trả
            count++;
        }
    }
    return count;
}

// MENU
void menu(); // Menu chính