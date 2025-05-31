#include "../include/book.h"
#include "../include/loan.h"
#include "../include/member.h"
#include "../include/utils.h"
#include "../include/io.h"
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<limits>
using namespace std;

const int MAX_BOOK = 100;

void test_book()
{
    printf("book.c is working");
}
void initTopic(NodeTopic** nb) {
    *nb = NULL;
}

void display(NodeBook* listBook); 
void display2(NodeTopic* listTP);

NodeBook* creNodeBook(char Id[], char Name[], char Author[], int Year, int Quantity) {
    NodeBook* newBook = new NodeBook;
    strcpy(newBook->book.id, Id);
    strcpy(newBook->book.name, Name);
    strcpy(newBook->book.author, Author);
    newBook->book.year     = Year;
    newBook->book.quantity = Quantity;
    newBook->next = NULL;
    return newBook;

}

void addBook(NodeBook*& listBook, Book book) {
    NodeBook* newBook = new NodeBook;
    newBook->book = book;
    newBook->next = listBook;
    listBook = newBook;
}

void addTopic(NodeTopic*& listTopic, const char NameTopic[], Book book[], int c) {
    NodeTopic* newTopic = new NodeTopic;
    strcpy(newTopic->nameTopic, NameTopic);
    newTopic->next = NULL;
    newTopic->listBook = NULL;  
    for(int i = c - 1; i >= 0; i--) {
        addBook(newTopic->listBook, book[i]);
    }

    newTopic->next = listTopic;
    listTopic = newTopic;
}

NodeTopic* searchTopic(NodeTopic* listTopic, const char s[]);

void addNew(NodeTopic*& listTopic) {
    char nameTP[100];
    int count;//so luong sach muon them vao chu de

    char id[20];//ma sach
    char name[100];//ten sach
    char author[30];//tac gia
    int year;//nam xuat ban
    int quantity;//so luong

    Book book[MAX_BOOK];
    if(listTopic == NULL) {
        cout << "\nNhap ten chu de ma ban muon them: ";
        cin.getline(nameTP, 50);
        cout << "\nBan muon them bao nhieu sach vao chu de nay?\n";
        cin >> count;
    
        for(int i = 0; i < count; i++) {
            cout << "\nNhap thong tin cua sach thu " << i + 1;
            cout << "\nNhap ma sach: ";
            cin >> id;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "\nNhap ten sach: ";
            cin.getline(name, 50);

            cout << "\nNhap tac gia: ";
            cin.getline(author, 50);

            cout << "\nNhap nam xuat ban: ";
            cin >> year;

             cout << "\nNhap so luong: ";
            cin >> quantity;

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            strcpy(book[i].id, id);
            strcpy(book[i].name, name);
            strcpy(book[i].author, author);
            book[i].year = year;
            book[i].quantity = quantity;
        }
        addTopic(listTopic, nameTP, book, count);
        return;
    }

    cout << "\nBan muon:";
    cout << "\n1. Them chu de moi";
    cout << "\n2. Them sach vao chu de da co\n";
    int c;
    cin >> c;
    switch(c) {
        case 1:
            cout << "\nNhap ten chu de ma ban muon them: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(nameTP, 50);
            cout << "\nBan muon them bao nhieu sach vao chu de nay?\n";
            cin >> count;
            for(int i = 0; i < count; i++) {
                cout << "\nNhap thong tin cua sach thu " << i + 1;
                cout << "\nNhap ma sach: ";
                cin >> id;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "\nNhap ten sach: ";
                cin.getline(name, 50);

                cout << "\nNhap tac gia: ";
                cin.getline(author, 50);

                cout << "\nNhap nam xuat ban: ";
                cin >> year;

                cout << "\nNhap so luong: ";
                cin >> quantity;

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                strcpy(book[i].id, id);
                strcpy(book[i].name, name);
                strcpy(book[i].author, author);
                book[i].year = year;
                book[i].quantity = quantity;
            }
            addTopic(listTopic, nameTP, book, count);
            return;
        case 2:
            int k = 1;
            cout << "\nNhap ten chu ma ban muon them sach vao: ";
            NodeTopic* ptrTP = listTopic;
            while(ptrTP != NULL) {
                cout << k << ". " << ptrTP->nameTopic << "\n";
                k++;
                ptrTP = ptrTP->next;
            }
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(nameTP, 50);
            NodeTopic* ptrNodeTP = searchTopic(listTopic, nameTP);
            cout << "\nBan muon them bao nhieu sach vao chu de nay?\n";
            cin >> count;
            for(int i = 0; i < count; i++) {
                cout << "\nNhap thong tin cua sach thu " << i + 1;
                cout << "\nNhap ma sach: ";
                cin >> id;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "\nNhap ten sach: ";
                cin.getline(name, 50);

                cout << "\nNhap tac gia: ";
                cin.getline(author, 50);

                cout << "\nNhap nam xuat ban: ";
                cin >> year;

                cout << "\nNhap so luong: ";
                cin >> quantity;

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                strcpy(book[i].id, id);
                strcpy(book[i].name, name);
                strcpy(book[i].author, author);
                book[i].year = year;
                book[i].quantity = quantity;
                addBook(ptrNodeTP->listBook, book[i]);
            }
            return;

    }
}

NodeTopic* searchTopic(NodeTopic* listTopic, const char s[]) {
    NodeTopic* ptrNodeTP = listTopic;
    while(ptrNodeTP != NULL) {
        if(strcmp(s, ptrNodeTP->nameTopic) == 0) {
            return ptrNodeTP;
        }
        ptrNodeTP = ptrNodeTP->next;
    }
    return NULL;
}
void display(NodeBook* listBook); 

NodeBook* searchByID1(NodeTopic*& listTopic){
    char i[20]; //Ten chu de muon tim
    char s[100]; //Ma sach muon tim
    int k = 1; //So thu tu di kem theo chu de
    
    if(listTopic == NULL) {
        cout << "\nDanh sach chu de dang trong. Vui long them sach de co the tim kiem!";
        return NULL;
    }
    cout << "\nBan muon tim sach cua chu de nao?\n";
    NodeTopic* ptrNodeTP = listTopic;

    while(ptrNodeTP != NULL) {
        cout << k <<". " << ptrNodeTP->nameTopic << "\n";
        k++;
        ptrNodeTP = ptrNodeTP->next;    
    }
    
    while(1) {
        cin.getline(i, 50);
        NodeTopic* ptrNodeTP = searchTopic(listTopic, i);
        if(ptrNodeTP->listBook == NULL) {
            cout << "\nDanh sach sach cua chu de nay dang trong. Vui long them sach vao chu de de co the tim kiem!";
            return NULL;
        }
        cout <<"\nNhap ten sach hoac ma sach ban muon tim: ";
        
        while(1) {
            cin.getline(s, 50); 
            NodeBook* ptrNodeB = ptrNodeTP->listBook;
            while(ptrNodeB != NULL) {
                if(strcmp(s, ptrNodeB->book.id) == 0 || strcmp(s, ptrNodeB->book.name) == 0) {
                    display(ptrNodeB);
                    return ptrNodeB;
                }
                ptrNodeB = ptrNodeB->next;
            }
            cout << "\nTen sach hoac Ma sach ban nhap khong dung hoac khong co sach nao trong thu vien co Ten hay Ma nhu vay. \n";
            cout << "Ban muon: ";
            cout << "\n1. Tiep tuc tim";
            cout << "\n2. Thoat\n";
            int m;
            cin >> m;
            switch(m) {
                case 1: 
                    cout << "\nNhap lai Ten hoac Ma sach ban muon tim: ";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                case 2:
                    return NULL;
            }
        }
        cout << "Chu de ban chon khong dung. Vui long chon lai dung chu de!\n";
        cout << "Ban muon: ";
            cout << "\n1. Tiep tuc tim";
            cout << "\n2. Thoat\n";
            int m;
            cin >> m;
            switch(m) {
                case 1: 
                    cout << "\nNhap lai ten chu de ban muon tim: ";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                case 2:
                    return NULL;
            }
    }
}


void display(NodeBook* listBook) {
    if(listBook == NULL) { 
        cout << "\nDanh sach sach dang trong";
        return;
    }
    cout << "・Ma sach     : " << listBook->book.id << "\n"
         << "・Ten sach    : " << listBook->book.name << "\n"
         << "・Tac gia     : " << listBook->book.author << "\n"
         << "・Nam xuat ban: " << listBook->book.year << "\n"
         << "・So luong    : " << listBook->book.quantity << "\n";
       
}

void display2(NodeTopic* listTP) {
    if(listTP == NULL) {
        cout << "\nDanh sach chu de trong";
        return;
    }
    cout << "\nDanh sach cac chu de: ";
    while(listTP != NULL) {         
        cout << "\n  -Ten chu de: " << listTP->nameTopic << "\n";
        cout << "  -Danh sach cac cuon sach trong chu de: ";
            NodeBook* ptrbook = listTP->listBook;
            while(ptrbook != NULL) {
                cout << "\n    +Ten sach: " << ptrbook->book.name
                     << "\n     ・Ma sach     : " << ptrbook->book.id
                     << "\n     ・Tac gia     : " << ptrbook->book.author
                     << "\n     ・Nam xuat ban: " << ptrbook->book.year
                     << "\n     ・So luong    : " << ptrbook->book.quantity
                     << "\n";
                ptrbook = ptrbook->next;
            }
        cout << "\n";
        listTP = listTP->next;
    }
}

void display3(NodeBook* listBook) {
    if(listBook == NULL) return;
    NodeBook* ptrNodeB = listBook;
    while(ptrNodeB != NULL) {
        cout << "・Ma sach     : " << ptrNodeB->book.id << "\n"
         << "・Ten sach    : " << ptrNodeB->book.name << "\n"
         << "・Tac gia     : " << ptrNodeB->book.author << "\n"
         << "・Nam xuat ban: " << ptrNodeB->book.year << "\n"
         << "・So luong    : " << ptrNodeB->book.quantity << "\n";
        ptrNodeB = ptrNodeB->next;
    }
}

void editBook(NodeTopic*& listTopic){
    char i[50]; //Ten chu de muon tim
    char s[100]; //Ma sach muon tim
    int k = 1; //So thu tu di kem theo chu de
    
    if(listTopic == NULL) {
        cout << "\nDanh sach chu de dang trong. Vui long them sach!";
        return;
    }
    cout << "\nBan muon sua sach cua chu de nao?\n";
    NodeTopic* ptrNodeTP1 = listTopic;

    while(ptrNodeTP1 != NULL) {
        cout << k <<". " << ptrNodeTP1->nameTopic << "\n";
        k++;
        ptrNodeTP1 = ptrNodeTP1->next;    
    }

    while(1) {
        cin.getline(i, 50);
        NodeTopic* ptrNodeTP = searchTopic(listTopic, i);
        if(ptrNodeTP->listBook == NULL) {
            cout << "\nDanh sach sach cua chu de nay dang trong. Vui long them sach vao chu de!";
            return;
        }
        cout <<"\nSach ma ban muon sua co ma la gi? Hay nhap ma cua sach do: ";
        
        while(1) {
        cin.getline(s, 50); 
        NodeBook* ptrNodeB = ptrNodeTP->listBook;
        while(ptrNodeB != NULL) {
            if(strcmp(s, ptrNodeB->book.id) == 0) {
                int h; //chon muc muon sua thong tin
                char newID[20];
                char newName[50];
                char newAuthor[50];
                int  newYear;
                int newQuantity;
                cout << "\nBan muon sua thong tin nao cua sach?";
                cout << "\n1. Ma sach"
                     << "\n2. Ten sach"
                     << "\n3. Tac gia"
                     << "\n4. Nam xuat ban"
                     << "\n5. So luong sach"
                     << "\n(Vui long chon '1' neu ban muon chon Ma sach, chon '2' neu ban muon chon Ten sach)\n";
                cin >> h;
                switch(h) {
                    case 1:
                        cout << "\nNhap Ma sach moi: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.getline(newID, 50);
                        strcpy(ptrNodeB->book.id, newID);
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 2:
                        cout << "\nNhap Ten sach moi: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.getline(newName, 50);
                        strcpy(ptrNodeB->book.name, newName);
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 3:
                        cout << "\nNhap Tac gia moi: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.getline(newAuthor, 50);
                        strcpy(ptrNodeB->book.author, newAuthor);
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 4:
                        cout << "\nNhap Nam xuat ban moi: ";
                        cin  >> newYear;
                        ptrNodeB->book.year = newYear;
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 5:
                        cout << "\nNhap So luong moi: ";
                        cin  >> newQuantity;
                        ptrNodeB->book.quantity = newQuantity;
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                }    
            }
            ptrNodeB = ptrNodeB->next;
        }
        cout << "\nMa sach ban nhap khong dung hoac khong co sach nao trong chu de nay co ma nhu vay.\n";
        cout << "Ban muon: ";
            cout << "\n1. Tiep tuc tim sach de chinh sua";
            cout << "\n2. Thoat\n";
            int m;
            cin >> m;
            switch(m) {
                case 1: 
                    cout << "\nNhap lai ma sach ban muon tim de chinh sua thong tin: ";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                case 2:
                    return;
            }
        }
        cout << "Chu de ban chon khong dung. Vui long chon lai dung chu de!\n";
    }
}

void deleteBookOrTopic(NodeTopic*& listTopic) {
    char nameTP[100];
    char nameAndId[100];//ten sach va ma sach de nhap
    
    if(listTopic == NULL) {
        cout << "\nDanh sach chu de dang trong.";
        return;
    }

    int i;
    cout << "\nBan muon";
    cout << "\n1. Xoa chu de";
    cout << "\n2. Xoa sach\n";
    cin >> i;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch(i) {
        case 1: {
            if(listTopic == NULL) {
                cout << "\nDanh sach chu de dang trong.";
                return;
            }
            cout << "\nBan muon xoa chu de nao?\n";

            NodeTopic* ptrNodeTP1 = listTopic;
            int k = 1;
            while(ptrNodeTP1 != NULL) {
                cout << k <<". " << ptrNodeTP1->nameTopic << "\n";
                k++;
                ptrNodeTP1 = ptrNodeTP1->next;    
            }
            cout << "\nHay nhap ten chu de ma ban muon xoa: ";
            while(1) {
                cin.getline(nameTP, 50);
                NodeTopic* ptrNodeTP = searchTopic(listTopic, nameTP);
                if(ptrNodeTP == NULL) {
                    cout << "\nKhong tim thay chu de. Hay nhap lai ten chu de muon xoa: ";
                    continue;
                }
                if(ptrNodeTP == listTopic) {
                    listTopic = listTopic->next;
                    delete ptrNodeTP;
                    cout << "\nDa xoa thanh cong chu de: " << nameTP;
                    cout << "\nDanh sach cac chu de hien tai: ";
                    display2(listTopic);
                    return;
                }
                NodeTopic* prevNodeTP = listTopic;
                while(prevNodeTP != NULL && prevNodeTP->next != ptrNodeTP) {
                   prevNodeTP = prevNodeTP->next;
                }
                prevNodeTP->next = ptrNodeTP->next;
                cout << "\nDa xoa thanh cong chu de: " << nameTP;
                delete ptrNodeTP;
                cout << "\nDanh sach cac chu de hien tai: ";
                display2(listTopic);
                return;
            }
            break;
        }

        case 2: {
            if(listTopic == NULL) {
                cout << "\nDanh sach chu de dang trong.";
                return;
            }
            cout << "\nBan muon xoa chu de nao?\n";

            NodeTopic* ptrNodeTP1 = listTopic;
            int k = 1;
            while(ptrNodeTP1 != NULL) {
                cout << k <<". " << ptrNodeTP1->nameTopic << "\n";
                k++;
                ptrNodeTP1 = ptrNodeTP1->next;    
            }
            cout << "\nHay nhap ten chu de ma ban muon xoa: ";
            while(1){
                cin.getline(nameTP, 50);
                NodeTopic* ptrNodeTP = searchTopic(listTopic, nameTP);
                if(ptrNodeTP == NULL) {
                    cout << "\nKhong tim thay chu de. Hay nhap lai ten chu de muon xoa: ";
                    continue;
                }
                if(ptrNodeTP->listBook == NULL) {
                    cout << "\nChu de dang trong. Vui long them sach vao chu de de tiep tuc!";
                    return;
                }
                cout << "\nNhap ten hoac ma sach ma ban muon xoa: ";
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while(1) {
                    bool done = false;
                    cin.getline(nameAndId, 50);
                    NodeBook* ptrNodeB = ptrNodeTP->listBook;
                    NodeBook* ptrNodeBookCurrent = new NodeBook;
                    while(ptrNodeB != NULL ) {
                        if(strcmp(nameAndId, ptrNodeB->book.name) == 0 || strcmp(nameAndId, ptrNodeB->book.id) == 0) {
                            ptrNodeBookCurrent = ptrNodeB; 
                            done = true;
                        }
                        ptrNodeB = ptrNodeB->next;
                    }
                    if(done == false) {
                        cout << "\nKhong tim thay sach co ma hay ten nhu vay. Vui long nhap lai ma hoac ten sach ma ban muon xoa: ";
                        continue;
                    }

                    NodeBook* prevB = ptrNodeTP->listBook;
                    while(prevB != NULL && prevB->next != ptrNodeBookCurrent){
                        prevB = prevB->next;
                    }
                    prevB->next = ptrNodeBookCurrent->next;
                    cout << "\nDa xoa thanh cong chu de: " << ptrNodeBookCurrent->book.name;
                    delete ptrNodeBookCurrent;
                    cout << "\nDanh sach sach cua chu de " <<  nameTP << " hien tai:\n";
                    display3(ptrNodeTP->listBook);
                    return;
                }
                
            }
        }
    }
}