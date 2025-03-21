#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;
// TODO: Define custom exception classes here
// - NegativeDepositException (for negative deposit attempts)

class NegativeDepositException : public runtime_error {
public:
    NegativeDepositException() : runtime_error("Error: Deposit amount cannot be negative") {}
};

// - OverdrawException (for withdrawing more than the balance)
class OverdrawException : public runtime_error {
public:
    OverdrawException() : runtime_error("Error: Insufficient funds!") {}
};

// - InvalidAccountOperationException (for transactions on a closed account)
class InvalidAccountOperationException : public runtime_error {
public:
    InvalidAccountOperationException() : runtime_error("Error: Account is closed for transactions!") {}
};

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(std::string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        // TODO: Implement exception handling for negative deposits
        if(!isActive)
        {
            throw InvalidAccountOperationException();
        }
        if(amount<0)
        {
            throw NegativeDepositException();
        }
        balance += amount;
    
    }

    // Withdraw method
    void withdraw(double amount) {
        // TODO: Implement exception handling for overdrawing and closed accounts
        if (!isActive)
        {
            throw InvalidAccountOperationException();
        }
        if (amount > balance)
        {
            throw OverdrawException();
        }
        
        
        balance -= amount;
    }

    // Method to get current balance
    double getBalance() const {
        return balance;
    }

    // Method to close the account
    void closeAccount() {
        // TODO: Prevent further transactions when the account is closed
        isActive = false;
    }
};

int main() {
    try {
        
        // TODO: Ask the user to enter an initial balance and create a BankAccount object using smart pointers
        double initialBalance;
        cout << "Enter initial balance: $";
        cin >> initialBalance;
        //auto account = std::make_unique<BankAccount>("123456", initialBalance);

        auto account = std::make_unique<BankAccount>("123456", initialBalance); // Example initialization

       // std::cout << "Bank Account Created: #" << "123456" << std::endl;

        // TODO: Allow the user to enter deposit amounts and call deposit() method
        double depositAmount;
        cout<<"Please enter a deposit amount: $";
        cin>>depositAmount;
        
        account->deposit(depositAmount);
        //cout<<account->getBalance();

        // TODO: Allow the user to enter withdrawal amounts and call withdraw() method
        
        double withdrawAmount;
        cout<<"Please enter withdraw amount: $";
        cin>>withdrawAmount;
        account->withdraw(withdrawAmount);
        //cout<<account->getBalance();

        std::cout << "Current Balance: $" << account->getBalance() << std::endl;

        // TODO: Test edge cases - try withdrawing more than available balance
        //std::cout << "Attempting to withdraw $600..." << std::endl;
        //account->withdraw(600); // This should trigger an exception once implemented

    }
    catch (const std::exception& e) {
        // TODO: Catch and handle exceptions properly
        std::cerr << e.what() << std::endl;
        
    }

    return 0;
}
