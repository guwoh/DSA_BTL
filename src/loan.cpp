#include <iostream>
#include <cstring>
#include <limits>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"
using namespace std;

// Kiểm tra người đọc có tồn tại
bool readerExists(const char* readerID, Reader* readerList) {
    for (Reader* r = readerList; r != NULL; r = r->next) {
        if (strcmp(r->id, readerID) == 0) return true;
    }
    return false;
}

// Kiểm tra sách có tồn tại
bool bookExists(const char* bookID, NodeTopic* topicList) {
    for (NodeTopic* t = topicList; t != NULL; t = t->next) {
        for (NodeBook* b = t->listBook; b != NULL; b = b->next) {
            if (strcmp(b->book.id, bookID) == 0) return true;
        }
    }
    return false;
}

// Tạo phiếu mượn mới
void createBorrowSlip(BorrowSlip** head, Reader* readerList, NodeTopic* topicList) {
    BorrowSlip* newSlip = new BorrowSlip;

    cout << "Nhap ID phieu muon: ";
    cin >> newSlip->slipID;

    cout << "Nhap ID nguoi doc: ";
    cin >> newSlip->readerID;
    if (!readerExists(newSlip->readerID, readerList)) {
        cout << "Nguoi doc voi ID \"" << newSlip->readerID << "\" khong ton tai.\n";
        delete newSlip;
        return;
    }

    cout << "Nhap ID sach: ";
    cin >> newSlip->bookID;
    if (!bookExists(newSlip->bookID, topicList)) {
        cout << "Sach voi ID \"" << newSlip->bookID << "\" khong ton tai.\n";
        delete newSlip;
        return;
    }

    cout << "Nhap ngay muon (dd/mm/yyyy): ";
    cin >> newSlip->borrowDate;

    cout << "Nhap ngay tra (dd/mm/yyyy): ";
    cin >> newSlip->dueDate;

    newSlip->returnDate[0] = '\0'; // chưa trả
    newSlip->next = *head;
    *head = newSlip;

    cout << "Tao phieu muon thanh cong.\n";
}

// Thêm phiếu mượn
void addBorrowSlip(BorrowSlip** head, Reader* readerList, NodeTopic* topicList) {
    createBorrowSlip(head, readerList, topicList);
}

// Trả sách (gán returnDate)
void returnBook(BorrowSlip* head) {
    char slipID[MAX_ID_LEN];
    cout << "Nhap ma phieu muon can tra: ";
    cin.getline(slipID, MAX_ID_LEN);

    BorrowSlip* current = head;
    while (current != nullptr) {
        if (strcmp(current->slipID, slipID) == 0) {
            if (strlen(current->returnDate) != 0) {
                cout << "Sach da duoc tra truoc do!" << endl;
                return;
            }

            cout << "Nhap ngay tra (dd/mm/yyyy): ";
            cin.getline(current->returnDate, MAX_DATE_LEN);
            cout << "Tra sach thanh cong!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Khong tim thay phieu muon voi ma da nhap!" << endl;
}

// Xóa phiếu mượn
void deleteBorrowSlip(BorrowSlip** head) {
    char slipID[MAX_ID_LEN];
    cout << "Nhap ma phieu muon can xoa: ";
    cin.getline(slipID, MAX_ID_LEN);

    BorrowSlip* current = *head;
    BorrowSlip* prev = nullptr;

    while (current != nullptr) {
        if (strcmp(current->slipID, slipID) == 0) {
            if (prev == nullptr) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Xoa phieu muon thanh cong!" << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Khong tim thay phieu muon voi ma da nhap!" << endl;
}

// Liệt kê phiếu mượn
void listBorrowSlips(BorrowSlip* head) {
    if (head == nullptr) {
        cout << "Khong co phieu muon nao!" << endl;
        return;
    }

    cout << "Danh sach phieu muon:" << endl;
    BorrowSlip* current = head;
    while (current != nullptr) {
        cout << "Phieu: " << current->slipID
             << ", Doc gia: " << current->readerID
             << ", Sach: " << current->bookID
             << ", Ngay muon: " << current->borrowDate
             << ", Han tra: " << current->dueDate
             << ", Ngay tra: " << (strlen(current->returnDate) > 0 ? current->returnDate : "Chua tra") << endl;
        current = current->next;
    }
}

// Tìm kiếm theo ID người mượn
void searchSlipByReader(BorrowSlip* head) {
    char readerID[MAX_ID_LEN];
    cout << "Nhap ID doc gia can tim: ";
    cin.getline(readerID, MAX_ID_LEN);

    bool found = false;
    BorrowSlip* current = head;
    while (current != nullptr) {
        if (strcmp(current->readerID, readerID) == 0) {
            cout << "Phieu: " << current->slipID
                 << ", Sach: " << current->bookID
                 << ", Ngay muon: " << current->borrowDate
                 << ", Han tra: " << current->dueDate
                 << ", Ngay tra: " << (strlen(current->returnDate) > 0 ? current->returnDate : "Chua tra") << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Khong co phieu muon nao cho doc gia nay!" << endl;
    }
}
// Liệt kê sách chưa trả
void listUnreturnedBooks(BorrowSlip* head) {
    if (head == nullptr) {
        cout << "Khong co phieu muon nao!" << endl;
        return;
    }

    cout << "Danh sach sach chua tra:" << endl;
    BorrowSlip* current = head;
    while (current != nullptr) {
        if (strlen(current->returnDate) == 0) {
            cout << "Phieu: " << current->slipID
                 << ", Doc gia: " << current->readerID
                 << ", Sach: " << current->bookID
                 << ", Ngay muon: " << current->borrowDate
                 << ", Han tra: " << current->dueDate << endl;
        }
        current = current->next;
    }
}
// Kiểm tra điều kiện mượn sách
void checkBorrowConditions(BorrowSlip* head) {
    if (head == nullptr) {
        cout << "Khong co phieu muon nao!" << endl;
        return;
    }

    BorrowSlip* current = head;
    while (current != nullptr) {
        if (strlen(current->returnDate) == 0) {
            cout << "Phieu: " << current->slipID
                 << ", Doc gia: " << current->readerID
                 << ", Sach: " << current->bookID
                 << ", Ngay muon: " << current->borrowDate
                 << ", Han tra: " << current->dueDate
                 << " - Chua tra sach!" << endl;
        }
        current = current->next;
    }
}
// Hàm kiểm thử
void test_loan() {
    BorrowSlip* head = nullptr;
    int choice;

    do {
        cout << "\n1. Them phieu muon";
        cout << "\n2. Tra sach";
        cout << "\n3. Xoa phieu muon";
        cout << "\n4. Liet ke phieu muon";
        cout << "\n5. Tim phieu theo ID doc gia";
        cout << "\n6. Liet ke sach chua tra";
        cout << "\n7. Kiem tra dieu kien muon sach";
        cout << "\n0. Thoat";
        cout << "\nChon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBorrowSlip(&head, nullptr, nullptr);    
                break;
            case 2:
                returnBook(head);
                break;
            case 3:
                deleteBorrowSlip(&head);
                break;
            case 4:
                listBorrowSlips(head);
                break;
            case 5:
                searchSlipByReader(head);
                break;
            case 6:
                checkBorrowConditions(head);
                break;
            case 0:
                cout << "Thoat!" << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    } while (choice != 0);

    // Giải phóng bộ nhớ
    while (head != nullptr) {
        BorrowSlip* temp = head;
        head = head->next;
        delete temp;
    }
}
/*int main() {
    test_loan();
    return 0;
}*/
