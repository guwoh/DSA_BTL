#ifndef MEMBER_H
#define MEMBER_H


#include<string.h>


#define MAX_NAME_LEN 50
#define MAX_DATE_LEN 11
#define MAX_ID_LEN 20

struct Reader{
    char id[MAX_ID_LEN];
    char name[MAX_NAME_LEN];
    char gender[10];
    char dob[MAX_DATE_LEN];
    char cardIssueDate[MAX_DATE_LEN];
    char cardExpiryDate[MAX_DATE_LEN];
    struct Reader* next;
};

void addReader(Reader** head);
void editReader(Reader* head);
void deleteReader(Reader** head);
void searchByName(Reader* head);
void searchByID(Reader* head);
void listReaders(Reader* head);

#endif
