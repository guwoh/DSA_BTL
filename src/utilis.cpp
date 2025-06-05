#include<stdio.h>
#include<string.h>

#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"

void test_utlis()
{
    printf("utlis.h is working");
}

// HÀM liên quan đến thống kê
// Sách được mượn nhiều nhất
/* 
Tổng quan ý tưởng:
Duyệt từng phần tử trong danh sách Book và với mỗi phần tử, duyệt toàn bộ danh sách BorrowSlip để đếm số lần mượn của sách đó.
*/ 
int countBookBorrowed(BorrowSlip* slipList, const char* bookID) {
    int count = 0;
    if (slipList == NULL || bookID == NULL) 
        return 0;
    while (slipList != NULL) {
        if (strcmp(slipList->bookID, bookID) == 0) {
            count++;
        }
        slipList = slipList->next;
    }
    return count;
} // Đếm số lần sách được mượn

void updateTop3Books(TopBook top3[], Book* book, int count) {
    if (count == 0) return; // Bỏ qua nếu count bằng 0
    for (int i = 0; i < 3; i++) {
        if (top3[i].book == NULL || count > top3[i].count) {
            for (int j = 2; j > i; j--) {
                top3[j] = top3[j - 1];
            }
            top3[i].book = book;
            top3[i].count = count;
            break;
        }
    }
}

void findTop3Books(NodeTopic* topicList, BorrowSlip* slipList) {
    if (topicList == NULL) {
        printf("Danh sach chu de rong.\n");
        return;
    }
    TopBook top3[3] = {{NULL, 0}, {NULL, 0}, {NULL, 0}};

    for (NodeTopic* topic = topicList; topic != NULL; topic = topic->next) {
        if (topic->listBook == NULL) continue; // Bỏ qua nếu không có sách
        for (NodeBook* bookNode = topic->listBook; bookNode != NULL; bookNode = bookNode->next) {
            int count = countBookBorrowed(slipList, bookNode->book.id);
            updateTop3Books(top3, &bookNode->book, count);
        }
    }

    printf("Top 3 sach duoc muon nhieu nhat:\n");
    int printed = 0;
    for (int i = 0; i < 3; i++) {
        if (top3[i].book != NULL && top3[i].count > 0) {
            printf("%d. %s (ID: %s) - %d lan\n", i + 1,
                   top3[i].book->name,
                   top3[i].book->id,
                   top3[i].count);
            printed++;
        }
    }

    if (printed == 0) {
        printf("Khong co sach nao duoc muon.\n");
    }
}

// Độc giả mượn nhiều sách nhất
/* 
Ý tưởng: Duyệt từng độc giả trong danh sách Reader
Với mỗi độc giả, duyệt toàn bộ danh sách BorrowSlip:
So sánh slip.readerID với reader.id
Cộng dồn số lượng sách từ slip.borrowedBooks
*/
int countBorrowedBooks(BorrowSlip* slipList, const char* readerID) {
    int count = 0;
    if (slipList == NULL || readerID == NULL) 
        return 0;
    while (slipList != NULL) {
        if (strcmp(slipList->readerID, readerID) == 0) {
            count++; // mỗi phiếu là 1 lần mượn 1 cuốn
        }
        slipList = slipList->next;
    }
    return count;
} // Đếm số sách mượn của độc giả

// Tìm kiếm top 3 độc giả mượn sách nhiều nhất
void updateTop3(TopReader top3[], Reader* reader, int count) {
    if (count == 0) return; // Bỏ qua nếu không mượn gì

    for (int i = 0; i < 3; i++) {
        if (top3[i].reader == NULL || count > top3[i].borrowCount) {
            // Dời các phần tử từ dưới lên
            for (int j = 2; j > i; j--) {
                top3[j] = top3[j - 1];
            }

            // Gán người đọc vào vị trí i
            top3[i].reader = reader;
            top3[i].borrowCount = count;
            break;
        }
    }
}

void findTop3Readers(Reader* readerList, BorrowSlip* slipList) {
    if (readerList == NULL) {
        printf("Danh sach doc gia rong.\n");
        return;
    }
    TopReader top3[3] = {{NULL, 0}, {NULL, 0}, {NULL, 0}};

    for (Reader* current = readerList; current != NULL; current = current->next) {
        int count = countBorrowedBooks(slipList, current->id);
        updateTop3(top3, current, count);
    }

    printf("Top 3 doc gia muon sach nhieu nhat:\n");
    int printed = 0;

    for (int i = 0; i < 3; i++) {
        if (top3[i].reader != NULL && top3[i].borrowCount > 0) {
            printf("%d. %s (ID: %s) - %d cuon sach\n",
                   i + 1,
                   top3[i].reader->name,
                   top3[i].reader->id,
                   top3[i].borrowCount);
            printed++;
        }
    }

    if (printed == 0) {
        printf("Khong tim thay doc gia nao.\n");
    }
}

// Tổng số sách đang mượn
void hienThiBorrowedBooks(BorrowSlip* head) {
    int count = 0;
    BorrowSlip* current = head;
    if (head == NULL) {
        printf("Khong co sach nao dang duoc muon.\n");
        return;
    }

    while (current != NULL) {
        if (strlen(current->returnDate) == 0) {  // Kiểm tra sách chưa trả
            count++;
            printf("ID doc gia: %s\n", current->readerID);
            printf("  - ID sach: %s\n", current->bookID);
            printf("  - Ngay muon: %s\n", current->borrowDate);
            printf("  - Han tra: %s\n\n", current->dueDate);
        }
        current = current->next;
    }

    printf("Tong so sach dang duoc muon: %d\n", count);
}


