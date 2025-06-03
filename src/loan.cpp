#include <iostream>
#include <cstring>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
using namespace std;

void test_loan() {
    cout << "loan.h is working" << endl;
}

// Tạo phiếu mượn mới
BorrowSlip* createBorrowSlip() {
    BorrowSlip* newSlip = new BorrowSlip;

    cout << "Nhap ma phieu muon: ";
    cin.ignore();
    cin.getline(newSlip->slipID, MAX_ID_LEN);

    cout << "Nhap ID doc gia: ";
    cin.getline(newSlip->readerID, MAX_ID_LEN);

    cout << "Nhap ID sach: ";
    cin.getline(newSlip->bookID, MAX_ID_LEN);

    cout << "Nhap ngay muon (dd/mm/yyyy): ";
    cin.getline(newSlip->borrowDate, MAX_DATE_LEN);

    cout << "Nhap han tra (dd/mm/yyyy): ";
    cin.getline(newSlip->dueDate, MAX_DATE_LEN);

    newSlip->returnDate[0] = '\0'; // Chưa trả
    newSlip->next = nullptr;

    return newSlip;
}

// Thêm phiếu mượn
void addBorrowSlip(BorrowSlip** head) {
    BorrowSlip* newSlip = createBorrowSlip();

    if (*head == nullptr) {
        *head = newSlip;
    } else {
        BorrowSlip* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newSlip;
    }

    cout << "Them phieu muon thanh cong!" << endl;
}

// Trả sách (gán returnDate)
void returnBook(BorrowSlip* head) {
    char slipID[MAX_ID_LEN];
    cout << "Nhap ma phieu muon can tra: ";
    cin.ignore();
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
    cin.ignore();
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
    cin.ignore();
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
/*
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
                addBorrowSlip(&head);
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
                listUnreturnedBooks(head);
                break;
            case 7:
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
}*/
