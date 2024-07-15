#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base class for Bank Account
class BankAccount {
protected:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    BankAccount(const string& name, int number, double initialBalance)
        : accountHolderName(name), accountNumber(number), balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
        cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    virtual void checkBalance() const {
        cout << "Account balance: $" << balance << endl;
    }

    virtual void displayAccountInfo() const {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

// Derived class for Savings Account
class SavingsAccount : public BankAccount {
public:
    SavingsAccount(const string& name, int number, double initialBalance)
        : BankAccount(name, number, initialBalance) {}

    // You can add specific features for SavingsAccount here
};

// Derived class for Checking Account
class CheckingAccount : public BankAccount {
public:
    CheckingAccount(const string& name, int number, double initialBalance)
        : BankAccount(name, number, initialBalance) {}

    // You can add specific features for CheckingAccount here
};

// Function to display menu
void displayMenu() {
    cout << "\n1. Open Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Check Balance" << endl;
    cout << "5. Display Account Information" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<BankAccount*> accounts;
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int number, type;
                double initialBalance;
                cout << "Enter account holder name: ";
                cin >> name;
                cout << "Enter account number: ";
                cin >> number;
                cout << "Enter initial balance: ";
                cin >> initialBalance;
                cout << "Enter account type (1 for Savings, 2 for Checking): ";
                cin >> type;

                if (type == 1) {
                    accounts.push_back(new SavingsAccount(name, number, initialBalance));
                } else if (type == 2) {
                    accounts.push_back(new CheckingAccount(name, number, initialBalance));
                } else {
                    cout << "Invalid account type!" << endl;
                }
                break;
            }
            case 2: {
                int number;
                double amount;
                cout << "Enter account number: ";
                cin >> number;
                cout << "Enter amount to deposit: ";
                cin >> amount;

                for (auto account : accounts) {
                    if (account->getAccountNumber() == number) {
                        account->deposit(amount);
                        break;
                    }
                }
                break;
            }
            case 3: {
                int number;
                double amount;
                cout << "Enter account number: ";
                cin >> number;
                cout << "Enter amount to withdraw: ";
                cin >> amount;

                for (auto account : accounts) {
                    if (account->getAccountNumber() == number) {
                        account->withdraw(amount);
                        break;
                    }
                }
                break;
            }
            case 4: {
                int number;
                cout << "Enter account number: ";
                cin >> number;

                for (auto account : accounts) {
                    if (account->getAccountNumber() == number) {
                        account->checkBalance();
                        break;
                    }
                }
                break;
            }
            case 5: {
                int number;
                cout << "Enter account number: ";
                cin >> number;

                for (auto account : accounts) {
                    if (account->getAccountNumber() == number) {
                        account->displayAccountInfo();
                        break;
                    }
                }
                break;
            }
            case 6:
                running = false;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    for (auto account : accounts) {
        delete account;
    }

    return 0;
}
