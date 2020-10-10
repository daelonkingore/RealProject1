#include <string>
using namespace std;

class Account {

private:
    string accountNum;
    int balance;
    int annualInterestRate;
    int annualServiceChrg;
    int dailyInterestRate;
    int dailyinterest;
    bool yearChrg = false;
    bool closeFlag = false;

public:
    void setAnnualServiceChrg(int);
    void calcInt();
    void yearlyCharge();
    virtual void deposit(int);
    virtual void withdraw(int);
    virtual void closeAcc();
    string getAccountNum();
    int getBalance();
    int getAnnualInterestRate();
    int getAnnualServiceChrg();

    // constructor sets all the initial values
    Account(int initialBalance, int interestRate, string accNum) {
        /* Accepts arguments for the initial balance, an annual interest rate, and a 
        unique account number */
        balance = initialBalance;
        annualInterestRate = interestRate;
        accountNum = accNum;
    }
};

// set the Annual Charge (may be used later)
void Account::setAnnualServiceChrg(int aServChrg) {
    annualServiceChrg = aServChrg;
}

// Returns values of necessary members
string Account::getAccountNum() {
    return accountNum;
}

int Account::getBalance() {
    return balance;
}

int Account::getAnnualInterestRate() {
    return annualInterestRate;
}

int Account::getAnnualServiceChrg() {
    return annualServiceChrg;
}

// functions to change balance, close account, and mess with interest
void Account::deposit(int depositAmnt) {
    /* A virtual function that accepts an argument for the amount of the deposit. 
    Eventually, the function should add the argument value to the account balance */
    balance += depositAmnt;
}

void Account::withdraw(int withdrawAmnt) {
    /* A virtual function that accepts an argument for the amount of the withdrawal.
    Eventually, the function should subtract the argument value from the balance */
    balance -= withdrawAmnt;
}

void Account::closeAcc() {
    // A virtual function to close a bank account.
    closeFlag = true;
}

void Account::calcInt() {
    /* A function that updates the balance by calculating the daily interest earned 
    by the account and adding this interest to the balance. This should be performed 
    by the following formulas */

    dailyInterestRate = annualInterestRate / 365;
    dailyinterest = balance * dailyInterestRate;
    balance += dailyinterest;
}

// yearly charge may be used later
void Account::yearlyCharge() {
    /* A function that will subtract the yearly service charge from the balance. 
    Yearly service charge must not be subtracted more than once in a given calendar year */
    yearChrg = true;
    balance -= annualServiceChrg;
}