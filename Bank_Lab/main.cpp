//
//  main.cpp
//  Bank_Lab
//
//  Created by BRANDON SERRANO on 3/14/17.
//  Copyright © 2017 Trendsverse. All rights reserved.
//

#include<iostream>
#include<curses.h>
#include <unistd.h>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


class useraccount
{
    int account;
    char lastname[50];
    char firstname[50];
    int deposit;
    char type;
public:
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

void useraccount::create_account()
{
    cout<<"\nEnter The Account No. :";
    cin>>account;
    cout<<"\n\nEnter The  LastName of The Account Holder : ";
    cin.ignore();
    cin>>lastname;
    cout<<"\n\nEnter The  FirstName of The Account Holder : ";
    cin.ignore();
    cin>>firstname;
    cout<<"\nEnter Type of The Account (C)urrent/(S)avings : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nEnter The Initial Amount(>=500 for Saving and >=1000 for Current ) : ";
    cin>>deposit;
    cout<<"\n\n\nAccount Created..";
}

void useraccount::show_account() const
{
    cout<<"\nAccount No. : "<<account;
    cout<<"\nAccount Holder Name : ";
    cout<<lastname <<" , "<<firstname;
    cout<<"\nType of Account : "<<type;
    cout<<"\nBalance Amount : "<<deposit;
}


void useraccount::modify()
{
    cout<<"\nAccount No. : "<<account;
    cout<<"\nModify Account Holder LastName : ";
    cin.ignore();
    cin >> lastname;
    cout<<"\nModify Account Holder FirstName : ";
    cin.ignore();
    cin >> firstname;
    cout<<"\nModify Type of Account : ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance Amount : ";
    cin>>deposit;
}


void useraccount::dep(int x)
{
    deposit+=x;
}

void useraccount::draw(int x)
{
    deposit-=x;
}

void useraccount::report() const
{
    cout<<account<<setw(10)<<" "<<lastname<<","<< firstname<<setw(10)<<" "<<type<<setw(15)<<deposit<<endl;
}


int useraccount::retacno() const
{
    return account;
}

int useraccount::retdeposit() const
{
    return deposit;
}

char useraccount::rettype() const
{
    return type;
}


void write_account();	void display_sp(int);	void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
void intro();



int main()
{
    char ch;
    int num;
    intro();
    do
    {
        
        sleep(1);
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. NEW ACCOUNT" << endl;
        cout<<"\n\n\t02. DEPOSIT AMOUNT"<< endl;
        cout<<"\n\n\t03. WITHDRAW AMOUNT"<< endl;
        cout<<"\n\n\t04. BALANCE ENQUIRY"<< endl;
        cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST"<< endl;
        cout<<"\n\n\t06. CLOSE AN ACCOUNT"<< endl;
        cout<<"\n\n\t07. MODIFY AN ACCOUNT"<< endl;
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) "<< endl;
        cin>>ch;
        
        switch(ch)
        {
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\n\tEnter The account No. : "; cin>>num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                cout<<"\n\n\tEnter The account No. : "; cin>>num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                cout<<"\n\n\tEnter The account No. : "; cin>>num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout<<"\n\n\tEnter The account No. : "; cin>>num;
                delete_account(num);
                break;
            case '7':
                cout<<"\n\n\tEnter The account No. : "; cin>>num;
                modify_account(num);
                break;
            case '8':
                cout<<"\n\n\tGood-Bye"<< endl;
                exit(0);
                
            default :cout<<"\a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');
    return 0;
}



void write_account()
{
    useraccount ac;
    ofstream outFile;
    outFile.open("useraccount.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(useraccount));
    outFile.close();
}

void display_sp(int n)
{
    useraccount ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("useraccount.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(useraccount)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number does not exist";
}



void modify_account(int n)
{
    bool found=false;
    useraccount ac;
    fstream File;
    File.open("useraccount.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(useraccount));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(useraccount));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(useraccount));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}


void delete_account(int n)
{
    useraccount ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("useraccount.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(useraccount)))
    {
        if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(useraccount));
        }
    }
    inFile.close();
    outFile.close();
    remove("useraccount.dat");
    rename("Temp.dat","useraccount.dat");
    cout<<"\n\n\tRecord Deleted ..";
}


void display_all()
{
    useraccount account;
    ifstream inFile;
    inFile.open("useraccount.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER'S\n\n";
    cout<<"=================================================================\n";
    cout<<"Account no.      NAME                   Type        Balance\n";
    cout<<"=================================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&account), sizeof(account)))
    {
        account.report();
    }
    inFile.close();
}


void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    useraccount ac;
    fstream File;
    File.open("useraccount.dat", ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(useraccount));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\n\tTO DEPOSITE AMOUNT ";
                cout<<"\n\nEnter The amount to be deposited";
                cin>>amt;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"\n\n\tTO WITHDRAW AMOUNT ";
                cout<<"\n\nEnter The amount to be withdraw";
                cin>>amt;
                int bal=ac.retdeposit()-amt;
                if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    cout<<" Insufficient Balance";
                else
                    ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(useraccount));
            cout<<"\n\n\t Record Updated";
            found=true;
	       }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found ";
}




void intro()
{
    cout<<"\n\n\n\t  BANK";
    cout<<"\n\n\t  LAB";
    cout<<"\n\n\t  PROJECT 2";
    cout<<"\n\n\n\nMADE BY : BRANDON SERRANO";
    cout << "\n\nPlease Press Enter To Continue" << endl;
    cin.get();
}
