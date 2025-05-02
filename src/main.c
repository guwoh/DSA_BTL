#include<stdio.h>

#include<book.h>
#include<loan.h>
#include<member.h>
#include<utils.h>

int main() {
    menu();
    int choice; // Lựa chọn của người dùng
    while (choice != 0) {
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: /*Books option*/; break;
            case 2: /*Readers option*/; break;
            case 3: /*Mượn trả option*/; break;
            case 4: /*Thống kế option*/; break;
            case 0: /*Exit option*/; break;
            default: printf("Lựa chọn không hợp lệ!\n");
        }
    }  
}