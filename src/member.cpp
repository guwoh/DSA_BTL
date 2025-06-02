#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

Reader* createReader() {
    Reader* newReader = (Reader*)malloc(sizeof(Reader));
    if (!newReader) {
        cout << "Lỗi cấp phát bộ nhớ\n";
        return nullptr;
    }
    cout << "Nhập ID: "; cin.getline(newReader->id, MAX_ID_LEN);
    cout << "Nhập tên: "; cin.getline(newReader->name, MAX_NAME_LEN);
    cout << "Nhập giới tính: "; cin.getline(newReader->gender, 10);
    cout << "Nhập ngày sinh (dd/mm/yyyy): "; cin.getline(newReader->dob, MAX_DATE_LEN);
    cout << "Ngày cấp thẻ: "; cin.getline(newReader->cardIssueDate, MAX_DATE_LEN);
    cout << "Ngày hết hạn thẻ: "; cin.getline(newReader->cardExpiryDate, MAX_DATE_LEN);
    newReader->next = nullptr;
    return newReader;
}

void addReader(Reader** head) {
    Reader* newReader = createReader();
    if (!newReader) return;

    if (*head == nullptr) {
        *head = newReader;
    } else {
        Reader* temp = *head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newReader;
    }
    cout << "Đã thêm người đọc thành công.\n";
}

void listReaders(Reader* head) {
    Reader* current = head;
    cout << "Danh sách người đọc:\n";
    while (current != nullptr) {
        cout << "ID: " << current->id << " | Tên: " << current->name
             << " | Giới tính: " << current->gender << " | Ngày sinh: " << current->dob
             << " | Cấp: " << current->cardIssueDate << " | Hết hạn: " << current->cardExpiryDate << "\n";
        current = current->next;
    }
}

void editReader(Reader* head) {
    char targetID[MAX_ID_LEN];
    cout << "Nhập ID người đọc cần sửa: ";
    cin.getline(targetID, MAX_ID_LEN);

    Reader* current = head;
    while (current != nullptr) {
        if (strcmp(current->id, targetID) == 0) {
            cout << "==> Tìm thấy người đọc. Nhập thông tin mới:\n";
            cout << "Tên: "; cin.getline(current->name, MAX_NAME_LEN);
            cout << "Giới tính: "; cin.getline(current->gender, 10);
            cout << "Ngày sinh: "; cin.getline(current->dob, MAX_DATE_LEN);
            cout << "Ngày cấp thẻ: "; cin.getline(current->cardIssueDate, MAX_DATE_LEN);
            cout << "Ngày hết hạn thẻ: "; cin.getline(current->cardExpiryDate, MAX_DATE_LEN);
            cout << "Đã cập nhật thông tin.\n";
            return;
        }
        current = current->next;
    }
    cout << "Không tìm thấy người đọc.\n";
}

void deleteReader(Reader** head) {
    char targetID[MAX_ID_LEN];
    cout << "Nhập ID người đọc cần xoá: ";
    cin.getline(targetID, MAX_ID_LEN);

    Reader *current = *head, *prev = nullptr;
    while (current != nullptr && strcmp(current->id, targetID) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        cout << "Không tìm thấy người đọc.\n";
        return;
    }
    if (prev == nullptr) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    cout << "Đã xoá người đọc.\n";
}

void searchByID(Reader* head) {
    char targetID[MAX_ID_LEN];
    cout << "Nhập ID cần tìm: ";
    cin.getline(targetID, MAX_ID_LEN);

    Reader* current = head;
    while (current != nullptr) {
        if (strcmp(current->id, targetID) == 0) {
            cout << "Tìm thấy:\n";
            cout << "ID: " << current->id << " | Tên: " << current->name
                 << " | Giới tính: " << current->gender << " | Ngày sinh: " << current->dob
                 << " | Cấp: " << current->cardIssueDate << " | Hết hạn: " << current->cardExpiryDate << "\n";
            return;
        }
        current = current->next;
    }
    cout << "Không tìm thấy người đọc.\n";
}

void searchByName(Reader* head) {
    char targetName[MAX_NAME_LEN];
    cout << "Nhập tên hoặc từ khoá tên cần tìm: ";
    cin.getline(targetName, MAX_NAME_LEN);

    Reader* current = head;
    int found = 0;
    while (current != nullptr) {
        if (strstr(current->name, targetName) != nullptr) {
            cout << "ID: " << current->id << " | Tên: " << current->name
                 << " | Giới tính: " << current->gender << " | Ngày sinh: " << current->dob
                 << " | Cấp: " << current->cardIssueDate << " | Hết hạn: " << current->cardExpiryDate << "\n";
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        cout << "Không tìm thấy người đọc.\n";
}
/*
void test_member() {
    Reader* head = nullptr;
    int choice;

    do {
        cout << "\n1. Thêm người đọc\n";
        cout << "2. Sửa thông tin người đọc\n";
        cout << "3. Xoá người đọc\n";
        cout << "4. Tìm kiếm theo ID\n";
        cout << "5. Tìm kiếm theo tên\n";
        cout << "6. Liệt kê tất cả người đọc\n";
        cout << "0. Thoát\n";
        cout << "Chọn: ";
        cin >> choice;
        cin.ignore(); // Để bỏ qua ký tự newline

        switch (choice) {
            case 1: addReader(&head); break;
            case 2: editReader(head); break;
            case 3: deleteReader(&head); break;
            case 4: searchByID(head); break;
            case 5: searchByName(head); break;
            case 6: listReaders(head); break;
            case 0: cout << "Thoát chương trình.\n"; break;
            default: cout << "Lựa chọn không hợp lệ.\n"; break;
        }
    } while (choice != 0);

    // Giải phóng bộ nhớ
    while (head) {
        Reader* temp = head;
        head = head->next;
        free(temp);
    }
}
int main() {
    test_member();
    return 0;
}*/
