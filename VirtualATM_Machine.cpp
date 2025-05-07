#include <iostream>
#include <cstring>
using namespace std;

const int MAX_USERS = 5;

struct Account {
    char name[50];
    int accNumber;
    int pin;
    float balance;
};

// Sample user data (can be made dynamic)
void initializeAccounts(Account* users) {
    strcpy(users[0].name, "Alice");
    users[0].accNumber = 1001;
    users[0].pin = 1234;
    users[0].balance = 5000;

    strcpy(users[1].name, "Bob");
    users[1].accNumber = 1002;
    users[1].pin = 5678;
    users[1].balance = 3000;

    strcpy(users[2].name, "Charlie");
    users[2].accNumber = 1003;
    users[2].pin = 2468;
    users[2].balance = 7000;
}

Account* login(Account* users, int totalUsers) {
    int accNum, pin;
    cout << "Enter Account Number: ";
    cin >> accNum;
    cout << "Enter PIN: ";
    cin >> pin;

    for (int i = 0; i < totalUsers; ++i) {
        if (users[i].accNumber == accNum && users[i].pin == pin) {
            cout << "\nLogin successful. Welcome, " << users[i].name << "!\n\n";
            return &users[i];
        }
    }

    cout << "Invalid account number or PIN.\n\n";
    return nullptr;
}

void checkBalance(Account* acc) {
    cout << "Current Balance: $" << acc->balance << "\n\n";
}

void deposit(Account* acc) {
    float amount;
    cout << "Enter amount to deposit: $";
    cin >> amount;
    if (amount > 0) {
        acc->balance += amount;
        cout << "Deposit successful.\n\n";
    }
    else {
        cout << "Invalid amount.\n\n";
    }
}

void withdraw(Account* acc) {
    float amount;
    cout << "Enter amount to withdraw: $";
    cin >> amount;
    if (amount <= 0) {
        cout << "Invalid amount.\n\n";
    }
    else if (amount > acc->balance) {
        cout << "Insufficient balance.\n\n";
    }
    else {
        acc->balance -= amount;
        cout << "Withdrawal successful.\n\n";
    }
}

void transfer(Account* sender, Account* users, int totalUsers) {
    int recvAccNum;
    float amount;
    cout << "Enter recipient account number: ";
    cin >> recvAccNum;
    cout << "Enter amount to transfer: $";
    cin >> amount;

    if (amount <= 0 || amount > sender->balance) {
        cout << "Invalid or insufficient amount.\n\n";
        return;
    }

    for (int i = 0; i < totalUsers; ++i) {
        if (users[i].accNumber == recvAccNum && &users[i] != sender) {
            sender->balance -= amount;
            users[i].balance += amount;
            cout << "Transferred $" << amount << " to " << users[i].name << " successfully.\n\n";
            return;
        }
    }

    cout << "Recipient account not found.\n\n";
}

void changePIN(Account* acc) {
    int newPIN;
    cout << "Enter new 4-digit PIN: ";
    cin >> newPIN;
    if (newPIN >= 1000 && newPIN <= 9999) {
        acc->pin = newPIN;
        cout << "PIN changed successfully.\n\n";
    }
    else {
        cout << "Invalid PIN format.\n\n";
    }
}

void showMenu() {
    cout << "===== VIRTUAL ATM SYSTEM =====\n";
    cout << "1. Check Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Transfer Money\n";
    cout << "5. Change PIN\n";
    cout << "6. Logout\n";
    cout << "Choose an option: ";
}

int main() {
    Account users[MAX_USERS];
    initializeAccounts(users);

    Account* currentUser = nullptr;
    int choice;

    while (true) {
        if (currentUser == nullptr) {
            currentUser = login(users, 3); // 3 pre-created users
        }
        else {
            showMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                checkBalance(currentUser);
                break;
            case 2:
                deposit(currentUser);
                break;
            case 3:
                withdraw(currentUser);
                break;
            case 4:
                transfer(currentUser, users, 3);
                break;
            case 5:
                changePIN(currentUser);
                break;
            case 6:
                cout << "Logged out.\n\n";
                currentUser = nullptr;
                break;
            default:
                cout << "Invalid option. Try again.\n\n";
            }
        }
    }

    return 0;
}
