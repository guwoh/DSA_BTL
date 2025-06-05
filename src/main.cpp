#include <iostream>
#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include "../include/menu.h"
// // hiep is here

int main() {
    NodeTopic* topicList;
    initTopic(&topicList); // Khởi tạo danh sách chủ đề sách
    Reader* readerList = NULL;
    BorrowSlip* borrowList = NULL;
    int luaChon;

    printf("Doc du lieu tu kho du lieu...\n");
    //  cập nhật data từ file bin

    // book, data số lượng sách trong kho
    bookReadBin(&topicList, "book.bin"); // cần thay đổi biến được truyền

    // reader, data thành viên đọc, sử dụng thư viện
    readerReadBin(readerList, "reader.bin"); // cần thay đổi biến được truyền 

    // loan, data phiếu mượn
    borrowSlipReadBin(&borrowList, "borrowSlip.bin"); // cần thay đổi biến được truyền 


    // utilis, data thống kê

    // book
    if(topicList == NULL) printf("Khong co du lieu ve sach!\n");
    else if(topicList != NULL) printf("Cap nhat du lieu sach thanh cong!\n");
    // member
    if(readerList == NULL) printf("Khong co du lieu ve thanh vien!\n");
    else if(readerList != NULL) printf("Cap nhat du lieu thanh vien thanh cong!\n");
    //borrow
    if(borrowList == NULL) printf("Khong co du lieu ve muon sach!\n");
    else if(borrowList != NULL) printf("Cap nhat du lieu sach duoc muon thanh cong!\n");
    // utilis
    //if(topicList == NULL) printf("Khong co du lieu ve thong ke!\n");
    //else if(topicList == NULL) printf("Cap nhat du lieu ve thong ke thanh cong!\n");
    
    printf("\n");
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
                choiceLoan(&borrowList, readerList, topicList);
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

    borrowSlipWriteBin(borrowList, "borrowSlip.bin");
    borrowSlipWriteText(borrowList, "borrowSlip.txt");
    
        
    printf("\n          THOAT CHUONG TRINH!");
    printf("\n-----------------------------------------\n");
    return 0;
}


