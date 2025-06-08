#include <stdio.h>                      //⇒ Thư viện I/O chuẩn: hàm fopen, fread, fwrite, fprintf, printf…
#include <stdlib.h>                     //⇒ Thư viện chuẩn: malloc, free, atoi, v.v.
#include <string.h>                     //⇒ Thư viện xử lý chuỗi: strcpy, strlen, sprintf…

#include "../include/book.h"            //⇒ Khai báo struct Book, NodeBook, NodeTopic… (định nghĩa ở file book.h)
#include "../include/loan.h"            //⇒ Khai báo struct BorrowSlip …
#include "../include/member.h"          //⇒ Khai báo struct Reader …
#include "../include/io.h"              //⇒ Khai báo prototype cho các hàm I/O đang cài đặt ở đây

#define MAX_TOPIC 200                   //⇒ Số ký tự tối đa cho tên chủ đề sách (để ghi/đọc nhị phân)

//====================
// PHẦN XỬ LÝ SÁCH
//====================

//--------------------------------------------------
// GHI DANH SÁCH SÁCH RA FILE TEXT
//--------------------------------------------------
void bookWriteText(NodeTopic* head, const char* fileName)           //⇒ Nhận con trỏ đầu danh sách topic & tên file đích
{
    char fullPath[100];                                             //⇒ Mảng chứa đường dẫn hoàn chỉnh
    sprintf(fullPath, "../doc/outPut/txt/%s", fileName);            //⇒ Ghép đường dẫn thư mục + tên file

    FILE* fp = fopen(fullPath, "w");                                //⇒ Mở file ở chế độ ghi (text)
    if (!fp) {                                                      //⇒ Nếu mở thất bại → thoát hàm
        return;
    }

    NodeTopic* topic = head;                                        //⇒ Bắt đầu duyệt danh sách topic
    fprintf(fp, "----------------DANH SACH TOPIC SACH----------------\n"); //⇒ In tiêu đề

    while (topic) {                                                 //⇒ Lặp qua từng topic
        fprintf(fp, "Topic: %s\n", topic->nameTopic);               //⇒ Ghi tên topic
        NodeBook* book = topic->listBook;                           //⇒ Con trỏ duyệt danh sách sách của topic

        while (book) {                                              //⇒ Lặp qua từng cuốn sách
            Book b = book->book;                                    //⇒ Sao chép struct Book để dùng ngắn gọn
            fprintf(fp,                                             //⇒ Ghi thông tin chi tiết sách thành nhiều dòng
                    "ID sach: %s\n  Ten sach: %s\n  Tac gia: %s\n  Nam xuat ban: %d\n  So luong: %d\n",
                    b.id, b.name, b.author, b.year, b.quantity);
            book = book->next;                                      //⇒ Chuyển sang sách kế tiếp
        }
        fprintf(fp, "END_TOPIC\n\n");                               //⇒ Đánh dấu kết thúc topic
        topic = topic->next;                                        //⇒ Chuyển sang topic kế tiếp
    }

    fclose(fp);                                                     //⇒ Đóng file
    fprintf(fp, "--------------------------------\n");              //⇒ (Dòng này lẽ ra in vào fp nhưng fp đã đóng – không có tác dụng)
    printf("Da luu danh sach vao file text thanh cong %s\n", fullPath); //⇒ Thông báo ra màn hình
}

//--------------------------------------------------
// GHI DANH SÁCH SÁCH RA FILE NHỊ PHÂN
//--------------------------------------------------
void bookWriteBin(NodeTopic* head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "../doc/outPut/bin/%s", fileName);            //⇒ Thư mục ./bin

    FILE* fp = fopen(fullPath, "wb");                               //⇒ Mở file dưới dạng ghi nhị phân
    if (!fp) { return; }

    NodeTopic* topic = head;
    while (topic) {
        fwrite(topic->nameTopic, sizeof(char), MAX_TOPIC, fp);      //⇒ Ghi đủ 200 byte tên topic (kể cả '\0' và phần thừa)

        int bookCount = 0;                                          //⇒ Đếm số sách thuộc topic
        NodeBook* tempBook = topic->listBook;
        while (tempBook) { bookCount++; tempBook = tempBook->next; }

        fwrite(&bookCount, sizeof(int), 1, fp);                     //⇒ Ghi số lượng sách (4 byte)

        tempBook = topic->listBook;                                 //⇒ Duyệt lại để ghi nội dung sách
        while (tempBook) {
            fwrite(&(tempBook->book), sizeof(Book), 1, fp);         //⇒ Ghi nguyên struct Book (định nghĩa trong book.h)
            tempBook = tempBook->next;
        }

        topic = topic->next;                                        //⇒ Sang topic tiếp
    }

    fclose(fp);
    printf("Da luu danh sach vao file bin thanh cong %s\n", fullPath);
}

//--------------------------------------------------
// ĐỌC DANH SÁCH SÁCH TỪ FILE NHỊ PHÂN
//--------------------------------------------------
void bookReadBin(NodeTopic** head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");                               //⇒ Mở file nhị phân để đọc
    if (!fp) { return; }

    char topicName[MAX_TOPIC];                                      //⇒ Bộ đệm cho tên chủ đề
    int bookCount;                                                  //⇒ Số sách trong topic
    Book book;                                                      //⇒ Biến tạm cho mỗi sách

    // Đọc tuần tự cho đến cuối file
    while (fread(topicName, sizeof(char), MAX_TOPIC, fp) == MAX_TOPIC) 
    {
        fread(&bookCount, sizeof(int), 1, fp);                      //⇒ Đọc số sách của topic

        NodeTopic* newTopic = (NodeTopic*)malloc(sizeof(NodeTopic));//⇒ Cấp phát node topic mới
        strcpy(newTopic->nameTopic, topicName);                     //⇒ Sao chép tên
        newTopic->listBook = NULL;                                  //⇒ Chưa có sách
        newTopic->next = NULL;

        // Thêm topic vào cuối danh sách liên kết *head
        if (*head == NULL) {
            *head = newTopic;
        } else {
            NodeTopic* temp = *head;
            while (temp->next) temp = temp->next;
            temp->next = newTopic;
        }

        // Đọc và thêm từng sách vào danh sách sách của topic mới
        for (int i = 0; i < bookCount; i++) {
            fread(&book, sizeof(Book), 1, fp);                      //⇒ Đọc struct Book

            NodeBook* newBook = (NodeBook*)malloc(sizeof(NodeBook));//⇒ Node sách mới
            newBook->book = book;
            newBook->next = NULL;

            if (newTopic->listBook == NULL) {                       //⇒ Thêm vào đầu
                newTopic->listBook = newBook;
            } else {                                                //⇒ Thêm vào cuối
                NodeBook* tempBook = newTopic->listBook;
                while (tempBook->next) tempBook = tempBook->next;
                tempBook->next = newBook;
            }
        }
    }

    fclose(fp);
    printf("Da doc du lieu ve sach thanh cong %s\n", fullPath);
}

//=====================
// PHẦN XỬ LÝ NGƯỜI ĐỌC
//=====================

//--------------------------------------------------
// GHI DANH SÁCH NGƯỜI ĐỌC RA FILE TEXT
//--------------------------------------------------
void readerWriteText(Reader* head, const char* fileName) 
{
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/txt/%s", fileName); //⇒ Dùng snprintf an toàn hơn sprintf

    FILE* fp = fopen(fullPath, "w");
    if (!fp) { return; }

    fprintf(fp, "----------------DANH SACH NGUOI DOC----------------\n");
    Reader* current = head;
    int count = 0;

    while (current != NULL) {
        count++;
        fprintf(fp, "\nNguoi doc thu %d:\n", count);
        fprintf(fp, 
                "ID nguoi doc: %s\n Ten nguoi doc: %s\n Gioi tinh: %s\n Ngay sinh: %s\n Ngay cap the: %s\n Ngay het han: %s\n",
                current->id, current->name, current->gender,
                current->dob, current->cardIssueDate, current->cardExpiryDate);
        current = current->next;
    }

    fclose(fp);
    printf("Da luu danh sach nguoi doc vao file text thanh cong %s\n", fullPath);
}

//--------------------------------------------------
// GHI DANH SÁCH NGƯỜI ĐỌC RA FILE NHỊ PHÂN
//--------------------------------------------------
void readerWriteBin(Reader* head, const char* fileName) 
{
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "wb");
    if (!fp) { return; }

    Reader* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Reader), 1, fp);                      //⇒ Ghi thẳng nguyên struct Reader
        current = current->next;
    }

    fclose(fp);
    printf("Da luu danh sach nguoi doc vao file bin thanh cong %s\n", fullPath);
}

//--------------------------------------------------
// ĐỌC DANH SÁCH NGƯỜI ĐỌC TỪ FILE NHỊ PHÂN
//--------------------------------------------------
void readerReadBin(Reader*& head, const char* fileName)   //⇒ Tham chiếu con trỏ head để cập nhật
{ 
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");
    if (!fp) { return; }

    Reader temp;                                                     //⇒ Biến tạm
    while (fread(&temp, sizeof(Reader), 1, fp)) {                    //⇒ Đọc từng Reader
        Reader* newReader = (Reader*)malloc(sizeof(Reader));
        if (!newReader) {                                            //⇒ Kiểm tra cấp phát
            printf("Loi cap phat bo nho khi doc.\n");
            fclose(fp);
            return;
        }
        *newReader = temp;                                           //⇒ Copy dữ liệu tạm
        newReader->next = NULL;

        if (head == NULL) {                                          //⇒ Thêm vào đầu
            head = newReader;
        } else {                                                     //⇒ Thêm cuối
            Reader* last = head;
            while (last->next != NULL) last = last->next;
            last->next = newReader;
        }
    }

    fclose(fp);
    printf("Da doc du lieu nguoi doc thanh cong %s\n", fullPath);
}

//===============================
// PHẦN XỬ LÝ PHIẾU MƯỢN (BorrowSlip)
//===============================

//--------------------------------------------------
// GHI DANH SÁCH PHIẾU MƯỢN RA FILE TEXT
//--------------------------------------------------
void borrowSlipWriteText(BorrowSlip* head, const char* fileName) 
{
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/txt/%s", fileName);

    FILE* fp = fopen(fullPath, "w");
    if (!fp) { return; }

    fprintf(fp, "----------------DANH SACH PHIEU MUON----------------\n");
    BorrowSlip* current = head;
    int count = 0;

    while (current != NULL) {
        count++;
        fprintf(fp, "\nPhieu muon thu %d:\n", count);
        fprintf(fp, 
                "ID phieu: %s\n ID sach: %s\n ID nguoi doc: %s\n Ngay muon: %s\n Ngay het han: %s\n Ngay tra: %s\n",
                current->slipID, current->bookID, current->readerID,
                current->borrowDate, current->dueDate, current->returnDate);
        current = current->next;
    }
    fprintf(fp, "\n--------------------------------\n");
    fclose(fp);
    printf("Da luu danh sach phieu muon vao file text thanh cong %s\n", fullPath);
}

//--------------------------------------------------
// GHI DANH SÁCH PHIẾU MƯỢN RA FILE NHỊ PHÂN
//--------------------------------------------------
void borrowSlipWriteBin(BorrowSlip* head, const char* fileName)
{
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "wb");
    if (!fp) { return; }

    BorrowSlip* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(BorrowSlip), 1, fp);                  //⇒ Ghi thẳng struct BorrowSlip
        current = current->next;
    }

    fclose(fp);
    printf("Da luu danh sach phieu muon vao file bin thanh cong %s\n", fullPath);
}

//--------------------------------------------------
// ĐỌC DANH SÁCH PHIẾU MƯỢN TỪ FILE NHỊ PHÂN
//--------------------------------------------------
void borrowSlipReadBin(BorrowSlip** head, const char* fileName) 
{
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");
    if (!fp) return;

    BorrowSlip temp;
    BorrowSlip** current = head;                                     //⇒ Dùng con trỏ cấp 2 để dễ gắn cuối danh sách

    while (fread(&temp, sizeof(BorrowSlip), 1, fp)) {                //⇒ Đọc từng phiếu mượn
        BorrowSlip* newNode = (BorrowSlip*)malloc(sizeof(BorrowSlip));
        if (!newNode) {
            printf("Loi cap phat bo nho.\n");
            fclose(fp);
            return;
        }
        *newNode = temp;
        newNode->next = NULL;

        *current = newNode;                                          //⇒ Gắn node mới vào cuối
        current = &((*current)->next);                               //⇒ current trỏ tới con trỏ next của node mới
    }
    
    fclose(fp);
    printf("Da doc du lieu phieu muon thanh cong %s\n", fullPath);
}
