// #ifndef IO_H
// #define IO_H

// #include "book.h"
// #include "member.h"

// // book.h
// // all this  function below use for book

// void bookWriteText(); // write text file for human
// void bookWriteBin(); // write bin file for machine
// void bookReadBin(); // machine read bin flie to recovery data of linked list Topic Book



// // member.h
// // all this function below use for reader

// void readerWriteText(); // write text file for human
// void readerWriteBin(); // write bin file for machine
// void readerReadBin(); // machine read bin flie to recovery data of linked list Reader 

// #endif
#ifndef IO_H
#define IO_H

#include "book.h"
#include "member.h"

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

#endif
