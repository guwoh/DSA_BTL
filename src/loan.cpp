#include <iostream>
#include <cstring>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
using namespace std;

void createBorrowSlip(BorrowSlip*& head, Reader* readerList, NodeTopic* topicList) {
    BorrowSlip* newSlip = new BorrowSlip;
    cout << "Nhập ID người đọc: ";
    cin >> newSlip->readerID;

    // Kiểm tra người đọc tồn tại
    Reader* reader = readerList;
    while (reader && strcmp(reader->id, newSlip->readerID) != 0)
        reader = reader->next;
    if (!reader) {
        cout << "Không tìm thấy người đọc.\n";
        delete newSlip;
        return;
    }

    cout << "Nhập ngày mượn sách (dd/mm/yyyy): ";
    cin >> newSlip->borrowDate;
    strcpy(newSlip->returnDate, ""); // mặc định chưa trả

    cout << "Nhập số lượng sách mượn (<= " << MAX_BORROWED_BOOKS << "): ";
    cin >> newSlip->numBorrowed;

    if (newSlip->numBorrowed > MAX_BORROWED_BOOKS || newSlip->numBorrowed <= 0) {
        cout << "Số lượng sách không hợp lệ.\n";
        delete newSlip;
        return;
    }

    for (int i = 0; i < newSlip->numBorrowed; i++) {
        cout << "Nhập ID sách: ";
        cin >> newSlip->books[i].bookId;
        cout << "Nhập số lượng sách: ";
        cin >> newSlip->books[i].quantity;
        newSlip->isReturned[i] = false;

        // Trừ số lượng sách (nếu có đủ)
        NodeTopic* topic = topicList;
        bool found = false;
        while (topic && !found) {
            NodeBook* b = topic->listBook;
            while (b) {
                if (strcmp(b->book.id, newSlip->books[i].bookId) == 0) {
                    if (b->book.quantity >= newSlip->books[i].quantity) {
                        b->book.quantity -= newSlip->books[i].quantity;
                        found = true;
                    } else {
                        cout << "Not enough quantity for book ID: " << b->book.id << "\n";
                        delete newSlip;
                        return;
                    }
                }
                b = b->next;
            }
            topic = topic->next;
        }
        if (!found) {
            cout << "Không tìm thấy sách.\n";
            delete newSlip;
            return;
        }
    }

    newSlip->next = head;
    head = newSlip;
    cout << "Tạo phiếu mượn thành công!\n";
}

void returnBook(BorrowSlip* head) {
    char readerId[MAX_ID_LEN], bookId[20];
    cout << "Nhập ID người đọc: ";
    cin >> readerId;
    cout << "Nhập ID sách cần trả: ";
    cin >> bookId;

    BorrowSlip* slip = head;
    while (slip) {
        if (strcmp(slip->readerID, readerId) == 0) {
            for (int i = 0; i < slip->numBorrowed; i++) {
                if (strcmp(slip->books[i].bookId, bookId) == 0 && !slip->isReturned[i]) {
                    slip->isReturned[i] = true;

                    // Nhập ngày trả
                    cout << "Nhập ngày trả sách (dd/mm/yyyy): ";
                    cin >> slip->returnDate;

                    cout << "Sách đã trả.\n";
                    return;
                }
            }
        }
        slip = slip->next;
    }
    cout << "Borrow record not found or already returned.\n";
}

void listBorrowSlips(BorrowSlip* head) {
    BorrowSlip* slip = head;
    while (slip) {
        cout << "ID người đọc: " << slip->readerID << "\n";
        cout << "Ngày mượn sách: " << slip->borrowDate << "\n";
        cout << "Ngày trả sách: " << (strlen(slip->returnDate) > 0 ? slip->returnDate : "Chưa trả sách") << "\n";

        for (int i = 0; i < slip->numBorrowed; i++) {
            cout << "- ID sách: " << slip->books[i].bookId
                 << ", Số lượng: " << slip->books[i].quantity
                 << ", Đã trả: " << (slip->isReturned[i] ? "Có" : "Không") << "\n";
        }
        cout << "--------------------------\n";
        slip = slip->next;
    }
}

void listUnreturnedBooks(BorrowSlip* head, const char* readerId) {
    BorrowSlip* slip = head;
    while (slip) {
        if (strcmp(slip->readerID, readerId) == 0) {
            for (int i = 0; i < slip->numBorrowed; i++) {
                if (!slip->isReturned[i]) {
                    cout << "ID sách: " << slip->books[i].bookId
                         << ", Số lượng: " << slip->books[i].quantity
                         << ", Ngày mượn sách: " << slip->borrowDate << "\n";
                }
            }
        }
        slip = slip->next;
    }
}

void checkBorrowStatus(BorrowSlip* head, const char* readerId, int* result) {
    int totalUnreturned = 0;
    BorrowSlip* slip = head;

    while (slip) {
        if (strcmp(slip->readerID, readerId) == 0) {
            for (int i = 0; i < slip->numBorrowed; i++) {
                if (!slip->isReturned[i]) {
                    totalUnreturned += slip->books[i].quantity;
                }
            }
        }
        slip = slip->next;
    }

    if (totalUnreturned >= MAX_BORROWED_BOOKS) {
        cout << "Mượn quá số lượng quy định. Không thể mượn thêm.\n";
        *result = 0; // Không đủ điều kiện
    } else {
        *result = 1; // Đủ điều kiện
    }
}
/*void test_loan() {
    // Test functions here
    BorrowSlip* borrowList = nullptr;
    Reader* readerList = nullptr; // Giả sử đã có danh sách người đọc
    NodeTopic* topicList = nullptr; // Giả sử đã có danh sách chủ đề sách

    // Tạo phiếu mượn
    createBorrowSlip(borrowList, readerList, topicList);

    // Liệt kê phiếu mượn
    listBorrowSlips(borrowList);

    // Trả sách
    returnBook(borrowList);

    // Liệt kê sách chưa trả của một người đọc
    char readerId[MAX_ID_LEN];
    cout << "Enter reader ID to list unreturned books: ";
    cin >> readerId;
    listUnreturnedBooks(borrowList, readerId);

    // Kiểm tra tình trạng mượn sách
    int result;
    checkBorrowStatus(borrowList, readerId, &result);
}
int main() {
    // Gọi hàm kiểm thử
    test_loan();
    return 0;
}*/
