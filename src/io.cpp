#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/io.h"

// main code below

// book
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/io.h"

#define MAX_TOPIC 100

const char* TEXT_FILE_BOOK = "doc/outPut/txt/book.txt";
const char* BIN_FILE_BOOK = "doc/outPut/bin/book.bin";
const char* TEXT_FILE_READER = "doc/outPut/txt/reader.txt";
const char* BIN_FILE_READER = "doc/outPut/bin/reader.bin";

// =============================
// GHI DỮ LIỆU DẠNG TEXT
// =============================
void bookWriteText(NodeTopic* head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "doc/outPut/txt/%s", fileName);  // Nối đường dẫn + tên file

    FILE* fp = fopen(fullPath, "w");
    if (!fp) {
        perror("Error opening text file");
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
    printf("Data saved to %s (text)\n", fullPath);
}

// =============================
// GHI DỮ LIỆU DẠNG NHỊ PHÂN
// =============================
void bookWriteBin(NodeTopic* head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "wb");
    if (!fp) {
        perror("Error opening binary file");
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

        fwrite(&bookCount, sizeof(int), 1, fp);

        // Ghi thông tin từng sách
        tempBook = topic->listBook;
        while (tempBook) {
            fwrite(&(tempBook->book), sizeof(Book), 1, fp);
            tempBook = tempBook->next;
        }

        topic = topic->next;
    }

    fclose(fp);
    printf("Data saved to %s (binary)\n", fullPath);
}

// =============================
// ĐỌC DỮ LIỆU TỪ FILE NHỊ PHÂN
// =============================
void bookReadBin(NodeTopic** head, const char* fileName)
{
    char fullPath[100];
    sprintf(fullPath, "doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");
    if (!fp) {
        perror("Error reading binary file");
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
    printf("Data loaded from %s (binary)\n", fullPath);
}


// =============================
// READER - TEXT
// =============================
void readerWriteText(Reader* head, const char* fileName) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "doc/outPut/txt/%s", fileName);

    FILE* fp = fopen(fullPath, "w");
    if (!fp) {
        perror("Không thể mở file để ghi văn bản");
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
    printf("Đã lưu người đọc vào file text thành công: %s\n", fullPath);
}

// =============================
// READER - BINARY
// =============================
void readerWriteBin(Reader* head, const char* fileName) {
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "wb");
    if (!fp) {
        perror("Không thể mở file để ghi nhị phân");
        return;
    }

    Reader* current = head;
    while (current != NULL) {
        fwrite(current, sizeof(Reader), 1, fp);
        current = current->next;
    }

    fclose(fp);
    printf("Đã lưu người đọc vào file binary thành công: %s\n", fullPath);
}

void readerReadBin(Reader*& head, const char* fileName) { // truyền tham chiếu giống C++
    char fullPath[256];
    snprintf(fullPath, sizeof(fullPath), "doc/outPut/bin/%s", fileName);

    FILE* fp = fopen(fullPath, "rb");
    if (!fp) {
        perror("Không thể mở file để đọc nhị phân");
        return;
    }

    Reader temp;
    while (fread(&temp, sizeof(Reader), 1, fp)) {
        Reader* newReader = (Reader*)malloc(sizeof(Reader));
        if (!newReader) {
            printf("Lỗi cấp phát bộ nhớ khi đọc.\n");
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
    printf("Đã đọc người đọc từ file binary thành công: %s\n", fullPath);
}
