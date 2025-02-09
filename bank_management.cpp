#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

#define MIN_BALANCE 100

class deficient_funds
{
};

class Cl_Accounts
{
private:
    long Accnt_No;
    string client_fname;
    string client_lname;
    string password;
    float client_balance;
    static long Nxt_Accnt_No;

public:
    Cl_Accounts() {}
    Cl_Accounts(string fname, string lname, string pwd, float client_balance);
    long getAccNo() { return Accnt_No; }
    string getFName() { return client_fname; }
    string getLName() { return client_lname; }
    string getPassword() { return password; }
    float getBlnce() { return client_balance; }
    void Deposit(float amount);
    void Withdraw(float amount);
    static void setLstAccntNo(long Accnt_No);
    static long getLstAccntNo();
    friend ofstream &operator<<(ofstream &ofs, Cl_Accounts &acc);
    friend ifstream &operator>>(ifstream &ifs, Cl_Accounts &acc);
    friend ostream &operator<<(ostream &os, Cl_Accounts &acc);
};

long Cl_Accounts::Nxt_Accnt_No = 0;

class Bank
{
private:
    map<long, Cl_Accounts> accounts_cl;

public:
    Bank();
    Cl_Accounts Cl_Open_Account(string fname, string lname, string pwd, float balance);
    Cl_Accounts Cl_Balance_Enquiry(long Account_no);
    Cl_Accounts Deposit(long Account_no, float amt);
    Cl_Accounts Withdraw(long Account_no, float amt);
    void CloseAccount(long Account_no);
    void ShowAllAccounts();
    void Transfer(long fromAccountNo, long toAccountNo, float amount);
    ~Bank();
};

int main()
{
    Bank bank1, bank2;
    Bank *selected_bank = nullptr;
    Cl_Accounts acc;
    int option, bank_choice;
    string fname, lname, password;
    long account_no, to_account_no;
    float blnced, amnts;

    cout << "***Bank Management System***" << endl;

    while (true)
    {
        cout << "\nSelect a Bank:";
        cout << "\n1. Bank 1";
        cout << "\n2. Bank 2";
        cout << "\n3. Quit";
        cout << "\nEnter your choice: ";
        cin >> bank_choice;

        if (bank_choice == 1)
            selected_bank = &bank1;
        else if (bank_choice == 2)
            selected_bank = &bank2;
        else if (bank_choice == 3)
            break;
        else
        {
            cout << "Invalid choice. Please select again.";
            continue;
        }

        while (true)
        {
            cout << "\n1. Open an Account";
            cout << "\n2. Login";
            cout << "\n3. Back to Bank Selection";
            cout << "\nEnter your choice: ";
            cin >> option;

            if (option == 1)
            {
                cout << "Enter First Name: ";
                cin >> fname;
                cout << "Enter Last Name: ";
                cin >> lname;
                cout << "Create Password: ";
                cin >> password;
                cout << "Enter Initial Balance: ";
                cin >> blnced;
                acc = selected_bank->Cl_Open_Account(fname, lname, password, blnced);
                cout << "\nCongratulations! Account is Created." << endl;
                cout << acc;
            }
            else if (option == 2)
            {
                cout << "Enter Account Number: ";
                cin >> account_no;
                cout << "Enter Password: ";
                cin >> password;

                try
                {
                    Cl_Accounts account = selected_bank->Cl_Balance_Enquiry(account_no);
                    if (account.getPassword() == password)
                    {
                        cout << "\nLogin Successful!" << endl;  
                        string fname = account.getFName();  
                        string lname = account.getLName();
                        string account_number = to_string(account.getAccNo());                  
                        cout<<"\n" <<fname<<" "<<lname<<", Welcome to your account."<<endl;  
                        cout<<"\n"<<"Account Number: "<<account_number<<endl;                     
                        while (true)
                        {
                            cout << "\n1. Balance Enquiry";
                            cout << "\n2. Deposit";
                            cout << "\n3. Withdrawal";
                            cout << "\n4. Close Account";
                            cout << "\n5. Show All Accounts";
                            cout << "\n6. Fund Transfer";
                            cout << "\n7. Logout";
                            cout << "\nEnter your choice: ";
                            cin >> option;

                            switch (option)
                            {
                            case 1:
                                cout << "\nYour Account Details:" << endl;
                                cout << account;
                                break;
                            case 2:
                                cout << "Enter Amount to Deposit: ";
                                cin >> amnts;
                                account = selected_bank->Deposit(account_no, amnts);
                                cout << "\nAmount Deposited Successfully." << endl;
                                cout << account;
                                break;
                            case 3:
                                cout << "Enter Amount to Withdraw: ";
                                cin >> amnts;
                                account = selected_bank->Withdraw(account_no, amnts);
                                cout << "\nAmount Withdrawn Successfully." << endl;
                                cout << account;
                                break;
                            case 4:
                                selected_bank->CloseAccount(account_no);
                                cout << "\nAccount Closed Successfully." << endl;
                                goto logout;
                            case 5:
                                selected_bank->ShowAllAccounts();
                                break;
                            case 6:
                                cout << "Enter your account number: ";
                                cin >> account_no;
                                cout << "Enter recipient account number: ";
                                cin >> to_account_no;
                                cout << "Enter amount to transfer: ";
                                cin >> amnts;

                                try
                                {
                                    selected_bank->Transfer(account_no, to_account_no, amnts);
                                    cout << "\nFund Transfer Successful!" << endl;
                                }
                                catch (const exception &e)
                                {
                                    cout << "\nTransfer Failed: " << e.what() << endl;
                                }
                                break;
                            case 7:
                                goto logout;
                            default:
                                cout << "Invalid choice. Please try again.";
                            }
                        logout:
                            break;
                        }
                    }
                    else
                    {
                        cout << "\nInvalid Password. Please try again.";
                    }
                }
                catch (...)
                {
                    cout << "\nAccount Not Found.";
                }
            }
            else if (option == 3)
            {
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again.";
            }
        }
    }

    return 0;
}

Cl_Accounts::Cl_Accounts(string fname, string lname, string pwd, float client_balance)
{
    Nxt_Accnt_No++;
    Accnt_No = Nxt_Accnt_No;
    client_fname = fname;
    client_lname = lname;
    password = pwd;
    this->client_balance = client_balance;
}

void Cl_Accounts::Deposit(float amt)
{
    client_balance += amt;
}

void Cl_Accounts::Withdraw(float amt)
{
    if (client_balance - amt < MIN_BALANCE)
        throw deficient_funds();
    client_balance -= amt;
}

void Cl_Accounts::setLstAccntNo(long Accnt_No)
{
    Nxt_Accnt_No = Accnt_No;
}

long Cl_Accounts::getLstAccntNo()
{
    return Nxt_Accnt_No;
}

ofstream &operator<<(ofstream &ofs, Cl_Accounts &acc)
{
    ofs << acc.Accnt_No << endl;
    ofs << acc.client_fname << endl;
    ofs << acc.client_lname << endl;
    ofs << acc.password << endl;
    ofs << acc.client_balance << endl;
    return ofs;
}

ifstream &operator>>(ifstream &ifs, Cl_Accounts &acc)
{
    ifs >> acc.Accnt_No;
    ifs >> acc.client_fname;
    ifs >> acc.client_lname;
    ifs >> acc.password;
    ifs >> acc.client_balance;
    return ifs;
}

ostream &operator<<(ostream &os, Cl_Accounts &acc)
{
    os << "First Name: " << acc.getFName() << endl;
    os << "Last Name: " << acc.getLName() << endl;
    os << "Account Number: " << acc.getAccNo() << endl;
    os << "Balance: " << acc.getBlnce() << endl;
    return os;
}

Bank::Bank()
{
    Cl_Accounts acnt;
    ifstream infile;
    infile.open("Bank.data");
    if (!infile)
    {
        return;
    }
    while (!infile.eof())
    {
        infile >> acnt;
        accounts_cl.insert(pair<long, Cl_Accounts>(acnt.getAccNo(), acnt));
    }
    Cl_Accounts::setLstAccntNo(acnt.getAccNo());
    infile.close();
}

Cl_Accounts Bank::Cl_Open_Account(string fname, string lname, string pwd, float balance)
{
    ofstream outfile;
    Cl_Accounts acnt(fname, lname, pwd, balance);
    accounts_cl.insert(pair<long, Cl_Accounts>(acnt.getAccNo(), acnt));
    outfile.open("Bank.data", ios::trunc);
    map<long, Cl_Accounts>::iterator itr;
    for (itr = accounts_cl.begin(); itr != accounts_cl.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
    return acnt;
}

Cl_Accounts Bank::Cl_Balance_Enquiry(long Accnt_No)
{
    map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
    if (itr != accounts_cl.end())
        return itr->second;
    else
        throw runtime_error("Account not found");
}

Cl_Accounts Bank::Deposit(long Accnt_No, float amt)
{
    map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
    itr->second.Deposit(amt);
    return itr->second;
}

Cl_Accounts Bank::Withdraw(long Accnt_No, float amt)
{
    map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
    itr->second.Withdraw(amt);
    return itr->second;
}

void Bank::CloseAccount(long Accnt_No)
{
    map<long, Cl_Accounts>::iterator itr = accounts_cl.find(Accnt_No);
    cout << "Account Deleted: " << itr->second;
    accounts_cl.erase(Accnt_No);
}

void Bank::ShowAllAccounts()
{
    map<long, Cl_Accounts>::iterator itr;
    for (itr = accounts_cl.begin(); itr != accounts_cl.end(); itr++)
    {
        cout << "Account " << itr->first << endl
             << itr->second << endl;
    }
}

void Bank::Transfer(long fromAccountNo, long toAccountNo, float amount)
{
    if (amount <= 0)
        throw invalid_argument("Amount must be greater than zero.");

    map<long, Cl_Accounts>::iterator fromAccountItr = accounts_cl.find(fromAccountNo);
    map<long, Cl_Accounts>::iterator toAccountItr = accounts_cl.find(toAccountNo);

    if (fromAccountItr == accounts_cl.end())
        throw runtime_error("Sender account not found.");
    if (toAccountItr == accounts_cl.end())
        throw runtime_error("Receiver account not found.");

    Cl_Accounts &fromAccount = fromAccountItr->second;
    Cl_Accounts &toAccount = toAccountItr->second;

    if (fromAccount.getBlnce() < amount)
        throw runtime_error("Insufficient funds in sender's account.");

    fromAccount.Withdraw(amount);
    toAccount.Deposit(amount);
}

Bank::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.data", ios::trunc);
    map<long, Cl_Accounts>::iterator itr;
    for (itr = accounts_cl.begin(); itr != accounts_cl.end(); itr++)
    {
        outfile << itr->second;
    }
}
