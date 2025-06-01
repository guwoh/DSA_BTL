#include<stdio.h>

#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"

// MENU chính
void hienThiMenuChinh() {
    printf("===== HỆ THỐNG QUẢN LÝ THƯ VIỆN =====\n");
    printf("1. Quản lý sách\n");
    printf("2. Quản lý người đọc\n");
    printf("3. Quản lý mượn/trả sách\n");
    printf("4. Thống kê\n");
    printf("0. Thoát\n");
}

// MENU phần thống kê
void menuThongKe() {
    printf("----- MENU THỐNG KÊ -----\n");
    printf("1. Thống kê sách mượn nhiều nhất\n");
    printf("2. Thống kê độc giả mượn nhiều nhất\n");
    printf("3. Thống kê sách đang được mượn\n");
    printf("0. Quay lại menu chính\n");
}

void choiceThongKe() {
    int choice;
    do {
        menuThongKe();
        printf("Chọn số liệu muốn thống kê: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Thực hiện thống kê sách mượn nhiều nhất...\n");
                void findTop3Books(NodeTopic* topicList, BorrowSlip* slipList);
                break;
            case 2:
                printf("Thực hiện thống kê độc giả mượn nhiều nhất...\n");
                void findTop3Readers(Reader* readerList, BorrowSlip* slipList);
                break;
            case 3:
                printf("Thực hiện thống kê sách được mượn nhiều nhất...\n");
                void hienThiBorrowedBooks(BorrowSlip* head);
                break;
            case 0:
                printf("Quay lại menu chính...\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
        printf("\n");
    } while (choice != 0);
}

// MENU phần Book
void menuBook() {
    printf("----- MENU QUẢN LÝ SÁCH -----\n");
    printf("1. Khởi tạo chủ đề\n");
    printf("2. Thêm chủ đề\n");
    printf("3. Thêm sách mới\n");
    printf("4. Sửa thông tin sách\n");
    printf("5. Xóa sách hoặc chủ đề\n");
    printf("6. Hiển thị sách của 1 chủ đề\n");
    printf("7. Hiển thị tất cả thư viện\n");
    printf("8. Hiển thị thông tin 1 sách cụ thể\n");
    printf("0. Quay lại menu chính\n");
}

void choiceBook() {
    int choice;
    do {
        menuBook();
        printf("Chọn chức năng quản lý sách: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initTopic();
                break;
            case 2:
                addTopic();
                break;
            case 3:
                addNew();
                break;
            case 4:
                editBook();
                break;
            case 5:
                deleteBookOrTopic();
                break;
            case 6:
                display();
                break;
            case 7:
                display2();
                break;
            case 8:
                display3();
                break;
            case 0:
                printf("Quay lại menu chính...\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ, vui lòng thử lại.\n");
        }
        printf("\n");
    } while (choice != 0);
}

// MENU phần Member
void menuMember() {
    printf("----- MENU QUẢN LÝ ĐỘC GIẢ -----\n");
    printf("1. Thêm độc giả\n");
    printf("2. Sửa thông tin độc giả\n");
    printf("3. Xóa độc giả\n");
    printf("4. Tìm kiếm độc giả theo tên\n");
    printf("5. Tìm kiếm độc giả theo ID\n");
    printf("6. Hiển thị danh sách độc giả\n");
    printf("0. Quay lại menu chính\n");
}

void choiceMember(Reader** head) {
    int choice;
    do {
        menuMember();
        printf("Chọn chức năng quản lý độc giả: ");
        scanf("%d", &choice);

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
                printf("Quay lại menu chính...\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ, vui lòng thử lại.\n");
        }
        printf("\n");
    } while (choice != 0);
}

// MENU phần Loan
void menuLoan() {
    printf("----- MENU QUẢN LÝ MƯỢN/TRẢ SÁCH -----\n");
    printf("1. Tạo phiếu mượn sách\n");
    printf("2. Trả sách\n");
    printf("3. Hiển thị danh sách phiếu mượn\n");
    printf("4. Hiển thị sách chưa trả\n");
    printf("5. Kiểm tra điều kiện mượn\n");
    printf("0. Quay lại menu chính\n");
}

void choiceLoan(BorrowSlip** head) {
    int choice;
    do {
        menuLoan();
        printf("Chọn chức năng: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createBorrowSlip(head);
                break;
            case 2:
                returnBook(*head);
                break;
            case 3:
                listBorrowSlips(*head);
                break;
            case 4:
                listUnreturnedBooks(*head);
                break;
            case 5:
                checkBorrowConditions(*head);
                break;
            case 0:
                printf("Quay lại menu chính...\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }
        printf("\n");
    } while (choice != 0);
}