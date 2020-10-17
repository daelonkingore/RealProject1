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

        //Contructor for new clients
        Checking(double initialBalance, double interestRate, string accNum):Account(initialBalance, interestRate, accNum){
            accountNum = "C" + accountNum;
        }

        //Contructor for existing clients
        Checking(double initialBalance, double interestRate, string accNum, string riskFlag, bool closeFlg, vector <int> createDate, vector <int> lastAccess):Account(initialBalance, interestRate, accNum, closeFlg, createDate, lastAccess){
            accountNum = "C" + accountNum;
            flag = riskFlag;
        }

        //Function withdraws from the balance and checks for certain conditions
        void withdrawal(double amount){
            if (balance <= 0){ //Checks to see if the balance is already below zero
                cout << "This account has insufficient funds, withdrawal request denied." << endl;
            }
            else{
                if ((balance - amount) < 0){ //Checks to see if withdraw amount would make balance go below zero
                    cout << "Non-sufficient funds a charge of $25 will be made to this account" << endl;

                    if ((balance - 25) < 0){ //Checks to see if the insufficient fund charge would make the balance reach negative
                        balance -= 25;
                        cout << "After $25 insufficient fund charge was made to this account, balance is now "
                        << getBalance() << " account is now considered HIGH RISK!" << endl;
                        flag = "*"; //Changes flag so account is high risk
                    }

                    else{
                        balance -= 25; //If insufficient fund charge would not make balance go negative
                    }
                }
                else {
                    balance -= amount;
                }
            }
        }

        //Deposits to balance with some checks
        void deposit(double amount){
            if (amount > 9999){ //If deposit amount is above 9999 account becomes high risk 
                cout << "Attention\n" << "This account is now considered HIGH RISK\n" << endl;
                flag = "*";
            }
            balance += amount;
        }

        string getAccountNum(){ //Function used to get Account num with flag
            return flag + accountNum;
        }

        string getAN(){ //Function used to get account num without flag
            return accountNum;
        }

        string getFlag() { //Returns flag
            return flag;
        }

        void setFlag(string newFlag){ //Allows for the setting of the flag
            flag = newFlag;
        }
};
