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
    while (slipList != NULL) {
        if (strcmp(slipList->bookID, bookID) == 0) {
            count++;
        }
        slipList = slipList->next;
    }
    return count;
} // Đếm số lần sách được mượn

void updateTop3Books(TopBook top3[], Book* book, int count) {
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
    TopBook top3[3] = {{NULL, 0}, {NULL, 0}, {NULL, 0}};

    for (NodeTopic* topic = topicList; topic != NULL; topic = topic->next) {
        for (NodeBook* bookNode = topic->listBook; bookNode != NULL; bookNode = bookNode->next) {
            int count = countBookBorrowed(slipList, bookNode->book.id);
            updateTop3Books(top3, &bookNode->book, count);
        }
    }

    printf("Top sách được mượn nhiều nhất:\n");
    int printed = 0;
    for (int i = 0; i < 3; i++) {
        if (top3[i].book != NULL) {
            printf("%d. %s (ID: %s) - %d lượt mượn\n", i + 1,
                   top3[i].book->name,
                   top3[i].book->id,
                   top3[i].count);
            printed++;
        }
    }

    if (printed == 0) {
        printf("Không có sách nào được mượn.\n");
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
    while (slipList != NULL) {
        if (strcmp(slipList->readerID, readerID) == 0) {
            count++;
        }
        slipList = slipList->next;
    }
    return count;
} // Đếm số sách đã mượn của độc giả

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
    TopReader top3[3] = {{NULL, 0}, {NULL, 0}, {NULL, 0}};

    // Duyệt danh sách độc giả bằng vòng for
    for (Reader* current = readerList; current != NULL; current = current->next) {
        int count = countBorrowedBooks(slipList, current->id);
        updateTop3(top3, current, count);
    }

    printf("Top độc giả mượn nhiều sách nhất:\n");

    int num = 0;
    for (int i = 0; i < 3; i++) {
        if (top3[i].reader != NULL) {
            printf("%d. %s (ID: %s) - %d sách\n", i + 1,
                   top3[i].reader->name,
                   top3[i].reader->id,
                   top3[i].borrowCount);
            num++;
        }
    }

    if (num == 0) {
        printf("Không có độc giả nào mượn sách.\n");
    }
}

// Tổng số sách đang mượn
void hienThiBorrowedBooks(BorrowSlip* head) {
    int count = 0;
    BorrowSlip* current = head;

    while (current != NULL) {
        if (strlen(current->returnDate) == 0) {
            count++;
            printf("Phiếu mượn ID: %s, Mã sách: %s, Mã độc giả: %s, Ngày mượn: %s, Hạn trả: %s\n",
                current->slipID,
                current->bookID,
                current->readerID,
                current->borrowDate,
                current->dueDate);
        }
        current = current->next;
    }

    printf("Tổng số sách đang được mượn chưa trả: %d\n", count);
}
