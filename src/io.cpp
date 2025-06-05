#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/io.h"

#define MAX_TOPIC 200

// const char* TEXT_FILE_BOOK = "doc/outPut/txt/book.txt";
// const char* BIN_FILE_BOOK = "doc/outPut/bin/book.bin";
// const char* TEXT_FILE_READER = "doc/outPut/txt/reader.txt";
// const char* BIN_FILE_READER = "doc/outPut/bin/reader.bin";


// data book****************************************************    

// =============================
// GHI DỮ LIỆU DẠNG TEXT
// =============================
void bookWriteText(NodeTopic* head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "../doc/outPut/txt/%s", fileName);  // Nối đường dẫn + tên file

    FILE* fp = fopen(fullPath, "w");
    if (!fp) {
        return;
    }

    NodeTopic* topic = head; // khai bao 
    while (topic) { // duyet qua tung list topic
        fprintf(fp, "Topic: %s\n", topic->nameTopic); // print name of topic
        NodeBook* book = topic->listBook;
        while (book) { // duyet qua tung  list book
            Book b = book->book;
            fprintf(fp, "%s;%s;%s;%d;%d\n", b.id, b.name, b.author, b.year, b.quantity);
            book = book->next;
        }
        fprintf(fp, "END_TOPIC\n");
        topic = topic->next;
    }

    fclose(fp);
    printf("Da luu danh sach vao file text thanh cong %s\n", fullPath);
}

// =============================
// GHI DỮ LIỆU DẠNG NHỊ PHÂN
// =============================
void bookWriteBin(NodeTopic* head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "wb");
    if (!fp) {
        return;
    }

    NodeTopic* topic = head;
    while (topic) {
        // Ghi tên chủ đề
        fwrite(topic->nameTopic, sizeof(char), MAX_TOPIC, fp);

        // Đếm số sách
        int bookCount = 0;
        NodeBook* tempBook = topic->listBook;
        while (tempBook) {
            bookCount++;
            tempBook = tempBook->next;
        }

        fwrite(&bookCount, sizeof(int), 1, fp); // ghi số sách vào bin

        // Ghi thông tin từng sách
        tempBook = topic->listBook;
        while (tempBook) {
            fwrite(&(tempBook->book), sizeof(Book), 1, fp);
            tempBook = tempBook->next;
        }

        topic = topic->next;
    }

    fclose(fp);
    printf("Da luu danh sach vao file bin thanh cong %s\n", fullPath);
}

// =============================
// ĐỌC DỮ LIỆU TỪ FILE NHỊ PHÂN
// =============================
void bookReadBin(NodeTopic** head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");
    if (!fp) {
        return;
    }

    char topicName[MAX_TOPIC];
    int bookCount;
    Book book;

    while (fread(topicName, sizeof(char), MAX_TOPIC, fp) == MAX_TOPIC) {
        fread(&bookCount, sizeof(int), 1, fp);

        // Tạo topic mới
        NodeTopic* newTopic = (NodeTopic*)malloc(sizeof(NodeTopic));
        strcpy(newTopic->nameTopic, topicName);
        newTopic->listBook = NULL;
        newTopic->next = NULL;

        // Thêm topic vào danh sách
        if (*head == NULL) {
            *head = newTopic;
        } else {
            NodeTopic* temp = *head;
            while (temp->next) temp = temp->next;
            temp->next = newTopic;
        }

        // Đọc các sách và thêm vào topic
        for (int i = 0; i < bookCount; i++) {
            fread(&book, sizeof(Book), 1, fp);

            NodeBook* newBook = (NodeBook*)malloc(sizeof(NodeBook));
            newBook->book = book;
            newBook->next = NULL;

            if (newTopic->listBook == NULL) {
                newTopic->listBook = newBook;
            } else {
                NodeBook* tempBook = newTopic->listBook;
                while (tempBook->next) tempBook = tempBook->next;
                tempBook->next = newBook;
            }
        }
    }

    fclose(fp);
    printf("Da doc du lieu ve sach thanh cong %s\n", fullPath);
}

// data reader*****************************************************

// =============================
// READER - TEXT
// =============================
void readerWriteText(Reader* head, const char* fileName) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/txt/%s", fileName);

    FILE* fp = fopen(fullPath, "w");
    if (!fp) 
    {
        return;
    }

    Reader* current = head;
    while (current != NULL) {
        fprintf(fp, "%s;%s;%s;%s;%s;%s\n",
                current->id, current->name, current->gender,
                current->dob, current->cardIssueDate, current->cardExpiryDate);
        current = current->next;
    }

    fclose(fp);
    printf("Da luu danh sach nguoi doc vao file text thanh cong %s\n", fullPath);
}

// =============================
// READER - BINARY
// =============================
void readerWriteBin(Reader* head, const char* fileName) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "wb");
    if (!fp) {
        return;
    }

    Reader* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Reader), 1, fp);
        //size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
        current = current->next;
    }

    fclose(fp);
    printf("Da luu danh sach nguoi doc vao file bin thanh cong %s\n", fullPath);
}

void readerReadBin(Reader*& head, const char* fileName) { // truyền tham chiếu giống C++
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");
    if (!fp) {
        return;
    }

    Reader temp;
    while (fread(&temp, sizeof(Reader), 1, fp)) {
        Reader* newReader = (Reader*)malloc(sizeof(Reader));
        if (!newReader) {
            printf("Loi cap phat bo nho khi doc.\n");
            fclose(fp);
            return;
        }
        *newReader = temp;
        newReader->next = NULL;

        if (head == NULL) {
            head = newReader;
        } else {
            Reader* last = head;
            while (last->next != NULL) last = last->next;
            last->next = newReader;
        }
    }

    fclose(fp);
    printf("Da doc du lieu nguoi doc thanh cong %s\n", fullPath);
}

// data borrow slip*****************************************************

// =============================
// GHI DỮ LIỆU DẠNG TEXT
// =============================
void borrowSlipWriteText(BorrowSlip* head, const char* fileName) {
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/txt/%s", fileName);

    FILE* fp = fopen(fullPath, "w");
    if (!fp) {
        return;
    }

    BorrowSlip* current = head; // khai bao con tro current
    while (current != NULL) {
        fprintf(fp, "%s;%s;%s;%s;%s;%s\n",
                current->slipID, current->bookID, current->readerID,
                current->borrowDate, current->dueDate, current->returnDate);
        current = current->next;
    }

    fclose(fp);
    printf("Da luu danh sach phieu muon vao file text thanh cong %s\n", fullPath);
}
// =============================
// GHI DỮ LIỆU DẠNG BIN
// =============================
void borrowSlipWriteBin(BorrowSlip* head, const char* fileName)
{
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "wb");
    if (!fp) {
        return;
    }   

    BorrowSlip* current = head; // khai bao con tro current
    while (current != NULL) {
        fwrite(current, sizeof(BorrowSlip), 1, fp);
        current = current->next;
    }

    fclose(fp);
    printf("Da luu danh sach phieu muon vao file bin thanh cong %s\n", fullPath);
}
// =============================
// ĐỌC DỮ LIỆU DẠNG BIN
// =============================
void borrowSlipReadBin(BorrowSlip** head, const char* fileName) 
{
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");
    if (!fp) return;

    BorrowSlip temp;
    BorrowSlip** current = head;  // current trỏ đến head ban đầu

    while (fread(&temp, sizeof(BorrowSlip), 1, fp)) {
        BorrowSlip* newNode = (BorrowSlip*)malloc(sizeof(BorrowSlip));
        if (!newNode) {
            printf("Loi cap phat bo nho.\n");
            fclose(fp);
            return;
        }
        *newNode = temp;
        newNode->next = NULL;

        *current = newNode;            // Gán node mới vào vị trí current đang trỏ đến
        current = &((*current)->next); // Di chuyển current đến next của node mới
    }
    
    fclose(fp);
    printf("Da doc du lieu phieu muon thanh cong %s\n", fullPath);
}

// data top reader*****************************************************

// attention: chỉ là struct bình thường

// =============================
// GHI DỮ LIỆU DẠNG TEXT
// =============================
void topReaderWriteText(TopReader* head, const char* fileName) {
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/txt/%s", fileName);


}


// =============================
// GHI DỮ LIỆU DẠNG BIN
// =============================
void topReaderWriteBin(TopReader* head, const char* fileName) {
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);
    
    
}

// =============================
// ĐỌC DỮ LIỆU DẠNG BIN
// =============================
void topReaderReadBin(TopReader*& head, const char* fileName) {
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);
    
    
}

// data top book*****************************************************


// =============================
// GHI DỮ LIỆU DẠNG TEXT
// =============================
void topBookWriteText(TopBook* head, const char* fileName) {
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/txt/%s", fileName);
    
    
}

// =============================
// GHI DỮ LIỆU DẠNG BIN
// =============================
void topBookWriteBin(TopBook* head, const char* fileName) {
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);
    
    
}

// =============================
// ĐỌC DỮ LIỆU DẠNG BIN
// =============================
void topBookReadBin(TopBook*& head, const char* fileName) {
    char fullPath[100];
    snprintf(fullPath, sizeof(fullPath), "../doc/outPut/bin/%s", fileName);
    
    
}   