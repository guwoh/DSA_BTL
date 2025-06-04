#include <iostream>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"
// // hiep is here

int main() {
    NodeTopic* topicList = NULL;
    initTopic(&topicList); // Khởi tạo danh sách chủ đề sách
    Reader* readerList = NULL;
    BorrowSlip* borrowList = NULL;
    int luaChon;

    printf("Doc du lieu tu kho (neu co)...\n");
    //  cập nhật data từ file bin

    // book, data số lượng sách trong kho
    bookReadBin(&topicList, "book.bin"); // cần thay đổi biến được truyền

    // reader, data thành viên đọc, sử dụng thư viện
    readerReadBin(readerList, "reader.bin"); // cần thay đổi biến được truyền 

    // loan, data phiếu mượn

    // utilis, data thống kê

    // book
    if(topicList == NULL) printf("Khong co du lieu ve sach!\n");
    else if(topicList != NULL) printf("Cap nhat du lieu sach thanh cong!\n");
    // member
    if(readerList == NULL) printf("Khong co du lieu ve thanh vien!\n");
    else if(readerList == NULL) printf("Cap nhat du lieu thanh vien thanh cong!\n");
    //borrow
    if(topicList == NULL) printf("Khong co du lieu ve muon sach!\n");
    else if(topicList == NULL) printf("Cap nhat du lieu sach duoc muon thanh cong!\n");
    // utilis
    if(topicList == NULL) printf("Khong co du lieu ve thong ke!\n");
    else if(topicList == NULL) printf("Cap nhat du lieu ve thong ke thanh cong!\n");
    
    printf("\n");
    do {
        hienThiMenuChinh();

        printf("\nNhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        while (getchar() != '\n'); // Xóa bộ đệm nhập
        printf("\n-----------------------------------------\n");
        switch (luaChon) {
            case 1:
                choiceBook(topicList);
                break;
            case 2:
                choiceMember(&readerList);
                break;
            case 3:
                choiceLoan(borrowList, readerList, topicList);
                break;
            case 4:
                choiceThongKe(topicList, borrowList, readerList);
                break;
            case 0:
                // printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }

        

    } while (luaChon != 0);
    
    printf("\n");
    printf("Luu tru du lieu...\n");

    // lưu file txt and bin
    bookWriteText(topicList, "book.txt");
    bookWriteBin(topicList, "book.bin");

    readerWriteText(readerList, "reader.txt");
    readerWriteBin(readerList, "reader.bin");
    
    printf("\n          THOAT CHUONG TRINH!");
    printf("\n-----------------------------------------\n");
    return 0;
}




// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>



// #define MAX_TOPIC 100

// // Hàm hiển thị thông tin sách trong một NodeBook
// void displayBooks(NodeBook* bookList) {
//     NodeBook* current = bookList;
//     while (current != NULL) {
//         Book b = current->book;
//         printf("  Ma sach: %s\n", b.id);
//         printf("  Ten sach: %s\n", b.name);
//         printf("  Tac gia: %s\n", b.author);
//         printf("  Nam xuat ban: %d\n", b.year);
//         printf("  So luong: %d\n\n", b.quantity);
//         current = current->next;
//     }
// }

// // Hàm hiển thị thông tin tất cả chủ đề và sách
// void displayTopics(NodeTopic* topicList) {
//     NodeTopic* current = topicList;
//     if (current == NULL) {
//         printf("Danh sach chu de trong!\n");
//         return;
//     }

//     while (current != NULL) {
//         printf("Chu de: %s\n", current->nameTopic);
//         printf("Danh sach sach:\n");
//         displayBooks(current->listBook);
//         current = current->next;
//     }
// }

// // Hàm giải phóng bộ nhớ
// void freeTopicList(NodeTopic** head) {
//     NodeTopic* current = *head;
//     while (current != NULL) {
//         NodeTopic* tempTopic = current;
//         current = current->next;
//         NodeBook* book = tempTopic->listBook;
//         while (book != NULL) {
//             NodeBook* tempBook = book;
//             book = book->next;
//             free(tempBook);
//         }
//         free(tempTopic);
//     }
//     *head = NULL;
// }

// int main() {
//     // Khởi tạo danh sách chủ đề
//     NodeTopic* topicList = NULL;

//     // Thêm chủ đề 1: "Van hoc"
//     NodeTopic* topic1 = (NodeTopic*)malloc(sizeof(NodeTopic));
//     if (!topic1) {
//         printf("Loi cap phat bo nho cho topic1!\n");
//         return 1;
//     }

    
//     printf("Doc du lieu tu kho (neu co)...\n");
//     //  cập nhật data từ file bin

//     // book, data số lượng sách trong kho
//     bookReadBin(&topicList, "book.bin"); // cần thay đổi biến được truyền

//     // reader, data thành viên đọc, sử dụng thư viện
//    // readerReadBin(readerList, "reader.bin"); // cần thay đổi biến được truyền 

//     // loan, data phiếu mượn

//     // utilis, data thống kê

//     // book
//     if(topicList == NULL) printf("Khong co du lieu ve sach!\n");
//     else if(topicList != NULL) printf("Cap nhat du lieu sach thanh cong!\n");
//     // member
//     //if(readerList == NULL) printf("Khong co du lieu ve thanh vien!\n");
//     //else if(readerList == NULL) printf("Cap nhat du lieu thanh vien thanh cong!\n");
//     //borrow
//     if(topicList == NULL) printf("Khong co du lieu ve muon sach!\n");
//     else if(topicList == NULL) printf("Cap nhat du lieu sach duoc muon thanh cong!\n");
//     // utilis
//     if(topicList == NULL) printf("Khong co du lieu ve thong ke!\n");
//     else if(topicList == NULL) printf("Cap nhat du lieu ve thong ke thanh cong!\n");
    
//     // strcpy(topic1->nameTopic, "Van hoc");
//     // topic1->listBook = NULL;
//     // topic1->next = NULL;

//     // // Thêm sách vào chủ đề 1
//     // NodeBook* book1 = (NodeBook*)malloc(sizeof(NodeBook));
//     // if (!book1) {
//     //     printf("Loi cap phat bo nho cho book1!\n");
//     //     free(topic1);
//     //     return 1;
//     // }
//     // strcpy(book1->book.id, "B001");
//     // strcpy(book1->book.name, "Truyen Kieu");
//     // strcpy(book1->book.author, "Nguyen Du");
//     // book1->book.year = 1820;
//     // book1->book.quantity = 5;
//     // book1->next = NULL;
//     // topic1->listBook = book1;

//     // NodeBook* book2 = (NodeBook*)malloc(sizeof(NodeBook));
//     // if (!book2) {
//     //     printf("Loi cap phat bo nho cho book2!\n");
//     //     free(book1);
//     //     free(topic1);
//     //     return 1;
//     // }
//     // strcpy(book2->book.id, "B002");
//     // strcpy(book2->book.name, "Luc Van Tien");
//     // strcpy(book2->book.author, "Nguyen Dinh Chieu");
//     // book2->book.year = 1850;
//     // book2->book.quantity = 3;
//     // book2->next = NULL;
//     // book1->next = book2;

//     // // Thêm chủ đề 2: "Khoa hoc"
//     // NodeTopic* topic2 = (NodeTopic*)malloc(sizeof(NodeTopic));
//     // if (!topic2) {
//     //     printf("Loi cap phat bo nho cho topic2!\n");
//     //     free(book2);
//     //     free(book1);
//     //     free(topic1);
//     //     return 1;
//     // }
//     // strcpy(topic2->nameTopic, "Khoa hoc");
//     // topic2->listBook = NULL;
//     // topic2->next = NULL;

//     // // Thêm sách vào chủ đề 2
//     // NodeBook* book3 = (NodeBook*)malloc(sizeof(NodeBook));
//     // if (!book3) {
//     //     printf("Loi cap phat bo nho cho book3!\n");
//     //     free(topic2);
//     //     free(book2);
//     //     free(book1);
//     //     free(topic1);
//     //     return 1;
//     // }
//     // strcpy(book3->book.id, "B003");
//     // strcpy(book3->book.name, "Vat ly co ban");
//     // strcpy(book3->book.author, "Richard Feynman");
//     // book3->book.year = 1965;
//     // book3->book.quantity = 10;
//     // book3->next = NULL;
//     // topic2->listBook = book3;

//     // // Liên kết các chủ đề
//     // topicList = topic1;
//     // topic1->next = topic2;

//     // // Hiển thị thông tin
//     // printf("=== DANH SACH CHU DE VA SACH ===\n");
//     displayTopics(topicList);


//     // printf("\n");
//     // printf("Luu tru du lieu...\n");

//     // // lưu file txt and bin
//     // bookWriteText(topicList, "book.txt");
//     // bookWriteBin(topicList, "book.bin");

//     // //readerWriteText(readerList, "reader.txt");
//     // //readerWriteBin(readerList, "reader.bin");
    
//     // printf("\n          THOAT CHUONG TRINH!");
//     // printf("\n-----------------------------------------\n");
//     // // Giải phóng bộ nhớ
//     freeTopicList(&topicList);

//     return 0;
// }