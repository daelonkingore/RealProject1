/* Group members: Daelon Kingore M03120686, Ashton Barnwell M03234066

The Savings class serves as the child class for Account. It puts the S in the account number, 
and overrides the virtual functions from the parent class. This class is used to withdraw and deposit money from and to a Savings account
Contains: private variables, 3 constructors to set the variables up, a couple setters and getters, and
override functions withdrawal and deposit. */

#include <string>
using namespace std;

// Savings derived from Account class declaration.
class Savings : public Account {

private:
    bool status = true;
    double savingsInitialBalance;
    double savingsInterestRate;

public:
    // constructors setting the Savings values
    Savings(){}

    Savings(double initialBalance, double interestRate, string accNum) : Account(initialBalance, interestRate, accNum) {
        accountNum = "S" + accNum;
    }

    Savings(double initialBalance, double interestRate, string accNum, bool stat, bool closeFlg, vector <int> createDate, vector <int> lastAccess) : Account(initialBalance, interestRate, accNum, closeFlg, createDate, lastAccess) {
        status = stat;
        accountNum = "S" + accNum;
    }


    void withdraw(int withdrawAmnt) {
        /* Withdraws the inputed amount of money from the savings account. Checks if the account is active
        and not closed, then checks if the amount inputed will make the balance go below 50, below 1, or below 0.
        In those cases, prints correlating messages and performs actions accordingly. Otherwise, withdraws the 
        money normally.

        Contains a line of if statements and else if statements to get desired outcome. */

        // if the account isn't inactive or closed
        if (status == true && closeFlag == false) {
            if (getBalance() - withdrawAmnt < 0) {
                // if the withdraw amount input goes below 0, deny
                cout << "Requested withdraw amount cause balance to go below $0. Request denied." << endl;
            }

            else if ((balance - withdrawAmnt) == 0) {
                // if trying to withdraw all money
                cout << "Withdrawing all money will close the account, and a $5 service charge\n"
                << "will be applied. Remaining money will be withdrawn. \n" << endl;
                setBalance(0);
                status = false;
            }

            else if (getBalance() - withdrawAmnt < 50) {
                // else if it doesn't go below 0, but does go below 50, service charge
                cout << "Alert:\n"
                << "Withdraw causes balance to go below $50, $5 service charge applied.\n"
                << "Deactivating account until above $50. No more withdraws may be\n"
                << "made until balance is above $50.\n" << endl;
                status = false;
                setBalance(getBalance() - 5);

                if (getBalance() - withdrawAmnt < 0) {
                    // if the service charge causes balance below 0, deny withdraw
                    cout << "Requested withdraw amount plus service charge cause balance to go below $0.\n"
                    << "Withdraw will only withdraw until balance is $0.\n" << endl;
                    setBalance(0);
                }

                else {
                    setBalance(getBalance() - withdrawAmnt);
                }
            }

            else if (getBalance() - withdrawAmnt >= 50) {
                // else if savings account stays above 50, withdraw the amount normally
                cout << "Withdrawing: " << withdrawAmnt << endl;
                setBalance(getBalance() - withdrawAmnt);
                cout << "New balance: " << getBalance() << endl;
            }
        }

        else if (status == false and getCloseFlag() == false) {
            // if the account is inactive
            cout << "No withdraw's allowed until balance is about $50. \n" << endl;
        }
    }

    void deposit(int depositAmnt) {
        /* Deposits the inputed amount into savings. Also checks if the balance of savings
        is above 50, if it is, makes sure the status is true. */
        // deposit the amount into account
        cout << "Depositing: " << depositAmnt << endl;
        setBalance(getBalance() + depositAmnt);
        cout << "New balance: " << getBalance() << endl;
        if (getBalance() > 50) {
            status = true;
        }
    }

    void setStatus(bool s) {
        status = s;
    }

    bool getStatus(){
        return status;
    }
};
