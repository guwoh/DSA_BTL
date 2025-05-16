/**
 * @brief lưu chữ thông tin liên quan đến thành viên 
 */
#include<string.h>

void test_member();

typedef struct {
    char id;
    char name;
    char gender;
    char dob; 
    char cardIssueDate; 
    char cardExpiryDate; 
    //Reader* next;
}Reader;

void addReader();
void editReader();
void deleteReader();
void searchByName();
void searchByID();
void listReaders();
