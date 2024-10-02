#include<iostream>      //for input output
#include<fstream>       //for file handling
#include<cctype>        //for character operation
#include<iomanip>       //for spacing and manipulation
using namespace std;



class account{
                        //declaring data member variables
    int ac_no;
    char name[50];
    int deposit;
    char type;
    public:
                       //declaring member function
    void create_account();
    void show_account() const;
    void modify();
    void dep(int);
    void draw(int);
    void report() const;
    int retacno() const;
    int retdeposit() const;
    char rettype() const;

};
                            //defining a function
void account::create_account()
{
        system("CLS");    // for clearing the screen
    cout << "\n\t\t\tEnter the Account No. : ";
    cin >> ac_no;
    cout << "\n\n\t\t\tPlease Enter the Name of the Account holder Here : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\n\t\t\tEnter Type of the Account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\n\t\t\tEnter The Initial amount : ";
    cin >> deposit;
    cout << "\n\n\t\t\tAccount Created..";
}
void account::show_account() const      //using const means it will no modify the object
{
    cout << "\n\t\t\tAccount No. : " << ac_no;
    cout << "\n\t\t\tAccount Holder Name : ";
    cout << name;
    cout << "\n\t\t\tType of Account : " << type;
    cout << "\n\t\t\tBalance amount : " << deposit;
}
void account::modify()                  //const is not used here as we want to modify/alter the object.....
{
    cout << "\n\t\t\tAccount No. : " << ac_no;
    cout << "\n\t\t\tModify Account Holder Name : ";
    cin.ignore();                       //to ignore extra characters remaining in account no......
    cin.getline(name, 50);              // to get full name including spaces......
    cout << "\n\t\t\tModify Type of Account : ";
    cin >> type;
    type = toupper(type);               //for typecasting it to uppercase from lowercase....
    cout << "\n\t\t\tModify Balance amount : ";
    cin >> deposit;
}
void account::dep(int x)
{
    deposit += x;                       //as depositing the money will increase bank balance 
}
 
void account::draw(int x)
{
    deposit -= x;                       //as withdrawing the money will decrease bank balance
}

void account::report() const            // it is used to display a summary of the account's details in a formatted way.

{
    cout << ac_no << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}
 
int account::retacno() const            //it returns the account number
{
    return ac_no;
}
 
int account::retdeposit() const         //it returns current bank balance
{
    return deposit;
}
 
char account::rettype() const           // it return type of account saving or current
{
    return type;
}

//declaration of function//


void write_account();                //used for creating new account
void display_sp(int);               //used for displaying account info of a specific account holder by it's account number
void modify_account(int);           //used for modifying details of an existing account
void delete_account(int);           //used to delete an existing account
void display_all();                 //used for displaying details of all accounts in system
void deposit_withdraw(int,int);     //used for handling deposit and withdrawl from a specific account

int main()
{
    char ch;        //used for storing user's menu selection(from 1 to 8)
    int num;        // used to store user's account number
    do{
        system("CLS");
        cout << "\n\n\t\t\t\t======================\n";
        cout << "\t\t\t\t||  BANK MANAGEMENT SYSTEM  ||\n"; 
        cout << "\n\t\t\t\t======================\n";

        cout << "\t\t\t\t    ::MAIN MENU::\n";
        cout << "\n\t\t\t\t1. NEW ACCOUNT";
        cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
        cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
        cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
        cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
        cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
        cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
        cout << "\n\t\t\t\t8. EXIT";
        cout << "\n\n\t\t\t\tSelect Your Option (1-8): ";
        cin >> ch;
        switch(ch)
        {
            case '1':
            write_account();
            break;
            case '2':
            system("CLS");
            cout <<"\n\n\t\t\tEnter The account No. : ";cin>>num;
            deposit_withdraw(num,1);
            break;
            case '3':
            system("CLS");
            cout <<"\n\n\t\t\tEnter The account No. : ";cin>>num;
            deposit_withdraw(num,2);
            break;
            case '4':
            system("CLS");
            cout <<"\n\n\t\t\tEnter The account No. : ";cin>>num;
            display_sp(num);
            break;
            case '5':
            system("CLS");
            display_all();
            break;
            case '6':
            system("CLS");
            cout <<"\n\n\t\t\tEnter The account No. : ";cin>>num;
            delete_account(num);
            break;
            case '7':
            system("CLS");
            cout <<"\n\n\t\t\tEnter The account No. : ";cin>>num;
            modify_account(num);
            break;
            case '8':
            system("CLS");
            cout <<"\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
            cout <<"THANK YOU FOR USING BANK MANAGEMENT SYSTEM"<<endl;
            break;
            default:
            cout <<"\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
        }
            cin.ignore();
            cin.get();
    }while(ch !='8');
    return 0;
}

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
    outFile.close();
}
 
void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\t\t\tBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        if (ac.retacno() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\n\t\t\tAccount number does not exist";
}

       
    

void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            cout << "\n\n\t\t\tEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur); 
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\t\t\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n\t\t\tRecord Not Found ";
}



void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);        //for setting pointer at the beginning
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        if (ac.retacno() != n)      //as we want to delete that record logic!!
        {
            outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\nRecord Deleted ..";
}
 
 
void display_all()
{
    system("CLS");
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}


void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char*> (&ac), sizeof(account));
        if (ac.retacno() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\t\t\tTO DEPOSITSS AMOUNT";
                cout << "\n\n\t\t\tEnter The amount to be deposited: ";
                cin >> amt;
                ac.dep(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\t\t\tTO WITHDRAW AMOUNT";
                cout << "\n\n\t\t\tEnter The amount to be withdraw: ";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if (bal < 0)
                    cout << "Insufficience balance";
                else
                    ac.draw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);//fn1353
            File.write(reinterpret_cast<char*> (&ac), sizeof(account));
            cout << "\n\n\t\t\tRecord Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n\t\t\tRecord Not Found ";
}
