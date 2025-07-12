#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class BankAccount {
private:
    string accountHolderName;
    int accountNumber;
    double balance;
    
public:
    // Constructor
    BankAccount(string name, int accNum, double initialBalance = 0.0) {
        accountHolderName = name;
        accountNumber = accNum;
        balance = initialBalance;
    }
    
    // Getter methods
    string getName() const { return accountHolderName; }
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    
    // Deposit function
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << fixed << setprecision(2) << amount << endl;
            cout << "New balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            cout << "Invalid amount! Deposit amount must be positive." << endl;
        }
    }
    
    // Withdrawal function
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount! Withdrawal amount must be positive." << endl;
        } else if (amount > balance) {
            cout << "Insufficient funds! Available balance: $" << fixed << setprecision(2) << balance << endl;
        } else {
            balance -= amount;
            cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << endl;
            cout << "Remaining balance: $" << fixed << setprecision(2) << balance << endl;
        }
    }
    
    // Balance inquiry
    void displayBalance() const {
        cout << "Account Balance: $" << fixed << setprecision(2) << balance << endl;
    }
    
    // Display account details
    void displayAccountInfo() const {
        cout << "\n--- Account Information ---" << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "-------------------------" << endl;
    }
};

class BankingSystem {
private:
    vector<BankAccount> accounts;
    int nextAccountNumber;
    
public:
    BankingSystem() : nextAccountNumber(1001) {}
    
    // Create new account
    void createAccount() {
        string name;
        double initialDeposit;
        
        cout << "\n--- Create New Account ---" << endl;
        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter initial deposit amount: $";
        cin >> initialDeposit;
        
        if (initialDeposit < 0) {
            cout << "Initial deposit cannot be negative!" << endl;
            return;
        }
        
        BankAccount newAccount(name, nextAccountNumber, initialDeposit);
        accounts.push_back(newAccount);
        
        cout << "Account created successfully!" << endl;
        cout << "Your account number is: " << nextAccountNumber << endl;
        nextAccountNumber++;
    }
    
    // Find account by account number
    BankAccount* findAccount(int accNum) {
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i].getAccountNumber() == accNum) {
                return &accounts[i];
            }
        }
        return nullptr;
    }
    
    // Handle deposit transaction
    void handleDeposit() {
        int accNum;
        double amount;
        
        cout << "\n--- Deposit Money ---" << endl;
        cout << "Enter account number: ";
        cin >> accNum;
        
        BankAccount* account = findAccount(accNum);
        if (account == nullptr) {
            cout << "Account not found!" << endl;
            return;
        }
        
        cout << "Enter deposit amount: $";
        cin >> amount;
        
        account->deposit(amount);
    }
    
    // Handle withdrawal transaction
    void handleWithdrawal() {
        int accNum;
        double amount;
        
        cout << "\n--- Withdraw Money ---" << endl;
        cout << "Enter account number: ";
        cin >> accNum;
        
        BankAccount* account = findAccount(accNum);
        if (account == nullptr) {
            cout << "Account not found!" << endl;
            return;
        }
        
        cout << "Enter withdrawal amount: $";
        cin >> amount;
        
        account->withdraw(amount);
    }
    
    // Handle balance inquiry
    void handleBalanceInquiry() {
        int accNum;
        
        cout << "\n--- Balance Inquiry ---" << endl;
        cout << "Enter account number: ";
        cin >> accNum;
        
        BankAccount* account = findAccount(accNum);
        if (account == nullptr) {
            cout << "Account not found!" << endl;
            return;
        }
        
        account->displayAccountInfo();
    }
    
    void displayAllAccounts() {
        if (accounts.empty()) {
            cout << "\nNo accounts found in the system." << endl;
            return;
        }
        
        cout << "\n--- All Accounts ---" << endl;
        for (int i = 0; i < accounts.size(); i++) {
            accounts[i].displayAccountInfo();
        }
    }
    
    // Display menu
    void displayMenu() {
        cout << "\n========== BANKING SYSTEM ==========" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Balance Inquiry" << endl;
        cout << "5. Display All Accounts" << endl;
        cout << "6. Exit" << endl;
        cout << "====================================" << endl;
        cout << "Enter your choice (1-6): ";
    }
    
    // Run the banking system
    void run() {
        int choice;
        
        cout << "Welcome to the Banking System!" << endl;
        
        while (true) {
            displayMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    handleDeposit();
                    break;
                case 3:
                    handleWithdrawal();
                    break;
                case 4:
                    handleBalanceInquiry();
                    break;
                case 5:
                    displayAllAccounts();
                    break;
                case 6:
                    cout << "Thank you for using our Banking System!" << endl;
                    cout << "Goodbye!" << endl;
                    return;
                default:
                    cout << "Invalid choice! Please enter a number between 1-6." << endl;
                    break;
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    }
};

int main() {
    BankingSystem bank;
    bank.run();
    return 0;
}