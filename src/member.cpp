#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"
using namespace std;

void test_member() {
    cout << "member.h is working" << endl;
}

// Tạo một độc giả mới
Reader* createReader() {
    Reader* newReader = new Reader;

    cout << "Nhap ID: ";
    cin.ignore();
    cin.getline(newReader->id, MAX_ID_LEN);

    cout << "Nhap ten: ";
    cin.getline(newReader->name, MAX_NAME_LEN);

    cout << "Nhap gioi tinh: ";
    cin.getline(newReader->gender, 10);

    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    cin.getline(newReader->dob, MAX_DATE_LEN);

    cout << "Nhap ngay cap the (dd/mm/yyyy): ";
    cin.getline(newReader->cardIssueDate, MAX_DATE_LEN);

    cout << "Nhap ngay het han (dd/mm/yyyy): ";
    cin.getline(newReader->cardExpiryDate, MAX_DATE_LEN);

    newReader->next = nullptr;

    return newReader;
}

// Thêm độc giả vào danh sách
void addReader(Reader** head) {
    Reader* newReader = createReader();

    if (*head == nullptr) {
        *head = newReader;
    } else {
        Reader* current = *head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newReader;
    }

    cout << "Them doc gia thanh cong!" << endl;
}

// Sửa thông tin độc giả
void editReader(Reader* head) {
    char id[MAX_ID_LEN];
    cout << "Nhap ID doc gia can sua: ";
    cin.ignore();
    cin.getline(id, MAX_ID_LEN);

    Reader* current = head;
    while (current != nullptr) {
        if (strcmp(current->id, id) == 0) {
            cout << "Nhap ten moi: ";
            cin.getline(current->name, MAX_NAME_LEN);

            cout << "Nhap gioi tinh moi: ";
            cin.getline(current->gender, 10);

            cout << "Nhap ngay sinh moi: ";
            cin.getline(current->dob, MAX_DATE_LEN);

            cout << "Nhap ngay cap the moi: ";
            cin.getline(current->cardIssueDate, MAX_DATE_LEN);

            cout << "Nhap ngay het han moi: ";
            cin.getline(current->cardExpiryDate, MAX_DATE_LEN);

            cout << "Sua thong tin thanh cong!" << endl;
            return;
        }
        current = current->next;
    }

    cout << "Khong tim thay doc gia voi ID da nhap!" << endl;
}

// Xóa độc giả
void deleteReader(Reader** head) {
    char id[MAX_ID_LEN];
    cout << "Nhap ID doc gia can xoa: ";
    cin.ignore();
    cin.getline(id, MAX_ID_LEN);

    Reader* current = *head;
    Reader* prev = nullptr;

    while (current != nullptr) {
        if (strcmp(current->id, id) == 0) {
            if (prev == nullptr) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "Xoa doc gia thanh cong!" << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Khong tim thay doc gia voi ID da nhap!" << endl;
}

// Tìm độc giả theo tên
void searchByName(Reader* head) {
    char name[MAX_NAME_LEN];
    cout << "Nhap ten doc gia can tim: ";
    cin.ignore();
    cin.getline(name, MAX_NAME_LEN);

    bool found = false;
    Reader* current = head;
    while (current != nullptr) {
        if (strcmp(current->name, name) == 0) {
            cout << "Tim thay: ID: " << current->id << ", Gioi tinh: " << current->gender
                 << ", DOB: " << current->dob << ", Ngay cap the: " << current->cardIssueDate
                 << ", Het han: " << current->cardExpiryDate << endl;
            found = true;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Khong tim thay doc gia voi ten da nhap!" << endl;
    }
}

// Tìm độc giả theo ID
void searchByID(Reader* head) {
    char id[MAX_ID_LEN];
    cout << "Nhap ID doc gia can tim: ";
    cin.ignore();
    cin.getline(id, MAX_ID_LEN);

    Reader* current = head;
    while (current != nullptr) {
        if (strcmp(current->id, id) == 0) {
            cout << "Tim thay: Ten: " << current->name << ", Gioi tinh: " << current->gender
                 << ", DOB: " << current->dob << ", Ngay cap the: " << current->cardIssueDate
                 << ", Het han: " << current->cardExpiryDate << endl;
            return;
        }
        current = current->next;
    }

    cout << "Khong tim thay doc gia voi ID da nhap!" << endl;
}

// In toàn bộ danh sách độc giả
void listReaders(Reader* head) {
    if (head == nullptr) {
        cout << "Danh sach doc gia rong!" << endl;
        return;
    }

    cout << "Danh sach doc gia:" << endl;
    Reader* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->id << ", Ten: " << current->name
             << ", Gioi tinh: " << current->gender << ", DOB: " << current->dob
             << ", Cap the: " << current->cardIssueDate
             << ", Het han: " << current->cardExpiryDate << endl;
        current = current->next;
    }
}
/*
// Hiển thị menu quản lý độc giả
void readerMenu(Reader** head) {
    int choice;
    do {
        cout << "\n--- Quan ly doc gia ---\n";
        cout << "1. Them doc gia\n";
        cout << "2. Sua thong tin doc gia\n";
        cout << "3. Xoa doc gia\n";
        cout << "4. Tim doc gia theo ten\n";
        cout << "5. Tim doc gia theo ID\n";
        cout << "6. Liet ke toan bo doc gia\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addReader(head);
                break;
            case 2:
                editReader(*head);
                break;
            case 3:
                deleteReader(head);
                break;
            case 4:
                searchByName(*head);
                break;
            case 5:
                searchByID(*head);
                break;
            case 6:
                listReaders(*head);
                break;
            case 0:
                cout << "Thoat khoi quan ly doc gia." << endl;
                break;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai." << endl;
        }
    } while (choice != 0);
}
*/
