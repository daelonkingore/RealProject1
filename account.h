/* Group members: Daelon Kingore M03120686, Ashton Barnwell M03234066 */

#include <string>
using namespace std;

class Account {

    protected:
        string accountNum;
        double balance;
        double annualInterestRate;
        double annualServiceChrg = 5;
        double dailyInterestRate;
        double dailyInterest;
        bool closeFlag = false;
        vector <int> date;
        vector <int> lastAccessDate;

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
            lastAccessDate = getTime();
            closeFlag = false;
        }

        Account(double initialBalance, double interestRate, string accNum, bool closeFlg, vector <int> createDate, vector <int> lastAccess) {
            /* Accepts arguments for the initial balance, an annual interest rate, and a
            unique account number */
            balance = initialBalance;
            annualInterestRate = interestRate/100;
            accountNum = accNum;
            closeFlag = closeFlg;
            date = createDate;
            lastAccessDate = lastAccess;
            calcInt();
        }

        // setters for some of the protected variables
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

        vector <int> getDate() {
            return date;
        }

        vector <int> getLastAccess() {
            return lastAccessDate;
        }

        // functions to change balance, close account, and mess with interest
        virtual void deposit(double depositAmnt) {
            /* A virtual function that accepts an argument for the amount of the deposit.
            Eventually, the function should add the argument value to the account balance */
            balance += depositAmnt;
        }

        virtual void withdraw(double withdrawAmnt) {
            /* A virtual function that accepts an argument for the amount of the withdrawal. */
            balance -= withdrawAmnt;
        }

        virtual void closeAcc() {
            // A virtual function to close a bank account.
            closeFlag = true;
        }

        void calcInt() {
            /* A function that updates the balance. Checks how far ahead the access date is, 
            adds the calculated interest into balance. 
            
            Contains: vector, if and else statments, for loops */
            vector <int> accessDate = getTime();
            int year, days;

            dailyInterestRate = annualInterestRate / 365;
            dailyInterest = balance * dailyInterestRate;

            // if the access date year is bigger than the previous access date
            if (accessDate[1] > lastAccessDate[1]) {
                year = accessDate[1] - lastAccessDate[1];
                if (accessDate[0] == lastAccessDate[0]) { // if accessing on the same day a year later
                    for (int i = 0; i < year; i++) {
                        balance += (balance * annualInterestRate);
                    }
                }
                else { // otherwise, calculate how many days more
                    days = 365 - lastAccessDate[1];
                    days += 365 * (year - 1);
                    days += accessDate[1];
                    for (int i = 0; i < days; i++) {
                        dailyInterest = balance * dailyInterestRate;
                        balance += dailyInterest;
                    }
                }
            }
            else { // If the access date is not bigger than a year, find how many more days
                if (accessDate[0] > lastAccessDate[0]) {
                    days = accessDate[0] - lastAccessDate[0];
                    for (int i = 0; i < days; i++) {
                        dailyInterest = balance * dailyInterestRate;
                        balance += dailyInterest;
                    }
                }
            }
            lastAccessDate = getTime();
        }

        // yearly charge may be used later
        void yearlyCharge() {
            /* A function that will subtract the yearly service charge from the balance. */
        /*    vector <int> accessDate = getTime();

            if(accessDate[2] > date[2] && accessDate[1] > date[1] && accessDate[0] > date[0]){
                if(lastYearlyCharge < accessDate[2]){
                    balance -= annualServiceChrg;
                }
            }*/
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
            /* Gets the time and date from the computer and put it into a vector, erases
            useless parts, turns the date into numbers and put into date vector.
            Returns the date vector.

            Contains: use of ctime and chrono, if and if else statements, vectors */

            string timeAndDate, strMonth;
            int month, day, year;
            vector <int> date;

            // gets the date and time information from computer
            auto time = std::chrono::system_clock::now();
            std::time_t end_time = std::chrono::system_clock::to_time_t(time);
            timeAndDate = std::ctime(&end_time);

            // puts that info into a vector using stringToVector
            vector <string> vectorTime = stringToVector(timeAndDate);

            // get rid of the useless parts
            vectorTime.erase(vectorTime.begin());
            vectorTime.erase(vectorTime.begin() + 2);

            // turns numbers into ints (except for strMonth)
            strMonth = vectorTime[0];
            day = stoi(vectorTime[1].substr(0, 2));
            year = stoi(vectorTime[2].substr(0, 4));

            // if statements determining the number value correlating to the month name
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

            int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            while (month-- > 0) {
                day = day + daysPerMonth[month - 1];
            }

            // puts the final info into date vector
            date.push_back(day);
            date.push_back(year);

            return date;
    }
};

