#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BankAccount 
{
protected:
    int id;
    double balance;
public:
    BankAccount()
    {
        id = 0;
        balance = 0;
    }
    BankAccount(int current_id, double current_balance)
    {
        id = current_id;
        balance = current_balance;
    }
    BankAccount(const BankAccount& other)
    {
        this->id = other.id;
        this->balance = other.balance;
    }
    BankAccount(ifstream& in)
    {
        while (!in.eof()) 
        {
            in >> id;        
            in >> balance;
        }
    }
    void SetId(int current_id)
    {
        id = current_id;
    }
    void SetBalance(double current_balance)
    {
        balance = current_balance;
    }
    int GetId()
    {
        return id;
    }
    int GetBalace()
    {
        return balance;
    }
    
    virtual void PrintAccount()
    {
        cout << "Account ID: " << id << endl;
        cout << "Balance: " << balance << endl;
    }
    virtual void execution_transaction(double summa) {}
    
    void deposit(double summa)
    {    
        balance += summa;
    }
    void debit(double summa)
    {
        if (balance >= summa)
        {
            balance -= summa;
        }
        else
        {    
            cout <<  "sufficient funds on this account!" << endl;
        }
    }

    void whriteAccount()
    {
        ofstream output("output.txt", ios::app);
        output << id << "   " << balance << endl;

        output.close();
    }
    bool operator == (const BankAccount& other)
    {
        return (this->id == other.id && this->balance == other.balance);
    }
    virtual ~BankAccount() {}

};
class SavingsAccount : public BankAccount
{
private:
    double koef;
public:
    int operation;
    SavingsAccount(int id, double balance) : BankAccount(id, balance) {}
    ~SavingsAccount() {}
    void SetKoef(double kof)
    {
        koef = kof;
    }
    void execution_transaction(double summa) override
    {
        cout << "Choose transaction: " << endl << "1. Deposit" << endl << "2. Debit" << endl << "Enter type (1/2)" << endl;
        cin >> operation;
        if (operation == 1)
        {
            if (summa > 0)
            { 
                balance += summa;
                balance += balance * koef;
            }
            else
                cout << "Invalid value." << endl;
        }
        else if (operation == 2)
        {
            if (summa > 0 && balance >= summa)
            {
                balance -= summa;
                balance += balance * koef;
            }
            else
                cout << "Invalid value." << endl;
        }
        else
            cout << "Error : incorrect transaction" << endl;
    }
    void PrintAccount() override
    {
        cout << "Saving Account (ID: " << id << ")" << endl;
        cout << "Balance: " << balance << endl;   
    }

};
class CheckingAccount : public BankAccount
{
public:
    int operation;
    CheckingAccount(int id, double balance) : BankAccount(id, balance){}
    ~CheckingAccount() {}
    void execution_transaction(double summa) override
    {
        cout << "Choose transaction: " << endl << "1. Deposit" << endl << "2. Debit" << endl << "Enter type (1/2)" << endl;
        cin >> operation;
        if (operation == 1)
        {
            if (summa > 0)
                balance += summa;
            else
                cout << "Invalid value." << endl;
        }
        else if (operation == 2)
        {
            if (summa > 0 && balance >= summa)
                balance -= summa;
            else
                cout << "Invalid value." << endl;
        }
        else
            cout << "Error : incorrect transaction" << endl;
    }
    void PrintAccount() override
    {
        cout << "Checking Account (ID: " << id << ")" << endl;
        cout << "Balance: " << balance << endl;
    }
};
class Customer 
{
private:
    string Name;
    BankAccount* curr_account;
public:
    Customer() 
    {
        Name = "";
        curr_account = nullptr;
    }
    Customer(const string client_name)
    {
        Name = client_name;
        curr_account = nullptr;
    }
    ~Customer() 
    {
        delete curr_account;
    }
    
    void SetName(string client_name)
    {
        Name = client_name;
    }
    string GetName() const
    {
        return Name;
    }
    BankAccount* GetAccount() const
    {
        return curr_account;
    }
    void PrintAccount()
    {
        curr_account->PrintAccount();
    }
};
class Transaction 
{
private:
    double summa;
public:
    Transaction()
    {
        summa = 0;
    }
    Transaction(double tr_summa)
    {
        summa = tr_summa;
    }
    ~Transaction() {}

    void SetSum(double tr_summa)
    {
        summa = tr_summa;
    }
    double GetSum()
    {
        return summa;
    }

    void deposit(BankAccount* curr_account)
    {
        curr_account->deposit(summa);
    }
    void debit(BankAccount* curr_account)
    {
        curr_account->debit(summa);
    }
};

int main()
{
    string name;
    int id;
    string type0, type1;
    int random_number, id_operation, new_account;
    double curr_balance, summ;
    SavingsAccount A(123, 1000.0);

    

    while (true)
    {
        cout << "Welcome to the banking system!" << endl;
        cout << "Are you a new user or already have an account?" << endl;
        cout << "Enter '1' if you already have an account and '0' if you want to create it." << endl;
        cin >> new_account;
        if (new_account == 0)
        {
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter account type (Savings/Cheking): ";
            cin >> type0;
            random_number = 1 + rand() % 50;
            if (type0 == "Savings")
            {
                SavingsAccount account(random_number, 0);
            }
            else if (type0 == "Cheking")
            {
                CheckingAccount account(random_number, 0);
            }
            else
            {
                cout << "Incorret comand. Try again." << endl;
                break;
            }
            cout << type0 << " account created." << endl;
            cout << "Client name: " << name << "    ID: " << random_number << endl;
        }

        cout << "Operations list: " << endl;
        cout << "1. Execute transaction" << endl;
        cout << "2. Read from file" << endl;
        cout << "3. Save to file" << endl;
        cout << "4. Check account info" << endl;
        cout << "5. Exit" << endl;
        cout << endl;
        cout << "Enter operation ID: ";
        cin >> id_operation;


        if (id_operation == 1)
        {
            cout << "Enter account type (Savings/Cheking): ";
            cin >> type1;
            if (type1 == "Savings")
            {
                cout << "Enter account ID: ";
				cin >> id;
				cout << "Enter current balance: ";
				cin >> curr_balance;

				SavingsAccount acc(id, curr_balance);
                acc.SetKoef(0.08);
				cout << "Enter transaction summ: ";
				cin >> summ;
				acc.execution_transaction(summ);
                cout << "Done!" << endl;
                acc.PrintAccount();
                return 0;
            }
            else if (type1 == "Cheking")
            {
                
                cout << "Enter account ID: ";
				cin >> id;
				cout << "Enter current balance: ";
				cin >> curr_balance;
				CheckingAccount acc(id, curr_balance);
				cout << "Enter transaction summ: ";
				cin >> summ;
				acc.execution_transaction(summ);
                cout << "Done!" << endl;
                acc.PrintAccount();
                return 0;
            }
        }
        else if (id_operation == 2)
        {
            ifstream file1("file1.txt");
            BankAccount acc(file1);
            acc.PrintAccount();
            file1.close();
            return 0;    
        }
        else if (id_operation == 3)
        {
            cout << "Enter account ID: ";
			cin >> id;
			cout << "Enter current balance: ";
			cin >> curr_balance;
			BankAccount acc(id, curr_balance);
            acc.whriteAccount();
            cout << "Account saved to file." << endl;
            return 0;
        }
        else if (id_operation == 4)
        {
            A.PrintAccount();
            return 0;
        }
        else if (id_operation == 5)
        {
            cout << "The session is over" << endl;
            return 0;
        }
        else
            cout << "Incorrect id of operation!" << endl;
            cout << "Try again: " << endl;
            
    }
    
    return 0;
}
    
