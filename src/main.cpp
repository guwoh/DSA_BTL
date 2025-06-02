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

        printf("\nNhập lựa chọn của bạn: ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                void choiceBook();
                break;
            case 2:
                void choiceMember();
                break;
            case 3:
                void choiceLoan();
                break;
            case 4:
                void choiceThongKe();
                break;
            case 0:
                printf("Thoát chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ. Vui lòng thử lại.\n");
        }

        printf("\n-----------------------------------------\n");

    } while (luaChon != 0);
     return 0;
}
   

