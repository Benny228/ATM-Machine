#include <iostream>
#include <string>

using namespace std;

const int MAX_ACCOUNTS = 100; // Maximum number of accounts

class Account {
public:
    string userId;
    string password;
    double balance;

    Account() : userId(""), password(""), balance(0.0) {} // Default constructor
};

class ATM {
private:
    Account accounts[MAX_ACCOUNTS]; // Array to store accounts
    int accountCount; // Current number of accounts

public:
    ATM() : accountCount(0) {} // Initialize account count

    void createAccount() {
        if (accountCount >= MAX_ACCOUNTS) {
            cout << "*** MAX ACCOUNT LIMIT REACHED! ***" << endl;
            return;
        }

        string userId, password;
        cout << "Please enter your user id: ";
        cin >> userId;
        cout << "Please enter your password: ";
        cin >> password;

        // Check if the account already exists
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].userId == userId) {
                cout << "*** ACCOUNT ALREADY EXISTS! ***" << endl;
                return;
            }
        }

        // Create new account
        accounts[accountCount].userId = userId;
        accounts[accountCount].password = password;
        accountCount++;
        cout << "Thank You! Your account has been created!" << endl;
    }

    bool login(string& userId, string& password) {
        cout << "Please enter your user id: ";
        cin >> userId;
        cout << "Please enter your password: ";
        cin >> password;

        // Check for valid login
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i].userId == userId && accounts[i].password == password) {
                cout << "Access Granted!" << endl;
                return true; // Successful login
            }
        }
        cout << "*** LOGIN FAILED! ***" << endl;
        return false; // Unsuccessful login
    }

    void mainMenu(Account& account) {
        char choice;
        do {
            cout << "\nd - Deposit Money\nw - Withdraw Money\nr - Request Balance\nq - Quit\n";
            cin >> choice;

            switch (choice) {
                case 'd':
                    deposit(account);
                    break;
                case 'w':
                    withdraw(account);
                    break;
                case 'r':
                    requestBalance(account);
                    break;
                case 'q':
                    cout << "Thank you for using the ATM. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } while (choice != 'q');
    }

    void deposit(Account& account) {
        double amount;
        cout << "Amount of deposit: $";
        cin >> amount;
        if (amount > 0) {
            account.balance += amount;
            cout << "Your balance is $" << account.balance << "." << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(Account& account) {
        double amount;
        cout << "Amount of withdrawal: $";
        cin >> amount;
        if (amount > 0 && amount <= account.balance) {
            account.balance -= amount;
            cout << "Your balance is $" << account.balance << "." << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }

    void requestBalance(Account& account) {
        cout << "Your balance is $" << account.balance << "." << endl;
    }

    void run() {
        char choice;
        do {
            cout << "\nHi! Welcome to the ATM Machine!" << endl;
            cout << "Please select an option from the menu below:\n";
            cout << "I - Login\nC - Create New Account\nQ - Quit\n";
            cin >> choice;

            switch (choice) {
                case 'I':
                case 'i': {
                    string userId, password;
                    if (login(userId, password)) {
                        // Find the account object for the logged-in user
                        for (int i = 0; i < accountCount; i++) {
                            if (accounts[i].userId == userId) {
                                mainMenu(accounts[i]);
                                break;
                            }
                        }
                    }
                    break;
                }
                case 'C':
                case 'c':
                    createAccount();
                    break;
                case 'Q':
                case 'q':
                    cout << "Thank you for using the ATM. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } while (choice != 'Q' && choice != 'q');
    }
};

int main() {
    ATM atm;
    atm.run();
    return 0;
}

