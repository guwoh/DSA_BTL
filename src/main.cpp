#include <iostream>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"
// hiep is here

int main() {
    NodeTopic* topicList;
    initTopic(&topicList); // Khởi tạo danh sách chủ đề sách
    Reader* readerList = NULL;
    BorrowSlip* borrowList = NULL;
    int luaChon;

    do {
        hienThiMenuChinh();

        printf("\nNhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        while (getchar() != '\n'); // Xóa bộ đệm nhập
        printf("\n-----------------------------------------\n");
        switch (luaChon) {
            case 1:
                choiceBook(&topicList);
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
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }

        printf("\n-----------------------------------------\n");

    } while (luaChon != 0);
     return 0;
}
   

