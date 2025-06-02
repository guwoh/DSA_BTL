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

void addBook(NodeBook** listBook, Book book) {
    NodeBook* newBook = new NodeBook;
    newBook->book = book;
    newBook->next = *listBook;
    *listBook = newBook;
}

void addTopic(NodeTopic** listTopic, const char NameTopic[], Book book[], int c) {
    NodeTopic* newTopic = new NodeTopic;
    strcpy(newTopic->nameTopic, NameTopic);
    newTopic->next = NULL;
    newTopic->listBook = NULL;  

    for(int i = c - 1; i >= 0; i--) {
        addBook(&(newTopic->listBook), book[i]);
    }

    newTopic->next = *listTopic;
    *listTopic = newTopic;
}

NodeTopic* searchTopic(NodeTopic* listTopic, const char s[]);

void addNew(NodeTopic** listTopic) {
    char nameTP[100];
    int count;//so luong sach muon them vao chu de

    char id[20];//ma sach
    char name[100];//ten sach
    char author[30];//tac gia
    int year;//nam xuat ban
    int quantity;//so luong

    Book book[MAX_BOOK];
    if(*listTopic == NULL) {
        cout << "\nNhap ten chu de ma ban muon them: ";
        cin.getline(nameTP, 50);
        cout << "\nBan muon them bao nhieu sach vao chu de nay: ";
        cin >> count;
    
        for(int i = 0; i < count; i++) {
            cout << "\nNhap thong tin cua sach thu " << i + 1;
            cout << "\nNhap ma sach: ";
            cin >> id;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "Nhap ten sach: ";
            cin.getline(name, 50);

            cout << "Nhap tac gia: ";
            cin.getline(author, 50);

            cout << "Nhap nam xuat ban: ";
            cin >> year;

             cout << "Nhap so luong: ";
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
            cout << "\nBan muon them bao nhieu sach vao chu de nay: ";
            cin >> count;
            for(int i = 0; i < count; i++) {
                cout << "\nNhap thong tin cua sach thu " << i + 1;
                cout << "\nNhap ma sach: ";
                cin >> id;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "Nhap ten sach: ";
                cin.getline(name, 50);

                cout << "Nhap tac gia: ";
                cin.getline(author, 50);

                cout << "Nhap nam xuat ban: ";
                cin >> year;

                cout << "Nhap so luong: ";
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
            
            NodeTopic* ptrTP = *listTopic;
            cout << "\nDanh sach chu de hien tai: \n";
            while(ptrTP != NULL) {
                cout << "- " << ptrTP->nameTopic << "\n";
    
                ptrTP = ptrTP->next;
            }
            cout << "\nNhap ten chu ma ban muon them sach vao: ";

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while(1) {
                cin.getline(nameTP, 50);
                NodeTopic* ptrNodeTP = searchTopic(*listTopic, nameTP);
                if(ptrNodeTP == NULL) {
                    cout << "\nKhong tim thay chu de ma ban muon them sach vao. Vui long nhap lai ten chu de: ";
                    continue;
                }

                cout << "\nBan muon them bao nhieu sach vao chu de nay: ";
                cin >> count;
                for(int i = 0; i < count; i++) {
                    cout << "\nNhap thong tin cua sach thu " << i + 1;
                    cout << "\nNhap ma sach: ";
                    cin >> id;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    cout << "Nhap ten sach: ";
                    cin.getline(name, 50);

                    cout << "Nhap tac gia: ";
                    cin.getline(author, 50);

                    cout << "Nhap nam xuat ban: ";
                    cin >> year;

                    cout << "Nhap so luong: ";
                    cin >> quantity;

                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    strcpy(book[i].id, id);
                    strcpy(book[i].name, name);
                    strcpy(book[i].author, author);
                    book[i].year = year;
                    book[i].quantity = quantity;
                    addBook(&ptrNodeTP->listBook, book[i]);
                }
                return;
        }
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

NodeBook* searchByID1(NodeTopic** listTopic){
    char i[20]; //Ten chu de muon tim
    char s[100]; //Ma sach muon tim
    int k = 1; //So thu tu di kem theo chu de
    
    if(*listTopic == NULL) {
        cout << "\nDanh sach chu de dang trong. Vui long them sach de co the tim kiem!";
        return NULL;
    }
    
    NodeTopic* ptrTP = *listTopic;

    cout << "\nDanh sach chu de hien tai: \n";
    while(ptrTP != NULL) {
        cout << "- " << ptrTP->nameTopic << "\n";
    
        ptrTP = ptrTP->next;
    }
        cout << "\nNhap ten chu ma ban muon tim: ";
    
    while(1) {
        cin.getline(i, 50);
        NodeTopic* ptrNodeTP = searchTopic(*listTopic, i);

        if(ptrNodeTP == NULL) {
            cout << "\nKhong tim thay chu de ma ban muon tim. Vui long nhap lai ten chu de: ";
            continue;
        }

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
                default:
                    return NULL;
            }
        }
    }
}


void display(NodeBook* listBook) {
    if(listBook == NULL) { 
        cout << "\nDanh sach sach dang trong";
        return;
    }
    cout << "- Ma sach     : " << listBook->book.id << "\n"
         << "- Ten sach    : " << listBook->book.name << "\n"
         << "- Tac gia     : " << listBook->book.author << "\n"
         << "- Nam xuat ban: " << listBook->book.year << "\n"
         << "- So luong    : " << listBook->book.quantity << "\n";
       
}

void display2(NodeTopic* listTP) {
    if(listTP == NULL) {
        cout << "\nDanh sach chu de trong";
        return;
    }
    cout << "\nDanh sach cac chu de: ";
    while(listTP != NULL) {         
        cout << "\n  - Ten chu de: " << listTP->nameTopic << "\n";
        cout << "  - Danh sach cac cuon sach trong chu de: ";
            NodeBook* ptrbook = listTP->listBook;
            while(ptrbook != NULL) {
                cout << "\n    +Ten sach: " << ptrbook->book.name
                     << "\n     _Ma sach     : " << ptrbook->book.id
                     << "\n     _Tac gia     : " << ptrbook->book.author
                     << "\n     _Nam xuat ban: " << ptrbook->book.year
                     << "\n     _So luong    : " << ptrbook->book.quantity
                     << "\n";
                ptrbook = ptrbook->next;
            }
        cout << "\n";
        listTP = listTP->next;
    }
}

void display3(NodeBook* listBook) {
    if(listBook == NULL){
        cout << "\nDanh sach dang trong";
        return;
    } 
    NodeBook* ptrNodeB = listBook;
    while(ptrNodeB != NULL) {
        cout << "- Ma sach     : " << ptrNodeB->book.id << "\n"
         << "- Ten sach    : " << ptrNodeB->book.name << "\n"
         << "- Tac gia     : " << ptrNodeB->book.author << "\n"
         << "- Nam xuat ban: " << ptrNodeB->book.year << "\n"
         << "- So luong    : " << ptrNodeB->book.quantity << "\n";
        ptrNodeB = ptrNodeB->next;
    }
}

void editBook(NodeTopic** listTopic){
    char i[50]; //Ten chu de muon tim
    char nameOrID[100]; //Ma sach muon tim
    int k = 1; //So thu tu di kem theo chu de
    
    if(*listTopic == NULL) {
        cout << "\nDanh sach chu de dang trong. Vui long them sach!";
        return;
    }

    NodeTopic* ptrTP = *listTopic;

    cout << "\nDanh sach chu de hien tai: \n";
    while(ptrTP != NULL) {
        cout << "- " << ptrTP->nameTopic << "\n";
    
        ptrTP = ptrTP->next;
    }
    cout << "\nNhap ten chu ma ban muon sua: ";

    while(1) {
        cin.getline(i, 50);
        NodeTopic* ptrNodeTP = searchTopic(*listTopic, i);
        
        if(ptrNodeTP == NULL) {
            cout << "\nKhong tim thay chu de ma ban muon sua. Vui long nhap lai ten chu de: ";
            continue;
        }

        if(ptrNodeTP->listBook == NULL) {
            cout << "\nDanh sach sach cua chu de nay dang trong. Vui long them sach vao chu de!";
            return;
        }
        cout <<"\nSach ma ban muon sua co ma hoac ten la gi? Hay nhap ma hoac ten cua sach do: ";
        
        while(1) {
        cin.getline(nameOrID, 50); 
        NodeBook* ptrNodeB = ptrNodeTP->listBook;
        while(ptrNodeB != NULL) {
            if(strcmp(nameOrID, ptrNodeB->book.id) == 0 || strcmp(nameOrID, ptrNodeB->book.name) == 0) {
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
                        cout << "\nMa sach cu la: " << ptrNodeB->book.id;
                        cout << "\nNhap Ma sach moi: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.getline(newID, 50);
                        strcpy(ptrNodeB->book.id, newID);
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 2:
                        cout << "\nTen sach cu la: " << ptrNodeB->book.name;
                        cout << "\nNhap Ten sach moi: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.getline(newName, 50);
                        strcpy(ptrNodeB->book.name, newName);
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 3:
                        cout << "\nTac gia cu la: " << ptrNodeB->book.author;
                        cout << "\nNhap Tac gia moi: ";
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cin.getline(newAuthor, 50);
                        strcpy(ptrNodeB->book.author, newAuthor);
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 4:
                        cout << "\nNam san xuat cu la: " << ptrNodeB->book.year;
                        cout << "\nNhap Nam xuat ban moi: ";
                        cin  >> newYear;
                        ptrNodeB->book.year = newYear;
                        cout << "\nThong tin cua sach sau khi sua:\n";
                        display(ptrNodeB);
                        return;
                    case 5:
                        cout << "\nSo luong cu la: " << ptrNodeB->book.quantity;
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

void deleteBookOrTopic(NodeTopic** listTopic) {
    char nameTP[100];
    char nameAndId[100];//ten sach va ma sach de nhap
    
    if(*listTopic == NULL) {
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
            if(*listTopic == NULL) {
                cout << "\nDanh sach chu de dang trong.";
                return;
            }

            NodeTopic* ptrTP = *listTopic;

            cout << "\nDanh sach chu de hien tai: \n";
            while(ptrTP != NULL) {
                cout << "- " << ptrTP->nameTopic << "\n";
    
                ptrTP = ptrTP->next;
            }
            cout << "\nNhap ten chu ma ban muon xoa: ";

            while(1) {
                cin.getline(nameTP, 50);
                NodeTopic* ptrNodeTP = searchTopic(*listTopic, nameTP);
                if(ptrNodeTP == NULL) {
                    cout << "\nKhong tim thay chu de. Hay nhap lai ten chu de muon xoa: ";
                    continue;
                }
                if(ptrNodeTP == *listTopic) {
                    *listTopic = (*listTopic)->next;
                    delete ptrNodeTP;
                    cout << "\nDa xoa thanh cong chu de: " << nameTP;
                    cout << "\nDanh sach cac chu de hien tai: ";
                    display2(*listTopic);
                    return;
                }
                NodeTopic* prevNodeTP = *listTopic;
                while(prevNodeTP != NULL && prevNodeTP->next != ptrNodeTP) {
                   prevNodeTP = prevNodeTP->next;
                }
                prevNodeTP->next = ptrNodeTP->next;
                cout << "\nDa xoa thanh cong chu de: " << nameTP;
                delete ptrNodeTP;
                cout << "\nDanh sach cac chu de hien tai: ";
                display2(*listTopic);
                return;
            }
            break;
        }

        case 2: {
            if(*listTopic == NULL) {
                cout << "\nDanh sach chu de dang trong.";
                return;
            }

            NodeTopic* ptrTP = *listTopic;

            cout << "\nDanh sach chu de hien tai: \n";
            while(ptrTP != NULL) {
                cout << "- " << ptrTP->nameTopic << "\n";
    
                ptrTP = ptrTP->next;
            }
            cout << "\nNhap ten chu ma ban muon xoa: ";

            while(1){
                cin.getline(nameTP, 50);
                NodeTopic* ptrNodeTP = searchTopic(*listTopic, nameTP);
                if(ptrNodeTP == NULL) {
                    cout << "\nKhong tim thay chu de. Hay nhap lai ten chu de muon xoa: ";
                    continue;
                }
                if(ptrNodeTP->listBook == NULL) {
                    cout << "\nChu de dang trong. Vui long them sach vao chu de de tiep tuc!";
                    return;
                }

                cout << "\nNhap ten hoac ma sach ma ban muon xoa: ";
                
                while(1) {
                    cin.getline(nameAndId, 50);
                    NodeBook* ptr = ptrNodeTP->listBook;
                    NodeBook* prev = NULL;

                    while (ptr != NULL) {
                        if (strcmp(nameAndId, ptr->book.name) == 0 || strcmp(nameAndId, ptr->book.id) == 0) {
                            break;
                        }
                        prev = ptr;
                        ptr = ptr->next;
                    }

                    if (ptr == NULL) {
                        cout << "\nKhong tim thay sach co ma hay ten nhu vay. Vui long nhap lai: ";
                        continue;
                    }

                    if (prev == NULL) { // xoá node đầu
                        ptrNodeTP->listBook = ptr->next;
                    } else {
                        prev->next = ptr->next;
                    }

                    cout << "\nDa xoa thanh cong sach: " << ptr->book.name;
                    delete ptr;
                    cout << "\nDanh sach sach cua chu de " << nameTP << " hien tai:\n";
                    display3(ptrNodeTP->listBook);
                    return;
                }
            }
        }
    }
}

/*

int main() {
    int i;
    NodeTopic* tp;
    initTopic(&tp);

    while(1) {
        cout << "Menu:\n"
             << "  1. Them chu de va sach" 
             << "\n  2. Sua thong tin sach"
             << "\n  3. Tim kiem sach"
             << "\n  4. Xoa chu de hoac sach"
             << "\n  5. Thoat";
        cout << "\nBan muon lam gi?\n";
        cin >> i;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(i) {
            case 1: 
                addNew(&tp);
                display2(tp);
                break;
            case 2:
                editBook(&tp);
                break;
            case 3:
                searchByID1(&tp);
                break;
            case 4:
                deleteBookOrTopic(&tp);
                break;
            default:
                return 0;         
        }
        cout << " \n        ========================================================\n";
    }
}
    
*/