#include <stdio.h>

#include "book.h"
#include "loan.h"
#include "member.h"
#include "utils.h"

int main() {
    menu(); // Hàm này bạn phải định nghĩa trong utils.h hoặc tương tự
	// hiep is here
    int choice; // Lựa chọn của người dùng
    do {
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Gọi hàm xử lý sách
                handle_books();
                break;
            case 2:
                // Gọi hàm xử lý người đọc
                handle_readers();
                break;
            case 3:
                // Gọi hàm xử lý mượn/trả
                handle_loans();
                break;
            case 4:
                // Gọi hàm thống kê
                show_statistics();
                break;
            case 0:
                printf("Thoát chương trình.\n");
                break;
            default:
                printf("Lựa chọn không hợp lệ!\n");
        }
    } while (choice != 0);

    return 0;
}

