#ifndef IO_H
#define IO_H

#include "book.h" // struct book
#include "member.h" // struct reader
#include "loan.h" // struct borrow slip

// BOOK
// Ghi sách (text)
void bookWriteText(NodeTopic* head, const char* fileName);

// Ghi sách (binary)
void bookWriteBin(NodeTopic* head, const char* fileName);

// Đọc sách từ file nhị phân
void bookReadBin(NodeTopic** head, const char* fileName);

//** */
// READER
// Ghi người đọc (text)
void readerWriteText(Reader* head, const char* fileName);

// Ghi người đọc (binary)
void readerWriteBin(Reader* head, const char* fileName);

// Đọc người đọc từ file nhị phân
void readerReadBin(Reader*& head, const char* fileName);

//** */
// BORROW SLIP
// Ghi danh sách vay mượn sách theo Text
void borrowSlipWriteText(BorrowSlip* head, const char* fileName);

// Ghi danh sách vay mượn sách theo Bin
void borrowSlipWriteBin(BorrowSlip* head, const char* fileName);

// Đọc danh sách vay mượn sách theo Bin
void borrowSlipReadBin(BorrowSlip** head, const char* fileName);



#endif
