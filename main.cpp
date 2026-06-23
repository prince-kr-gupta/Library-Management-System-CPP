#include<iostream>
#include<fstream>
using namespace std;

class Library{
    protected:

    string id,name,author,search, quantity;
    fstream Bookfile;

    public:

    void displayBook(){

        Bookfile.open("BookData.txt",ios::in);
        
        if(!Bookfile){
            cout<<"---No Books Found---!"<<endl;
            return;
        }

        cout<<"Book Id \t\tBook Name\t\tAuthor's name\t\tQuantity"<<endl;


        while(getline(Bookfile,id,'|')){
            getline(Bookfile,name,'|');
            getline(Bookfile,author,'|');
            getline(Bookfile,quantity,'\n');

          
           cout<<id<<" \t\t\t "<<name<<" \t\t\t "<<author<<" \t\t\t "<<quantity<<endl;

        }
        Bookfile.close();


    }
};

class Admin : public Library{
    private:
    string adminUsername = "admin";
    string adminPassword = "admin@123";

    public:

    bool adminLogin() {
        string username,password;
        cout<<"---Admin Login---"<<endl;
        cout<<"Enter username : ";
        cin>>username;
        cin.ignore();

        cout<<"Enter password : ";
        cin>>password;
        cin.ignore();

        if(adminUsername == username && adminPassword == password){
            cout<<" Login Successful---!"<<endl;
            return true;
        }
        else {
            cout<<" Wrong Password---!"<<endl;
            return false;
        }

    }

        void addBook(){

        cout<<" Enter Book ID : ";
        getline(cin,id);
        cout<<" Enter the Name of a Book : ";
        getline(cin,name);
        cout<<" Enter the Name of the Author : ";
        getline(cin,author);
        cout<<" Enter quantity of a book : ";
        getline(cin,quantity);

        Bookfile.open("BookData.txt",ios::out | ios::app);
        Bookfile<<id<<"|"<<name<<"|"<<author<<"|"<<quantity<<endl;
        Bookfile.close();

        cout<<" Book Added Successfully---! "<<endl;

    }
    void removeBook(){

        displayBook();
        cout<<"Enter Book Id to Remove: ";  
        getline(cin,search);

        Bookfile.open("BookData.txt",ios::in);
        string allData="";
        bool found=false;

        while(getline(Bookfile,id,'|')){
            getline(Bookfile,name,'|');
            getline(Bookfile,author,'|');
            getline(Bookfile,quantity,'\n');

            if(search == id){
               found = true;
                cout<<id<<" \t\t\t "<<name<<" \t\t\t "<<author<< "\t\t\t "<<quantity<<endl;
                cout<<" Book Removed Successfully---! "<<endl;

            }
            else {
                allData += id + "|" + name + "|" + author + "|" + quantity + "\n";
            }

        }
        Bookfile.close();


        if(found){
            Bookfile.open("BookData.txt", ios::out);
            Bookfile<<allData;
            Bookfile.close();
        }
        else{
            cout<<" Book Id "<<search<<" Not Found"<<endl;
        }

    }


    void updateBook(){
        displayBook();

        cout<<"---Enter Book ID to Update---"<<endl;
        getline(cin,search);

        Bookfile.open("BookData.txt",ios::in);
        string allData="";
        bool found = false;

        while(getline(Bookfile,id,'|')){
            getline(Bookfile,name,'|');
            getline(Bookfile,author,'|');
            getline(Bookfile,quantity,'\n');

            if(search==id){
                found = true;

                cout<<"\n---Current Book Details---\n";
                cout<<"ID : "<<id<<endl;
                cout<<"Name : "<<name<<endl;
                cout<<"Author's Name : "<<author<<endl;


                cout<<" Enter New Book Name : ";
                getline(cin,name);
                cout<<"Enter New Author Name : ";
                getline(cin,author);
                cout<<" Enter Book Quantity : ";
                getline(cin,quantity);


                  allData += id + "|" + name + "|" + author + "|" + quantity + "\n";
                cout<<"Book Updated Successfully---!"<<endl;

            }
            else {
                  allData += id + "|" + name + "|" + author + "|" + quantity + "\n";

            }

        }
        Bookfile.close();

        if(found) {
            Bookfile.open("BookData.txt",ios::out);
            Bookfile<<allData;
            Bookfile.close();

        }
        else{
            cout<<"Book ID "<<search<<" Not Found---!"<<endl;
        }

    }

    void adminPanel() {
        if(!adminLogin()) return;

        int choice;
        do{
            cout<<"\n=============================\n";
            cout<<"          ADMIN PANEL           "<<endl;
            cout<<"================================"<<endl;
            cout<<"1. Display All Books"<<endl;
            cout<<"2. Add Book"<<endl;
            cout<<"3. Remove Book"<<endl;
            cout<<"4. Update Book"<<endl;
            cout<<"0. Exit"<<endl;
            
            cout<<"\n-----------------------\n";
            cout<<"Enter Choice : ";
            cin>>choice;
            cin.ignore();

            switch(choice){
                case 1:
                displayBook();
                break;

                case 2:
                addBook();
                break;

                case 3:
                removeBook();
                break;

                case 4:
                updateBook();
                break;
                case 0:
                cout<<"Exit";
                break;

                default:
                cout<<"Invalid Choice---!"<<endl;

            }
        }
            while(choice!=0);
        }
    

};

class Student : public Library{
    private:
    string studentId;

    public:

    bool studentLogin() {
        
        cout<<"\n---Student login---\n";
        cout<<"Enter the Student ID : ";
        getline(cin,studentId);
        return true;
        
    }

    void borrowBook(){
        displayBook();
        cout<<" Enter Book ID to Borrow : ";
        getline(cin,search);

        Bookfile.open("BookData.txt",ios::in);
            string allData="";
            bool found = false;

            
        while (getline(Bookfile, id, '|')) {
            getline(Bookfile, name, '|');
            getline(Bookfile, author, '|');
            getline(Bookfile, quantity, '\n');

            if(search == id){
                found = true;
                int qty = stoi(quantity);
                if(qty>0){
                qty--;
                quantity = to_string(qty);
                }
                cout<<"Book  "<<name<<"  Borrowed successfully"<<endl;

                fstream borrowfile;
                borrowfile.open("BorrowData.txt",ios::out | ios::app);
                borrowfile<<studentId<<"|"<<id<<"|"<<name<<endl;
                borrowfile.close();
            }
            
            allData += id + "|" + name + "|" + author + "|" + quantity + "\n";


        }
        Bookfile.close();
        
        if(found){
            Bookfile.open("BookData.txt",ios::out);
            Bookfile<<allData;
            Bookfile.close();
        }
        else{
            cout<<"Book Id "<<search<<" Not Found---!"<<endl;
        }
    }

    void returnBook() {
        cout<<"Enter Book ID to Return : ";
        getline(cin,search);

        fstream borrowfile;
        borrowfile.open("BorrowData.txt",ios::in);

        string sID,bID,bName;
        string allData="";
        bool found = false;

        while(getline(borrowfile,sID,'|')){
            getline(borrowfile,bID,'|');
            getline(borrowfile,bName,'\n');

            if(sID == studentId && bID ==search){
                found = true;
                cout<<"Book Returned Successfully"<<endl;

            }
            else{
                allData += sID + "|" + bID + "|" + bName +"\n";

            }
        }
          borrowfile.close();
          if(!found) {
            cout<<"Book Not Found in Your Borrowed List"<<endl;
            return;
          }

          borrowfile.open("BorrowData.txt",ios::out);
          borrowfile<<allData;
          borrowfile.close();

          Bookfile.open("BookData.txt",ios::in);
          string allBooks="";

          while(getline(Bookfile,id,'|')){
            getline(Bookfile,name,'|');
            getline(Bookfile,author,'|');
            getline(Bookfile,quantity,'\n');

            if(id==search){
                int qty = stoi(quantity);
                qty++;
                quantity = to_string(qty);
            }
            allBooks += id + "|" + name + "|" + author +"|" + quantity +"\n";

          }
          Bookfile.close();

          Bookfile.open("BookData.txt",ios::out);
          Bookfile<<allBooks;
          Bookfile.close();

    }
    void studentPanel() {
        if(!studentLogin()) return;
        int choice;
        do{
        cout<<"\n=======================\n";
        cout<<"     STUDENT PANEL      "<<endl;
        cout<<"========================="<<endl;

        cout<<"1. Display All Books"<<endl;
        cout<<"2. Borrow Book"<<endl;
        cout<<"3. Return Book"<<endl;
        cout<<"0. Exit"<<endl;

        cout<<"Enter the Choice : ";
        cin>>choice;
        cin.ignore();

        switch(choice){
            case 1:
            displayBook();
            break;

            case 2:
            borrowBook();
            break;

            case 3:
            returnBook();
            break;

            case 0:
            cout<<"Exit"<<endl;
            break;

            default:
            cout<<"Invalid Choice---!"<<endl;
        }

        }
         while(choice!=0);

    }
  
};



int main() {
    Library library;
    Admin admin;
    Student student;
    int choice;
    do {
        cout <<"\n----------------------------\n";
        cout <<"1. Display All Books"<<endl;
        cout<<"2. Log into Admin Panel"<<endl;
        cout<<"3. Log into Student Panel"<<endl;
        cout<<"-------------------------------"<<endl;

        cout<<"------------------------"<<endl;
        cout << "Enter Choice: ";
        cout<<"------------------------"<<endl;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: 
            library.displayBook();
             break;
            case 2: 
            admin.adminPanel();
             break;
            case 3: 
            student.studentPanel();
             break;
            
            default: cout << "Invalid Choice!\n";
        }
    } while (choice != 0);

    return 0;
}