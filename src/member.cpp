#include <stdio.h>
#include <stdlib.h>
#include "member.h"

Reader* createReader() {
    Reader* newReader = (Reader*)malloc(sizeof(Reader));
    if (!newReader) {
        printf("Lỗi cấp phát bộ nhớ\n");
        return NULL;
    }
    printf("Nhập ID: "); scanf(" %[^\n]", newReader->id);
    printf("Nhập tên: "); scanf(" %[^\n]", newReader->name);
    printf("Nhập giới tính: "); scanf(" %[^\n]", newReader->gender);
    printf("Nhập ngày sinh (dd/mm/yyyy): "); scanf(" %[^\n]", newReader->dob);
    printf("Ngày cấp thẻ: "); scanf(" %[^\n]", newReader->cardIssueDate);
    printf("Ngày hết hạn thẻ: "); scanf(" %[^\n]", newReader->cardExpiryDate);
    newReader->next = NULL;

    return newReader;
}


void addReader(Reader** head) {
    Reader* newReader = createReader();
    if (!newReader) return;

    if (*head == NULL) {
        *head = newReader;
    } else {
        Reader* temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newReader;
    }
    printf("Đã thêm người đọc thành công.\n");
}

void listReaders(Reader* head) {
    Reader* current = head;
    printf("Danh sách người đọc:\n");
    while (current != NULL) {
        printf("ID: %s | Tên: %s | Giới tính: %s | Ngày sinh: %s | Cấp: %s | Hết hạn: %s\n",
               current->id, current->name, current->gender,
               current->dob, current->cardIssueDate, current->cardExpiryDate);
        current = current->next;
    }
}

void editReader(Reader* head) {
    char targetID[MAX_ID_LEN];
    printf("Nhập ID người đọc cần sửa: ");
    scanf(" %[^\n]", targetID);

    Reader* current = head;
    while (current != NULL) {
        if (strcmp(current->id, targetID) == 0) {
            printf("==> Tìm thấy người đọc. Nhập thông tin mới:\n");
            printf("Tên: "); scanf(" %[^\n]", current->name);
            printf("Giới tính: "); scanf(" %[^\n]", current->gender);
            printf("Ngày sinh: "); scanf(" %[^\n]", current->dob);
            printf("Ngày cấp thẻ: "); scanf(" %[^\n]", current->cardIssueDate);
            printf("Ngày hết hạn thẻ: "); scanf(" %[^\n]", current->cardExpiryDate);
            printf("Đã cập nhật thông tin.\n");
            return;
        }
        current = current->next;
    }
    printf("Không tìm thấy người đọc.\n");
}

void deleteReader(Reader** head) {
    char targetID[MAX_ID_LEN];
    printf("Nhập ID người đọc cần xoá: ");
    scanf(" %[^\n]", targetID);
    Reader *current = *head, *prev = NULL;
    while (current != NULL && strcmp(current->id, targetID) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Không tìm thấy người đọc.\n");
        return;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    printf("Đã xoá người đọc.\n");
}

void searchByID(Reader* head) {
    char targetID[MAX_ID_LEN];
    printf("Nhập ID cần tìm: ");
    scanf(" %[^\n]", targetID);

    Reader* current = head;
    while (current != NULL) {
        if (strcmp(current->id, targetID) == 0) {
            printf("Tìm thấy:\n");
            printf("ID: %s | Tên: %s | Giới tính: %s | Ngày sinh: %s | Cấp: %s | Hết hạn: %s\n",
                   current->id, current->name, current->gender,
                   current->dob, current->cardIssueDate, current->cardExpiryDate);
            return;
        }
        current = current->next;
    }
    printf("Không tìm thấy người đọc.\n");
}

void searchByName(Reader* head) {
    char targetName[MAX_NAME_LEN];
    printf("Nhập tên hoặc từ khoá tên cần tìm: ");
    scanf(" %[^\n]", targetName);

    Reader* current = head;
    int found = 0;
    while (current != NULL) {
        if (strstr(current->name, targetName) != NULL) {
            printf("ID: %s | Tên: %s | Giới tính: %s | Ngày sinh: %s | Cấp: %s | Hết hạn: %s\n",
                   current->id, current->name, current->gender,
                   current->dob, current->cardIssueDate, current->cardExpiryDate);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("Không tìm thấy người đọc.\n");
}
