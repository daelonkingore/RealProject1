/* Group members: Daelon Kingore M03120686, Ashton Barnwell M03234066 

The Checking class serves as the child class for Account. It puts the C in the account number, 
and overrides the virtual functions from the parent class. This class is used to withdraw and deposit money from and to a checkings account
Contains: private variables, 3 constructors to set the variables up, few setters and getters, and
override functions withdrawal and deposit. */

#include <string>
using namespace std;
// Room class declaration.
class Checking : public Account {
    private:
        string flag = "";
    public:

        Checking(){}

        Checking(double initialBalance, double interestRate, string accNum):Account(initialBalance, interestRate, accNum){
            accountNum = "C" + accountNum;
        }

        Checking(double initialBalance, double interestRate, string accNum, string riskFlag, bool closeFlg, vector <int> createDate, vector <int> lastAccess):Account(initialBalance, interestRate, accNum, closeFlg, createDate, lastAccess){
            accountNum = "C" + accountNum;
            flag = riskFlag;
        }

        void withdrawal(double amount){
            if (balance <= 0){
                cout << "This account has insufficient funds, withdrawal request denied." << endl;
            }
            else{
                if ((balance - amount) < 0){
                    cout << "Non-sufficient funds a charge of $25 will be made to this account" << endl;

                    if ((balance - 25) < 0){
                        balance -= 25;
                        cout << "After $25 insufficient fund charge was made to this account, balance is now "
                        << getBalance() << " account is now considered HIGH RISK!" << endl;
                        flag = "*";
                    }

                    else{
                        balance -= 25;
                    }
                }
                else {
                    balance -= amount;
                }
            }
        }

        void deposit(double amount){
            if (amount > 9999){
                cout << "Attention\n" << "This account is now considered HIGH RISK\n" << endl;
                flag = "*";
            }
            balance += amount;
        }

        string getAccountNum(){
            return flag + accountNum;
        }

        string getAN(){
            return accountNum;
        }

        string getFlag() {
            return flag;
        }

        void setFlag(string newFlag){
            flag = newFlag;
        }
};
