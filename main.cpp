/*
- stworzenie menu;
- funkcja weryfikujaca wprowadzony char;
- funkcja dodajaca kontakt, utworzenie pliku.txt.;
- funkcja wczytujaca plik txt do vektora;-
- f. wyswietlajaca wszystkie kontakty;
- f. wyszukujaca po imieniu;
- f. wyszukujaca po nazwisku;
- submenu do edycji kontaktu;
- f. edycji kontaktu;
- f usowania kontaktu z potwierdzeniem.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <vector>

using namespace std;

struct ContactInfo{
    int id;
    string name, surname, tel, address, email;
};

void menu();
int addNewContact(ContactInfo, int contactsNr);
vector <string> abstractWordFromText();
void displayAllContacts(vector<string>&);
int convertIdtoNr(vector<string>&);
void findSurname(vector<string>&);
void findName(vector<string>&);
void removeContact(vector<string>&);
void editContact(vector<string>&);
int verifyChar();
string editTxt();
void exportVectorToFile(vector<string>& contacts);

int main()
{
    ContactInfo contact;
    vector<string>contacts;
    string idTxt;
    int choice, contactsNr=0;
    contacts=abstractWordFromText();
    contactsNr=convertIdtoNr(contacts);

    while(true){
        menu();
        choice=verifyChar();

         switch(choice){
            case 1:{
                    contactsNr=addNewContact(contact,contactsNr);
                    contacts=abstractWordFromText();
                break;
            }case 2:{
                 if(contactsNr==0){
                    cout<<"Address Book empty !!!";
                    Sleep(2000);
                }else findName(contacts);
                break;
            }case 3:{
                    if(contactsNr==0){
                    cout<<"Address Book empty !!!";
                    Sleep(2000);
                }else findSurname(contacts);
                break;
            }case 4:{
                if(contactsNr==0){
                    cout<<"Address Book empty !!!";
                    Sleep(2000);
                }else displayAllContacts(contacts);
                break;
            }case 5:{
                if(contactsNr==0){
                    cout<<"Address Book empty !!!";
                    Sleep(2000);
                }else removeContact(contacts);
                break;
            }case 6:{
                if(contactsNr==0){
                    cout<<"Address Book empty !!!";
                    Sleep(2000);
                }else editContact(contacts);
                break;
            }case 0: exit(0);break;
            default: cout<<"Sorry wrong choice. Try again(0-6)"; Sleep(2000);
         }
    }
    return 0;
}
void menu(){
    system("cls");
        cout << "\t\tMENU" << endl;
        cout << "====================================" << endl;
        cout << "1. Add new person." << endl;
        cout << "2. Find person by name." << endl;
        cout << "3. Find person by surname." << endl;
        cout << "4. Display all contacts." << endl;
        cout << "5. Remove contact." << endl;
        cout << "6. Edit contact." << endl;
        cout << "0. Exit." << endl;
        cout << "====================================" << endl;
        cout << "Your choice: ";
}

int verifyChar(){
    string choice; int digit;

    while(cin>>choice){
    if(choice.length()>1) return 13;
        else{
            digit=choice[0]-48;
            if(digit>=0&&digit<=9) return digit;
            else return 13;
        }
    }
}

string editTxt(){
    string txt;
    cin.sync();
    getline(cin, txt);
    transform(txt.begin(), txt.end(),txt.begin(),::toupper);
    return txt;
}

int addNewContact(ContactInfo, int contactsNr){
    ContactInfo contact;
        contact.id=contactsNr+1;
        cout << "Enter Name: ";
        contact.name = editTxt();
        cout << "Enter Surname: ";
        contact.surname = editTxt();
        cout << "Phone Nr: ";
        contact.tel = editTxt();
        cout << "Email: ";
        contact.email = editTxt();
        cout << "Address: ";
        contact.address = editTxt();

    fstream file;
    file.open("ContactsBook.txt",ios::out | ios::app);

    if (file.good() == true){
        file<<contact.id<<"|"<<contact.name<<"|"<<contact.surname<<"|"<<contact.tel
            <<"|"<<contact.email<<"|"<<contact.address <<"|"<< endl;
        file.close();
    }else{
        cout << "ERROR: Contact not saved." << endl;
        system("pause");
    }
    cout << endl << "New contact added." << endl; system("pause");
    return contactsNr+1;

}

vector <string> abstractWordFromText(){
    vector <string> txtWords;
    string txt;
    string singleWord;
    fstream file;
    file.open("ContactsBook.txt", ios::in);
    if(file.good()==true){
        while(getline(file,txt)){
            for (int pozycjaWyrazu = 0; pozycjaWyrazu < txt.size(); pozycjaWyrazu++){
                if (txt[pozycjaWyrazu] !='|')
                {
                    singleWord += txt[pozycjaWyrazu];
                }
                else
                {
                    txtWords.push_back(singleWord);
                    singleWord = "";
                }
            }
        }
        file.close();
    }
            return txtWords;
}

void displayAllContacts(vector<string>& contacts){

    for(int i=0; i<contacts.size(); i=i+6){
        cout<<"\nid: "<<contacts[i]<<endl;
        cout<<"\tName: "<<contacts[i+1]<<"\t"<<"Surname: "<<contacts[i+2]<<endl;
        cout<<"\tPhone: "<<contacts[i+3]<<endl;
        cout<<"\tEmail: "<<contacts[i+4]<<endl;
        cout<<"\tAddress: "<<contacts[i+5]<<endl;
        cout<<"    =================================="<<endl;
    }
    getchar();getchar();
}

void findSurname(vector<string>& contacts){
    string tmpSurname;
    int tmp_nr=0, vectorSize;
    cout<<"Enter surname: ";
    tmpSurname=editTxt();
    vectorSize=contacts.size();
     for(int i=2; i<vectorSize; i=i+6){
        if(tmpSurname==contacts[i]){
            cout<<"\nid: "<<contacts[i-2]<<endl;
            cout<<"\tName: "<<contacts[i-1]<<"\tSurname: "<<contacts[i]<<endl;
            cout<<"\tPhone: "<<contacts[i+1]<<endl;
            cout<<"\tEmail: "<<contacts[i+2]<<endl;
            cout<<"\tAddress: "<<contacts[i+3]<<endl;
            cout<<"   =======================================\n";
            tmp_nr++;
        }
    }
    if(tmp_nr==0) cout<<"No contact has been found.";
        tmp_nr=0;
    getchar();
}

void findName(vector<string>& contacts){
    string tmpName;
    int tmp_nr=0, vectorSize;
    cout<<"Enter Name: ";
    tmpName=editTxt();
    vectorSize=contacts.size();
     for(int i=1; i<vectorSize; i=i+6){
        if(tmpName==contacts[i]){
            cout<<"\nid: "<<contacts[i-1]<<endl;
            cout<<"\tName: "<<contacts[i]<<"\tSurname: "<<contacts[i+1]<<endl;
            cout<<"\tPhone: "<<contacts[i+2]<<endl;
            cout<<"\tEmail: "<<contacts[i+3]<<endl;
            cout<<"\tAddress: "<<contacts[i+4]<<endl;
            cout<<"   =======================================\n";
            tmp_nr++;
        }
    }
    if(tmp_nr==0) cout<<"No contact has been found.";
        tmp_nr=0;
    getchar();
}

int convertIdtoNr(vector<string>& contacts){
    int nr, vectorSize; string idTxt;
    vectorSize=contacts.size();
    if(vectorSize<5) nr=0;
    else{nr=vectorSize-6;
        idTxt=contacts[nr];
        nr=atoi(idTxt.c_str());
        }
    return nr;
}

void editContact(vector<string>& contacts){
    string tmpId,txt;
    int choice;
    bool found=false;
    cout<<"Enter contact Id you wish to edit: "; cin>>tmpId;

       for(int i=0; i<contacts.size(); i=i+6){
         if(tmpId==contacts[i]){
                found=true;
                cout<<"\nYou are going to edit contact with id: "<<contacts[i]<<endl;
                cout<<"Name: "<<contacts[i+1]<<" Surname: "<<contacts[i+2]<<endl<<endl;
                cout<<"Which data are you going to change?"<<endl;
                cout<<"1. Name."<<endl;
                cout<<"2. Surname."<<endl;
                cout<<"3. Phone."<<endl;
                cout<<"4. Email."<<endl;
                cout<<"5. Address."<<endl;
                cout<<"0. Return to main Menu."<<endl;
                cout<<"================="<<endl;
                cout<<"Choice: ";
                choice=verifyChar();
                switch(choice){
                    case 1:{
                        cout<<"Tape in new Name: ";
                        txt=editTxt();
                        contacts[i+1]=txt;
                        cout<<"Changes saved!!!"<<endl;
                        exportVectorToFile(contacts);
                        break;
                    }case 2:{
                        cout<<"Tape in new Surname: ";
                        txt=editTxt();
                        contacts[i+2]=txt;
                        cout<<"Changes saved!!!"<<endl;
                        exportVectorToFile(contacts);
                        break;
                    }case 3:{
                        cout<<"Tape in new Phone number: ";
                        txt=editTxt();
                        contacts[i+3]=txt;
                        cout<<"Changes saved!!!"<<endl;
                        exportVectorToFile(contacts);
                        break;
                    }case 4:{
                        cout<<"Tape in new Email: ";
                        txt=editTxt();
                        contacts[i+4]=txt;
                        cout<<"Changes saved!!!"<<endl;
                        exportVectorToFile(contacts);
                        break;
                    }case 5:{
                        cout<<"Tape in new Address: ";
                        txt=editTxt();
                        contacts[i+5]=txt;
                        cout<<"Changes saved!!!"<<endl;
                        exportVectorToFile(contacts);
                        break;
                    }case 0: menu();break;
                    default: cout<<"Sorry wrong choice. Try again(0-5)"<<endl;Sleep(2000);
                }
            }
        }
        if (found==false){
        cout<<"Sorry contact with id: "<<tmpId<<" not found."<<endl;
         Sleep(2000);
       }
}

void exportVectorToFile(vector<string>& contacts){
    fstream file;
    file.open("ContactsBook.txt",ios::out);

    if (file.good() == true){
        for(int i=0; i<contacts.size(); i=i+6){
        file<<contacts[i]<<"|"<<contacts[i+1]<<"|"<<contacts[i+2]<<"|"<<contacts[i+3]
            <<"|"<<contacts[i+4]<<"|"<<contacts[i+5]<<"|"<< endl;
        }
        file.close();
    }else{
        cout << "ERROR: Contact not saved." << endl;
        system("pause");
    }
}
void removeContact(vector<string>& contacts){
    string tmpId, txt;
    string ver;
    bool found=false;
    cout<<"Enter contact Id you wish to remove: "; cin>>tmpId;

        for(int i=0; i<contacts.size();i=i+6){
         if(tmpId==contacts[i]){
            found=true;
            cout<<"You are going to remove contact id: "<<contacts[i]<<endl;
            cout<<" Name: "<<contacts[i+1]<<" Surname: "<<contacts[i+2]<<endl;
            cout<<"\nPlease confirm: enter Y for yes or N for no: ";
            cin>>ver;
            transform(ver.begin(), ver.end(),ver.begin(),::toupper);
            if(ver=="Y"){
                cout<<"Contact removed"<<endl;
               contacts.erase (contacts.begin()+i,contacts.begin()+i+6);
                exportVectorToFile(contacts);
                Sleep(1500);
            }else if(ver=="N"){
                cout<<"You rejected to remove this contact."<<endl;
                Sleep(1500);
                menu();
            }else {
                cout<<"Sorry wrong choice."<<endl;
                Sleep(1500);
                menu();
            }
         }

       }
       if (found==false){
        cout<<"Sorry contact with id: "<<tmpId<<" not found."<<endl;
         Sleep(2000);
       }
}
