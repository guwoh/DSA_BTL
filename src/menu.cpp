#include<stdio.h>
#include <stdlib.h>

#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"

// MENU chính
void hienThiMenuChinh() {
    printf("===== HE THONG QUAN LY THU VIEN =====\n");
    printf("1. Quan ly sach\n");
    printf("2. Quan ly nguoi doc\n");
    printf("3. Quan ly muon/tra sach\n");
    printf("4. Thong ke\n");
    printf("0. Thoat\n");
}

// MENU phần Book
void menuBook() {
    printf("----- MENU QUAN LY SACH -----\n");
    printf("1. Hien thi chu de va sach co san\n");
    printf("2. Them chu de va sach\n");
    printf("3. Sua thong tin sach\n");
    printf("4. Tim kiem sach\n");
    printf("5. Xoa chu de hoac sach\n");
    printf("0. Quay lai menu chinh\n");
}

void choiceBook(NodeTopic** tp) {
    int choice;
    do {
        menuBook();
        printf("Chon chuc nang quan ly sach: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Xóa bộ đệm nhập
        switch (choice) {
            case 1:
                display2(*tp);
                break;
            case 2:
                addNew(tp);
                display2(*tp);
                break;
            case 3:
                editBook(tp);
                break;
            case 4:
                searchByID1(tp);
                break;
            case 5:
                deleteBookOrTopic(tp);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
        printf("\n");
    } while (choice != 0);
}

// MENU phần Member
void menuMember() {
    printf("----- MENU QUAN LY DOC GIA -----\n");
    printf("1. Them nguoi doc\n");
    printf("2. Sua thong tin nguoi doc\n");
    printf("3. Xoa nguoi doc\n");
    printf("4. Tim kiem nguoi doc theo ID\n");
    printf("5. Tim kiem nguoi doc theo ten\n");
    printf("6. Hien thi danh sach nguoi doc\n");
    printf("0. Quay lai menu chinh\n");
}

void choiceMember(Reader** head) {
    int choice;
    do {
        menuMember();
        printf("Chon chuc nang quan ly doc gia: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Xóa bộ đệm nhập
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
                searchByID(*head);
                break;
            case 5:
                searchByName(*head);
                break;
            case 6:
                listReaders(*head);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
        printf("\n");
    } while (choice != 0);
}

// MENU phần Loan
void menuLoan() {
    printf("----- MENU QUAN LY MUON/TRA SACH -----\n");
    printf("1. Them phieu muon sach\n");
    printf("2. Tra sach\n");
    printf("3. Xoa phieu muon\n");
    printf("4. Hien thi danh sach phieu muon\n");
    printf("5. Hien thi danh sach chua tra\n");
    printf("6. Kiem tra dieu kien muon\n");
    printf("0. Quay lai menu chinh\n");
}

void choiceLoan(BorrowSlip* borrowList, Reader* readerList, NodeTopic* topicList) {
    int choice;
    do {
        menuLoan();
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Xóa bộ đệm nhập
        
        switch (choice) {
            case 1:
                addBorrowSlip(&borrowList, readerList, topicList);
                break;
            case 2:
                returnBook(borrowList);
                break;
            case 3:
                deleteBorrowSlip(&borrowList);
                break;
            case 4:
                listBorrowSlips(borrowList);
                break;
            case 5:
                listUnreturnedBooks(borrowList);
                break;
            case 6:
                checkBorrowConditions(borrowList);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
        printf("\n");
    } while (choice != 0);
}

// MENU phần thống kê
void menuThongKe() {
    printf("----- MENU THONG KE -----\n");
    printf("1. Thong ke sach duoc muon nhieu nhat\n");
    printf("2. Thong ke doc gia muon nhieu nhat\n");
    printf("3. Thong ke so sach dang duoc muon\n");
    printf("0. Quay lai menu chinh\n");
}

void choiceThongKe(NodeTopic* topicList, BorrowSlip* slipList, Reader* readerList) {
    int choice;
    do {
        menuThongKe();
        printf("Chon so lieu muon thong ke: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Xóa bộ đệm nhập
        switch (choice) {
            case 1:
                printf("Thuc hien thong ke muon sach nhieu nhat...\n");
                findTop3Books(topicList, slipList);
                break;
            case 2:
                printf("Thuc hien thong ke doc gia muon nhieu nhat...\n");
                findTop3Readers(readerList, slipList);
                break;
            case 3:
                printf("Thuc hien thong ke so sach dang duoc muon...\n");
                hienThiBorrowedBooks(slipList);
                break;
            case 0:
                printf("Quay lai menu chinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
        printf("\n");
    } while (choice != 0);
}