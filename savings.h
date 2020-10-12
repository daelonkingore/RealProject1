#include <string>
using namespace std;

// Savings derived from Account class declaration.
class Savings : public Account {

private:
    bool status = true;
    bool denyFlag = false;
    string savingsAccNum;
    int savingsInitialBalance;
    int savingsInterestRate;
    int savingsNum;

public: 
    void withdraw(int);
    void deposit(int);

    // constructor setting the Savings accNum
    Savings(int initialBalance, int interestRate, int accNum) : Account(initialBalance, interestRate, savingsNum) {
        savingsAccNum = "S" + to_string(savingsNum);
    }
};

void Savings::withdraw(int withdrawAmnt) {
    if (status == true and getCloseFlag() == false) {

        if (getBalance() - withdrawAmnt < 0) { 
            // if the withdraw amount input goes below 0, deny
            cout << "Requested withdraw amount cause balance to go below $0. Request denied." << endl;
            denyFlag = true;
        }

        else if (getBalance() - withdrawAmnt < 50) { 
            // else if it doesn't go below 0, but does go below 50, service charge
            cout << "Alert in Savings account " << getAccountNum()  << ":\n"
            << "Withdraw amount going below $50, $5 service charge applied. " 
            << "Deactivating account until above $50. No more withdraws may be" 
            << " made until above $50." << endl;
            status = false;
            withdrawAmnt += 5;
        }

        if (getBalance() - withdrawAmnt < 0 and denyFlag == false) { 
            // if the service charge causes balance below 0, deny withdraw, but still charge
            cout << "Requested withdraw amount plus service charge cause balance to go below $0. "
            << "Request denied, service charge still applied." << endl;
            setBalance(getBalance() - 5);
            denyFlag = true;
        }
        
        else if (getBalance() - withdrawAmnt < 1 and getBalance() - withdrawAmnt >= 0 and denyFlag == false) {
            // else if savings account goes below 1, close Account ( need to change after main is done )
            cout << "ALERT in Savings account: " << getAccountNum() << ":\n"
            << " causes the account to shut down permanently. " << endl;
            closeAcc();
        }

        else if (getBalance() - withdrawAmnt >= 50 and denyFlag == false) {
            // else if savings account stays above 50, withdraw the amount normally
            cout << "Withdrawing: " << withdrawAmnt << endl;
            setBalance(getBalance() - withdrawAmnt);
            cout << "New balance: " << getBalance() << endl;
        }
    }

    else if (status == false and getCloseFlag() == false) {
        // if the account is inactive
        cout << "No withdraw's allowed until balance is about $50. " << endl;
    }

    else if (getCloseFlag() == true) {
        // if the account is closed
        cout << "This account has been permanently closed. " << endl;
    }
}

void Savings::deposit(int depositAmnt) {
    // deposit the amount into account
    cout << "Depositing: " << depositAmnt << endl;
    setBalance(getBalance() + depositAmnt);
    cout << "New balance: " << getBalance() << endl;
}