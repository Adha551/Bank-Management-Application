#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    float balance;

public:

    // Create Account
    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    // Display Account Details
    void displayAccount() const
    {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nCustomer Name  : " << name;
        cout << "\nBalance        : " << balance << endl;
    }

    // Get Account Number
    int getAccountNumber() const
    {
        return accountNumber;
    }

    // Deposit Money
    void deposit()
    {
        float amount;

        cout << "\nEnter Amount to Deposit: ";
        cin >> amount;

        balance += amount;

        cout << "\nAmount Deposited Successfully!";
    }

    // Withdraw Money
    void withdraw()
    {
        float amount;

        cout << "\nEnter Amount to Withdraw: ";
        cin >> amount;

        if(amount > balance)
        {
            cout << "\nInsufficient Balance!";
        }
        else
        {
            balance -= amount;
            cout << "\nWithdrawal Successful!";
        }
    }

    // Balance Inquiry
    void showBalance() const
    {
        cout << "\nCurrent Balance: " << balance << endl;
    }
};

// Create Account Function
void createNewAccount()
{
    BankAccount acc;

    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    file.write((char*)&acc, sizeof(acc));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display All Accounts
void displayAllAccounts()
{
    BankAccount acc;

    ifstream file("bank.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n===== Account Records =====\n";

    while(file.read((char*)&acc, sizeof(acc)))
    {
        acc.displayAccount();
        cout << "---------------------------\n";
    }

    file.close();
}

// Deposit Function
void depositMoney()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    while(file.read((char*)&acc, sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo)
        {
            acc.deposit();

            int pos = (-1) * sizeof(acc);

            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

// Withdraw Function
void withdrawMoney()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    while(file.read((char*)&acc, sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo)
        {
            acc.withdraw();

            int pos = (-1) * sizeof(acc);

            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

// Balance Inquiry
void balanceInquiry()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    while(file.read((char*)&acc, sizeof(acc)))
    {
        if(acc.getAccountNumber() == accNo)
        {
            acc.showBalance();

            found = true;

            break;
        }
    }

    file.close();

    if(!found)
    {
        cout << "\nAccount Not Found!\n";
    }
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n====== Bank Management System ======\n";

        cout << "1. Create New Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Balance Inquiry\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                createNewAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                balanceInquiry();
                break;

            case 5:
                displayAllAccounts();
                break;

            case 6:
                cout << "\nThank You for Using Bank System!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}
