#include <string>
using namespace std;
// Room class declaration.
class Checking : public Account {
    private:
        string flag = "";
    public:

        Checking(){}

        Checking(int initialBalance, int interestRate, string accNum):Account(initialBalance, interestRate, accNum){
            accountNum = "C" + accountNum;
        }

        Checking(int initialBalance, int interestRate, string accNum, string riskFlag, bool closeFlg):Account(initialBalance, interestRate, accNum, closeFlg){
            accountNum = "C" + accountNum;
            flag = riskFlag;
        }

        void withdrawal(int amount){
            if (balance <= 0){
                cout << "Account " << accountNum << " has insufficient funds, withdrawal request denied.";
            }
            else{
                if ((balance - amount) < 0){
                    cout << "non-sufficient funds a charge of $25 will be made to this account" << endl;

                    if ((balance - 25) < 0){
                        balance -= 25;
                        cout << "After $25 insufficient fund charge was made to account " << accountNum << " balance is now "
                        << balance << " account is now considered HIGH RISK!";
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

        void deposit(int amount){
            if (amount > 9999){
                cout << "Attention!\nAccount " << accountNum << " is now considered HIGH RISK!";
            }
            balance += amount;
        }

        string getAccountNum(){
            return flag + accountNum;
        }

};
