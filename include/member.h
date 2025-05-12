#include<string.h>

struct Reader {
    string id;
    string name;
    string gender;
    string dob; 
    string cardIssueDate; 
    string cardExpiryDate; 
    Reader* next;
};

void addReader();
void editReader();
void deleteReader();
void searchByName();
void searchByID();
void listReaders();
