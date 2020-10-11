#include <string>
using namespace std;

// Room class declaration.
class Savings : public Account {
    private:
        bool status = true;
        bool permanentShutDown = false;

    public: 
        void withdraw(int);
        void deposit(int);
};

void Savings::withdraw(int withdrawAmnt) {
    if (status == true and permanentShutDown == false) {
        if (getBalance() - withdrawAmnt < 50) {
            cout << "Alert - Savings account: " << getAccountNum() 
            << " withdraw amount going below $50, $5 service charge applied. " 
            << "Deactivating account until above $50. No more withdraws may be" 
            << " made until above $50." << endl;
            status = false;
            withdrawAmnt += 5;
        }

        if (getBalance() - withdrawAmnt < 0) {
            cout << "Requested withdraw amount cause balance below $0. Request denied." << endl;
        }
        
        if (getBalance() - withdrawAmnt < 1 and withdrawAmnt >= 0) {
            cout << "ALERT - withdraw for Savings account: " << getAccountNum() 
            << " causes the account to shut down permanently. " << endl;
            permanentShutDown = true;
        }

        if (getBalance() - withdrawAmnt >= 50) {
            cout << "Withdrawing: " << withdrawAmnt << endl;
            setBalance(getBalance() - withdrawAmnt);
            cout << "New balance: " << getBalance() << endl;
        }
    }

    else if (status == false and permanentShutDown == false) {
        cout << "No withdraw's allowed until balance is about $50. " << endl;
    }

    else if (permanentShutDown = true) {
        cout << "This account has been permanently closed. " << endl;
    }
}

void Savings::deposit(int depositAmnt) {
    cout << "Depositing: " << depositAmnt << endl;
    setBalance(getBalance() + depositAmnt);
    cout << "New balance: " << getBalance() << endl;
}