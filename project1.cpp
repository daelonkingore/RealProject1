/* Group members: Daelon Kingore M03120686, Ashton Barnwell M03234066 */

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <chrono>
#include <ctime>
#include "account.h"
#include "savings.h"
#include "checking.h"

using namespace std;

// Global Variables for interest rate and account numbers.
vector <string> numList;
double bankRate = 0;

// Individual client structure
struct client{
    Savings savAcc;
    Checking chkAcc;

    client(){
    }
};

// Global bank variable
vector <client> bank;

// Prototypes
vector <string> readFromFile(string file);
vector <string> stringToVector(string line);
void accessChecking(int clientNum);
void accessSavings(int clientNum);
void accessAccount();
int newAccNum();
void createAccounts(client c);
void readBankFile(string fileName);
vector <int> getTime();
void infoToFile(string fileName);
vector <int> formatDate(string date);

// controls the program
int main() {
    string fileName, input;
    while(true){
        cout << "Enter a bank file." << endl;
        cin >> fileName;
        try{
            readBankFile(fileName);
            break;
        }
        catch(...){
            cout << "Invalid bank file try again..." << endl;
        }
    }

    while(true){
        cout << "Please Enter a Command.\n[1] New Account\n[2] Access Existing Account\n[3] Exit" << endl;

        cin >> input;
        if (input == "1"){
            client newClient;
            createAccounts(newClient);
        }
        else if (input == "2"){
            accessAccount();
        }
        else if (input == "3"){
            cout << "Goodbye!" << endl;
            break;
        }
        else{
            cout << "Invalid bank file try again..." << endl;
        }
    }
    infoToFile(fileName);
    return 0;
}

vector <int> formatDate(string date) {
    /* Takes the date from the file and seperates it wherever the / is found.
    Puts the separated day and year into a vector and returns the vector.
    
    Contains: vector */
    int day, year;
    vector <int> theDate;

    day = stoi(date.substr(0, date.find("/")));
    year = stoi(date.substr(date.find("/") + 1, 4));

    theDate.push_back(day);
    theDate.push_back(year);
    return theDate;
}

// Converts input file to vector
vector <string> readFromFile(string file){
    //This function is used to read from the user inputed file
    string text;
    ifstream inFile;
    vector <string> fileLineList;

    inFile.open(file);

    if (inFile){
        while (getline(inFile, text)){
            fileLineList.push_back(text);
        }
    }

    else{
        throw "no file error";
    }

    cout << "newFile complete." << endl;

    inFile.close();

    return fileLineList;

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

// Used to access accounts
void accessAccount() {
    /* Asks the user for an account number and determines if the account is for savings or checking.
    It then either calls the accessSavings function or accessChecking function. Otherwise, invalid input. */

    string inputAccNum;
    string savNum;
    string checkNum;
    int clientNum;
    bool workFlag = false;

    cout << "Please input your Checking or Savings account number: ";
    cin >> inputAccNum;

    // Check if inputed account number is equal to an existing account number
    if (inputAccNum.substr(0, 1) == "S") {
        // if it is savings
        try {
            for (int i = 0; i < bank.size(); i++) {
                    if (bank[i].savAcc.getCloseFlag() == false && stoi(inputAccNum.substr(1, inputAccNum.length())) == stoi(bank[i].savAcc.getAccountNum().substr(1, bank[i].savAcc.getAccountNum().length()))) {
                    // above if statement is just testing the number part of the inputed account number against the existing one
                    clientNum = i;
                    workFlag = true;
                    accessSavings(clientNum);
                }
            }
            if (workFlag == false) {
                cout << "Account number invalid or closed, try again." << endl;
                accessAccount();
            }
        }
        catch(...) {
            cout << "Account number invalid or closed, try again." << endl;
            accessAccount();
        }
    }

    else if (inputAccNum.substr(0, 1) == "C") {
        // checking
        try {
            for (int i = 0; i < bank.size(); i++) {
                if (bank[i].chkAcc.getCloseFlag() == false && stoi(inputAccNum.substr(1, inputAccNum.length())) == stoi(bank[i].chkAcc.getAN().substr(1, bank[i].chkAcc.getAN().length()))) {
                    // above if statement is just testing the number part of the inputed account number against the existing one
                    clientNum = i;
                    workFlag = true;
                    accessChecking(clientNum);
                }
            }
            if (workFlag == false) {
                cout << "Account number invalid or closed, try again." << endl;
                accessAccount();
            }
        }
        catch(...) {
            cout << "Account number invalid or closed, try again." << endl;
            accessAccount();
        }
    }

    else {
        cout << "Account number invalid or closed, try again." << endl;
        accessAccount();
    }
}

void accessSavings(int clientNum){
    /* Asks the user to either deposit, withdraw, check their balance, or go back.
    Deposit, withdraw, and check balance calls are all within a switch statement, and simply
    call their respective class functions. For going back, the function first makes sure
    the user knows if their balance is below $1 the account will close.

    Contains: switch statment, while loops, if and else statments*/

    int choice;
    double depositAmm;
    double withdrawAmm;

    // loop until user inputs to go back
    while (choice != 4) {
        cout << "Welcome! User: " << bank[clientNum].savAcc.getAccountNum() << endl;
        cout << "[1] Deposit\n"
        << "[2] Withdraw\n"
        << "[3] Check Balance\n"
        << "[4] Go back" << endl;
        cin >> choice;

        // make sure input is 1, 2, 3, or 4
        if (choice != 1 and choice != 2 and choice != 3 and choice != 4) {
            cout << "Enter 1, 2, 3, or 4." << endl;
            accessAccount();
        }

        // user chooses to deposit, withdraw, or check balance
        switch (choice)
        {
        case 1: // deposit
            cout << "Enter deposit amount: " << endl;
            cin >> depositAmm;
            bank[clientNum].savAcc.deposit(depositAmm);
            break;
        case 2: // withdraw
        {
            cout << "Enter withdraw amount: " << endl;
            cin >> withdrawAmm;
            bank[clientNum].savAcc.withdraw(withdrawAmm);
            break;
        }
        case 3: // check balance
            cout << bank[clientNum].savAcc.getBalance() << endl;
            break;
        }
    }

    // if the user chose to go back
    if (choice == 4) {
        int choice2 = 0;
        while (choice2 != 1 and choice2 != 2) {
            if (bank[clientNum].savAcc.getBalance() < 1) { // if the balance is lower than $1, warn the user
                cout << "ALERT\n"
                << "The account will shut down permanently unless more money deposited.\n"
                << "[1] Continue and close account?\n"
                << "[2] Deposit\n";
                cin >> choice2;

                // if the user chooses to close account
                if (choice2 == 1) {
                    cout << "Closing account permanently." << endl;
                    bank[clientNum].savAcc.closeAcc();
                    break;
                }

                // if the user chooses to deposit
                if (choice2 == 2) {
                    cout << "Enter deposit amount: " << endl;
                    cin >> depositAmm;
                    bank[clientNum].savAcc.deposit(depositAmm);
                    break;
                }
            }

            else { // breaks out of accessing account
                choice2 = 1;
                break;
            }
        }
    }
}

void accessChecking(int clientNum) {
    /* Asks the user to either deposit, withdraw, check their balance, or go back.
    Calls respective class functions. For going back, the while loop will check
    if the inputed value is 4, and just stop.

    Contains: switch statment, while loop, if statment*/

    int choice;
    double depositAmm;
    double withdrawAmm;

    // loops until user inputs 4
    while (choice != 4) {
        cout << "Welcome! User: " << bank[clientNum].chkAcc.getAccountNum() << endl;
        cout << "[1] Deposit\n"
        << "[2] Withdraw\n"
        << "[3] Check Balance\n"
        << "[4] Go back" << endl;
        cin >> choice;

        // make sure input is 1, 2, 3, or 4
        if (choice != 1 and choice != 2 and choice != 3 and choice != 4){
            cout << "Enter 1, 2, 3, or 4." << endl;
            accessAccount();
        }

        // user chooses to deposit, withdraw, or check balance
        switch (choice)
        {
        case 1: // deposit
            cout << "Enter deposit amount: " << endl;
            cin >> depositAmm;
            bank[clientNum].chkAcc.deposit(depositAmm);
            break;
        case 2: // withdraw
        {
            cout << "Enter withdraw amount: " << endl;
            cin >> withdrawAmm;
            bank[clientNum].chkAcc.withdrawal(withdrawAmm);
            break;
        }
        case 3: // check balance
            cout << bank[clientNum].chkAcc.getBalance() << endl;
            break;
        }
    }
}

// Generates a random number
int newAccNum(){
    int accNum;
    srand (time(NULL));
    accNum = rand() % 5000 + 1000;
    return accNum;
}

// Creates a new checking and saving account
void createAccounts(client c){
    double initBal = 0;
    string accNum;

    cout << "Creating new accounts...\nEntering new account setup.\n\n";
    accNum = to_string(newAccNum());
    while(find(begin(numList), end(numList), accNum) != end(numList)){
        accNum = to_string(newAccNum());
    }
    numList.push_back(accNum);

    while(initBal < 50){
        cout << "Please enter an initial balance for your new SAVINGS account.\n*Note a minimum initial balance of 50 is required." << endl;
        cin >> initBal;
    }
    c.savAcc = Savings(initBal, bankRate, accNum);
    cout << "New SAVINGS account created.\nYour account number for this account is " << c.savAcc.getAccountNum() << endl;


    initBal = 0;
    while(initBal < 1){
        cout << "Please enter an initial balance for your new CHECKING account.\n*Note a minimum initial balance of 1 is required." << endl;
        cin >> initBal;
    }
    c.chkAcc = Checking(initBal, bankRate, accNum);
    cout << "New CHECKING account created.\nYour account number for this account is " << c.chkAcc.getAccountNum() << endl;

    bank.push_back(c);
}

// Reads the base file for the bank
void readBankFile(string fileName){

    vector <string> file = readFromFile(fileName);

    for(int i = 0; i < file.size(); i++){
        vector <string> line = stringToVector(file[i]);

        if (line[0] == "Rate"){ //Gets bank rate from file
            if(stod(line[1]) >= 0.1 && stod(line[1]) <= 10){
                bankRate = stod(line[1]);
            }
            else{
                throw "badFile";
            }
        }

        else if (line[0] == "Account"){ //Gets account information from file
            numList.push_back(line[1]);
            client newClient;
            vector <string> accLine = stringToVector(file[i+1]);

            bool stat;
            if (accLine[2] == "false"){
                stat = false;
            }
            else if (accLine[2] == "true"){
                stat = true;
            }
            else{
                throw "badFile";
            }

            bool clsFlg;
            if (accLine[3].substr(0, 5) == "false"){
                clsFlg = false;
            }
            else if(accLine[3].substr(0, 4) == "true"){
                clsFlg = true;
            }
            else{
                throw "badFile";
            }

            vector <int> createDate = formatDate(accLine[4]);
            vector <int> lastAccess = formatDate(accLine[5]);

            newClient.savAcc = Savings(stod(accLine[1]), bankRate, line[1], stat, clsFlg, createDate, lastAccess);

            accLine = stringToVector(file[i+2]);

            if(accLine[2] == "empty"){
                accLine[2] = "";
            }

            else if (accLine[2] != "*"){
                throw "badFile";
            }

            if (accLine[3].substr(0, 5) == "false"){
                clsFlg = false;
            }
            else if(accLine[3].substr(0, 4) == "true"){
                clsFlg = true;
            }
            else{
                throw "badFile";
            }

            createDate = formatDate(accLine[4]);
            lastAccess = formatDate(accLine[5]);

            newClient.chkAcc = Checking(stod(accLine[1]), bankRate, line[1], accLine[2], clsFlg, createDate, lastAccess);

            bank.push_back(newClient);
        }
    }
}

void infoToFile(string fileName){
    ofstream delOutFile(fileName, ofstream::trunc);
    delOutFile.close();

    ofstream outFile (fileName, ofstream::app);

    outFile << "Rate " << bankRate << "\n";

    for (int clnt = 0; clnt < bank.size(); clnt++){
        string aNum = bank[clnt].savAcc.getAccountNum().substr(1,4);

        string stat, flg, cFlag;
        vector <int> date, lastAccess;

        if (bank[clnt].savAcc.getStatus()){
            stat = "true";
        }
        else{
            stat = "false";
        }

        if(bank[clnt].chkAcc.getFlag() == "*"){
            flg = "*";
        }
        else{
            flg = "empty";
        }

        if (bank[clnt].savAcc.getCloseFlag()){
            cFlag = "true";
        }
        else{
            cFlag = "false";
        }
        date = bank[clnt].savAcc.getDate();
        lastAccess = bank[clnt].savAcc.getLastAccess();

        outFile << "Account " << bank[clnt].savAcc.getAccountNum().erase(0,1) << "\n";
        outFile << "S" << aNum << " " << bank[clnt].savAcc.getBalance() << " " << stat << " " << cFlag << " " << date[0] << "/" << date[1] << " " << lastAccess[0] << "/" << lastAccess[1] << "\n";

        if (bank[clnt].chkAcc.getCloseFlag()){
            cFlag = "true";
        }
        else{
            cFlag = "false";
        }

        date = bank[clnt].chkAcc.getDate();
        lastAccess = bank[clnt].chkAcc.getLastAccess();
        outFile << "C" << aNum << " " << bank[clnt].chkAcc.getBalance() << " " << flg << " " << cFlag << " " << date[0] << "/" << date[1] << " " << lastAccess[0] << "/" << lastAccess[1] << "\n";

    }
    outFile.close();
}
