#ifndef IO_H
#define IO_H

#include "book.h"
#include "member.h"
#include "utils.h"

// Ghi sách (text)
void bookWriteText(NodeTopic* head, const char* fileName);

// Ghi sách (binary)
void bookWriteBin(NodeTopic* head, const char* fileName);

// Đọc sách từ file nhị phân
void bookReadBin(NodeTopic** head, const char* fileName);

// Ghi người đọc (text)
void readerWriteText(Reader* head, const char* fileName);

// Ghi người đọc (binary)
void readerWriteBin(Reader* head, const char* fileName);

// Đọc người đọc từ file nhị phân
void readerReadBin(Reader*& head, const char* fileName);


// Ghi danh sách vay mượn sách theo Text
void writeBorrowSlipText(BorrowSlip* head, const char* fileName);

// Ghi danh sách vay mượn sách theo Bin
void writeBorrowSlipBin(BorrowSlip* head, const char* fileName);

// Đọc danh sách vay mượn sách theo Bin
void readBorrowSlipBin(BorrowSlip*& head, const char* fileName);

// Ghi danh sách top độc giả và top sách theo text
void writeTopReaderText(TopReader* head, const char* fileName);
void writeTopBookText(TopBook* head, const char* fileName);

// Ghi danh sách top độc giả và top sách theo bin
void writeTopReaderBin(TopReader* head, const char* fileName);
void writeTopBookBin(TopBook* head, const char* fileName);

// Đọc danh sách top độc giả và top sách theo bin
void readTopReaderBin(TopReader*& head, const char* fileName);
void readTopBookBin(TopBook*& head, const char* fileName);


#endif
