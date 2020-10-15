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
        vector <int> date;

    public:

        Account(){}

        // constructor sets all the initial values
        Account(double initialBalance, double interestRate, string accNum) {
            /* Accepts arguments for the initial balance, an annual interest rate, and a
            unique account number */
            balance = initialBalance;
            annualInterestRate = interestRate;
            accountNum = accNum;
            date = getTime();
        }

        Account(double initialBalance, double interestRate, string accNum, bool closeFlg) {
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

        void setBalance(double newBalance) {
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

        // Converts string to vector
        vector <string> stringToVector(string line){
            //Turns string into vector

            vector <string> lineList;
            string buffer;
            stringstream ss(line);

            while (getline(ss, buffer, ' ')){
                lineList.push_back(buffer);
            }
            return lineList;
        }
        

        vector <int> getTime() {
            // gets current time
            string timeAndDate, strMonth;
            int month, day, year;
            vector <int> date;

            auto time = std::chrono::system_clock::now();
            std::time_t end_time = std::chrono::system_clock::to_time_t(time);
            timeAndDate = std::ctime(&end_time);

            vector <string> vectorTime = stringToVector(timeAndDate);

            vectorTime.erase(vectorTime.begin());
            vectorTime.erase(vectorTime.begin() + 2);

            for (int i = 0; i < vectorTime.size(); i++) {
                cout << vectorTime[i] << endl;
            }

            strMonth = vectorTime[0];
            day = stoi(vectorTime[1].substr(0, 2));
            year = stoi(vectorTime[2].substr(0, 4));

            // month
            if (strMonth == "Jan") {
                month = 1;
            }
            else if (strMonth == "Feb") {
                month = 2;
            }
            else if (strMonth == "Mar") {
                month = 3;
            }
            else if (strMonth == "Apr") {
                month = 4;
            }
            else if (strMonth == "May") {
                month = 5;
            }
            else if (strMonth == "Jun") {
                month = 6;
            }
            else if (strMonth == "Jul") {
                month = 7;
            }
            else if (strMonth == "Aug") {
                month = 8;
            }
            else if (strMonth == "Sep") {
                month = 9;
            }
            else if (strMonth == "Oct") {
                month = 10;
            }
            else if (strMonth == "Nov") {
                month = 11;
            }
            else if (strMonth == "Dec") {
                month = 12;
            }

            date.push_back(month);
            date.push_back(day);
            date.push_back(year);

            return date;
    }
};

