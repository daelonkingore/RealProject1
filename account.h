#include <string>
using namespace std;

class Account {

    protected:
        string accountNum;
        double balance;
        double annualInterestRate;
        double annualServiceChrg;
        double dailyInterestRate;
        double dailyinterest;
        bool yearChrg = false;
        bool closeFlag = false;

    public:
        /*void setAnnualServiceChrg(int);
        void setBalance(int);
        void calcInt();
        void yearlyCharge();
        virtual void deposit(int);
        virtual void withdraw(int);
        virtual void closeAcc();
        virtual string getAccountNum();
        bool getCloseFlag();
        double getBalance();
        double getAnnualInterestRate();
        double getAnnualServiceChrg();*/

        Account(){}

        // constructor sets all the initial values
<<<<<<< HEAD
        Account(double initialBalance, double interestRate, string accNum) {
=======
        Account(int initialBalance, int interestRate, string accNum) {
>>>>>>> b314eb8da7c500e75af9c1281938bf51d1c0dd9b
            /* Accepts arguments for the initial balance, an annual interest rate, and a
            unique account number */
            balance = initialBalance;
            annualInterestRate = interestRate;
            accountNum = accNum;
        }

<<<<<<< HEAD
        Account(double initialBalance, double interestRate, string accNum, bool closeFlg) {
=======
        Account(int initialBalance, int interestRate, string accNum, bool closeFlg) {
>>>>>>> b314eb8da7c500e75af9c1281938bf51d1c0dd9b
            /* Accepts arguments for the initial balance, an annual interest rate, and a
            unique account number */
            balance = initialBalance;
            annualInterestRate = interestRate;
            accountNum = accNum;
            closeFlag = closeFlg;
        }

                // set the Annual Charge (may be used later)
        void setAnnualServiceChrg(int aServChrg) {
            annualServiceChrg = aServChrg;
        }

<<<<<<< HEAD
        void setBalance(double newBalance) {
=======
        void setBalance(int newBalance) {
>>>>>>> b314eb8da7c500e75af9c1281938bf51d1c0dd9b
            balance = newBalance;
        }

        // Returns values of necessary members
        virtual string getAccountNum() {
            return accountNum;
        }

        virtual bool getCloseFlag() {
            return closeFlag;
        }

        double getBalance() {
            return balance;
        }

        double getAnnualInterestRate() {
            return annualInterestRate;
        }

        double getAnnualServiceChrg() {
            return annualServiceChrg;
        }

        // functions to change balance, close account, and mess with interest
        virtual void deposit(double depositAmnt) {
            /* A virtual function that accepts an argument for the amount of the deposit.
            Eventually, the function should add the argument value to the account balance */
            balance += depositAmnt;
        }

        virtual void withdraw(double withdrawAmnt) {
            /* A virtual function that accepts an argument for the amount of the withdrawal.
            Eventually, the function should subtract the argument value from the balance */
            balance -= withdrawAmnt;
        }

        virtual void closeAcc() {
            // A virtual function to close a bank account.
            closeFlag = true;
        }

        void calcInt() {
            /* A function that updates the balance by calculating the daily interest earned
            by the account and adding this interest to the balance. This should be performed
            by the following formulas */

            dailyInterestRate = annualInterestRate / 365;
            dailyinterest = balance * dailyInterestRate;
            balance += dailyinterest;
        }

        // yearly charge may be used later
        void yearlyCharge() {
            /* A function that will subtract the yearly service charge from the balance.
            Yearly service charge must not be subtracted more than once in a given calendar year */
            yearChrg = true;
            balance -= annualServiceChrg;
        }
};

/*
// set the Annual Charge (may be used later)
void Account::setAnnualServiceChrg(int aServChrg) {
    annualServiceChrg = aServChrg;
}

void Account::setBalance(int newBalance) {
    balance = newBalance;
}

// Returns values of necessary members
string Account::getAccountNum() {
    return accountNum;
}

bool Account::getCloseFlag() {
    return closeFlag;
}

double Account::getBalance() {
    return balance;
}

double Account::getAnnualInterestRate() {
    return annualInterestRate;
}

double Account::getAnnualServiceChrg() {
    return annualServiceChrg;
}

// functions to change balance, close account, and mess with interest
void Account::deposit(double depositAmnt) {
    /* A virtual function that accepts an argument for the amount of the deposit.
    Eventually, the function should add the argument value to the account balance
    balance += depositAmnt;
}

void Account::withdraw(double withdrawAmnt) {
    /* A virtual function that accepts an argument for the amount of the withdrawal.
    Eventually, the function should subtract the argument value from the balance
    balance -= withdrawAmnt;
}

void Account::closeAcc() {
    // A virtual function to close a bank account.
    closeFlag = true;
}

void Account::calcInt() {
    /* A function that updates the balance by calculating the daily interest earned
    by the account and adding this interest to the balance. This should be performed
    by the following formulas

    dailyInterestRate = annualInterestRate / 365;
    dailyinterest = balance * dailyInterestRate;
    balance += dailyinterest;
}

// yearly charge may be used later
void Account::yearlyCharge() {
    /* A function that will subtract the yearly service charge from the balance.
    Yearly service charge must not be subtracted more than once in a given calendar year
    yearChrg = true;
    balance -= annualServiceChrg;
}*/
