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
Book mostBorrowedBook(NodeTopic* topicHead, BorrowSlip* slipHead) {
    Book mostBorrowed;
    int maxCount = 0;
    memset(&mostBorrowed, 0, sizeof(Book)); // reset rác

    for (NodeTopic* topic = topicHead; topic != NULL; topic = topic->next) {
        for (NodeBook* bookNode = topic->listBook; bookNode != NULL; bookNode = bookNode->next) {
            int count = 0;

            // Duyệt toàn bộ danh sách phiếu mượn
            for (BorrowSlip* slip = slipHead; slip != NULL; slip = slip->next) {
                for (BorrowedBook* borrowed = slip->borrowedBooks; borrowed != NULL; borrowed = borrowed->next) {
                    if (strcmp(borrowed->bookID, bookNode->book.id) == 0) {
                        count += borrowed->quantity; // cộng tổng số sách đã mượn
                    }
                }
            }

            if (count > maxCount) {
                maxCount = count;
                mostBorrowed = bookNode->book;
            }
        }
    }

    return mostBorrowed;
}

// Độc giả mượn nhiều sách nhất
/* Ý tưởng: Duyệt từng độc giả trong danh sách Reader
   Với mỗi độc giả, duyệt toàn bộ danh sách BorrowSlip:
   So sánh slip.readerID với reader.id
   Cộng dồn số lượng sách từ slip.borrowedBooks
*/
Reader mostActiveReader(Reader* readerHead, BorrowSlip* slipHead) {
    Reader result;
    memset(&result, 0, sizeof(Reader));
    int maxCount = 0;

    for (Reader* r = readerHead; r != NULL; r = r->next) {
        int count = 0;

        for (BorrowSlip* s = slipHead; s != NULL; s = s->next) {
            if (strcmp(r->id, s->readerID) == 0) {
                for (BorrowedBook* bb = s->borrowedBooks; bb != NULL; bb = bb->next) {
                    count += bb->quantity;
                }
            }
        }

        if (count > maxCount) {
            maxCount = count;
            result = *r;  // sao chép dữ liệu reader
        }
    }

    return result;
}

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

// Xây dựng hàm đọc dữ liệu từ file - có vẻ dùng chung được
// Hàm đọc danh sách phiếu mượn
BorrowSlip* loadBorrowSlipsFromFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    BorrowSlip* head = NULL;
    BorrowSlip* tail = NULL;

    int n;
    fscanf(f, "%d\n", &n); // số phiếu mượn
    for (int i = 0; i < n; ++i) {
        BorrowSlip* slip = (BorrowSlip*)malloc(sizeof(BorrowSlip));
        slip->borrowedBooks = NULL;
        slip->next = NULL;

        fscanf(f, "%s %s %s %s %d\n", slip->slipID, slip->readerID, slip->borrowDate, slip->dueDate, &slip->isReturned);

        int m;
        fscanf(f, "%d\n", &m); // số sách trong phiếu

        BorrowedBook* bTail = NULL;
        for (int j = 0; j < m; ++j) {
            BorrowedBook* bb = (BorrowedBook*)malloc(sizeof(BorrowedBook));
            bb->next = NULL;
            fscanf(f, "%s %d %d\n", bb->bookID, &bb->quantity, &bb->quantityReturned);

            if (!slip->borrowedBooks)
                slip->borrowedBooks = bTail = bb;
            else {
                bTail->next = bb;
                bTail = bb;
            }
        }

        if (!head) head = tail = slip;
        else {
            tail->next = slip;
            tail = slip;
        }
    }

    fclose(f);
    return head;
}

// MENU
void menu(); // Menu chính