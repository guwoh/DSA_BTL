/**
 * @file main.c
 * @author guwoh (hoanghiephaikanamaconggmail.com)
 * @author (you@domain.com)
 * @author (you@domain.com)
 * @author (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-05-16
 * 
 * @copyright Copyright (c) 2025
 *hehe 
 */
#include <iostream>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"


int main() {
    int luaChon;

    do {
        void hienThiMenuChinh();

        printf("\nNhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        while (getchar() != '\n'); // Xóa bộ đệm nhập
        printf("\n-----------------------------------------\n");
        switch (luaChon) {
            case 1:
                NodeTopic* topicList = NULL;
                initTopic(&topicList); // Khởi tạo danh sách chủ đề sách
                choiceBook(topicList);
                // Giải phóng bộ nhớ
                NodeTopic* currentTopic = topicList;
                while (currentTopic != NULL) {
                    NodeTopic* tempTopic = currentTopic;
                    currentTopic = currentTopic->next;

                    NodeBook* currentBook = tempTopic->listBook;
                    while (currentBook != NULL) {
                        NodeBook* tempBook = currentBook;
                        currentBook = currentBook->next;
                        delete tempBook;
                    }
                    delete tempTopic;
                }
                topicList = NULL;
                break;
            case 2:
                Reader* readerList = NULL;
                choiceMember(&readerList);
                // Giải phóng bộ nhớ
                while (readerList) {
                    Reader* temp = readerList;
                    readerList = readerList->next;
                    free(temp);
                }
                break;
            case 3:
                BorrowSlip* borrowList = NULL;
                choiceLoan(&borrowList);
                while (borrowList) {
                    BorrowSlip* temp = borrowList;
                    borrowList = borrowList->next;
                    free(temp);
                }   
                break;
            case 4:
                choiceThongKe(topicList, borrowList, readerList);
                break;
            case 0:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }

        printf("\n-----------------------------------------\n");

    } while (luaChon != 0);
     return 0;
}
   

