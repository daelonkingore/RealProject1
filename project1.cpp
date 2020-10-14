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

// controls the program
int main() {
    //vector <client> bank;
    string x;
    //string adminPass = "1234";
    //double bankRate = 0;

    /*
    cout << "***BANK SETUP PLEASE ENTER ADMIN PASSWORD***" << endl;
    cin >> x;
    if (x == adminPass){
        cout << "Welcome to bank setup!" << endl;
        while (bankRate > 10 || bankRate < 0.1){
            cout << "Please enter the bank's interest rate.\n*Note rate but be smaller than 10% but greater than 0.1%" << endl;
            cin >> bankRate;
        }
    }*/
    cout << "Enter a bank file." << endl;
    while(true){
        cin >> x;
        try{
            readBankFile(x);
            break;
        }
        catch(...){
            cout << "Invalid bank file try again..." << endl;
        }
    }

    while(true){
        cout << "Please Enter a Command.\n[1] New Account\n[2] Access Existing Account\n[3] Exit" << endl;

        cin >> x;
        if (x == "1"){
            client newClient;
            createAccounts(newClient);
        }
        else if (x == "2"){
            accessAccount();
            /*bank[0].savAcc.withdraw(50);
            cout << bank[0].savAcc.getBalance() << endl;*/
        }
        else if (x == "3"){
            cout << "Goodbye!" << endl;
            break;
        }
        else{
            cout << "Invalid Input try again..." << endl;
        }
    }
    return 0;
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
    string inputAccNum;
    string savNum;
    string checkNum;
    int clientNum;

    cout << "Please input your Checking or Savings account number: ";
    cin >> inputAccNum;

    // Check if account number == existing num
    if (inputAccNum.substr(0, 1) == "S") {
        // savings
        for (int i = 0; i < bank.size(); i++) {
            if (stoi(inputAccNum.substr(1, inputAccNum.length())) == stoi(bank[i].savAcc.getAccountNum().substr(1, bank[i].savAcc.getAccountNum().length()))) {
                inputAccNum = savNum;
                clientNum = i;
            }
        }
    }

    else if (inputAccNum.substr(0, 1) == "C") {
        // checking
        for (int i = 0; i < bank.size(); i++) {
            if (stoi(inputAccNum.substr(1, inputAccNum.length())) == stoi(bank[i].chkAcc.getAccountNum().substr(1, bank[i].chkAcc.getAccountNum().length()))) {
                inputAccNum = checkNum;
                clientNum = i;
            }
        }
    }

    else {
        cout << "Account number invalid, try again." << endl;
        accessAccount();
    }

    if (inputAccNum == savNum)
        accessSavings(clientNum);

    else if ( inputAccNum == checkNum) 
        accessChecking(clientNum);
}

void accessSavings(int clientNum){
    int choice;
    int depositAmm;
    int withdrawAmm;

    do {
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        cout << "[1] Deposit\n"
        << "[2] Withdraw\n"
        << "[3] Check Balance\n"
        << "[4] Go back" << endl;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        
        if (choice != 1 and choice != 2 and choice != 3 and choice != 4) {
            cout << "Enter 1, 2, 3, or 4." << endl;
            accessAccount();
        }
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
        case 4:
        {
            int choice2 = 0;
            while (choice2 != 1 and choice2 != 2) {
                if (bank[clientNum].savAcc.getBalance() < 1) {
                    cout << "ALERT in Savings accountA" << bank[clientNum].savAcc.getAccountNum() << ":\n"
                    << " causes the account to shut down permanently unless more money deposited.\n"
                    << "[1] Continue and close account?\n" 
                    << "[2] Deposit\n";
                    cin >> choice2;

                    if (choice2 == 1) {
                        cout << "Closing account permanently." << endl;
                        bank[clientNum].savAcc.closeAcc();
                        main();
                    }

                    if (choice2 == 2) {
                        cout << "Enter deposit amount: " << endl;
                        cin >> depositAmm;
                        bank[clientNum].savAcc.deposit(depositAmm);
                        main();
                    }
                }
                else {
                    choice2 = 1;
                    main();
                }
            }
        }
        }
    }
    while (choice != 4);
}

void accessChecking(int clientNum) {
    int choice;
    int depositAmm;
    int withdrawAmm;

    do {
        cout << "[1] Deposit\n"
        << "[2] Withdraw\n"
        << "[3] Check Balance\n"
        << "[4] Go back" << endl;
        cin >> choice;

        if (choice != 1 and choice != 2 and choice != 3 and choice != 4){
            cout << "Enter 1, 2, 3, or 4." << endl;
            accessAccount();
        }

        switch (choice) 
        {
        case 1: // deposit
            cout << "Enter deposit amount: " << endl;
            cin >> depositAmm;
            bank[clientNum].chkAcc.deposit(depositAmm);
        case 2: // withdraw
        {
            cout << "Enter withdraw amount: " << endl;
            cin >> withdrawAmm;
            bank[clientNum].chkAcc.withdrawal(withdrawAmm);
        }
        case 3: // check balance
            bank[clientNum].chkAcc.getBalance();
        case 4:
            main();
        default:
            cout << "Error" << endl;
            accessAccount();
        }
    }
    while (choice != 4);
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
    cout << accNum << endl;
    while(find(begin(numList), end(numList), accNum) != end(numList)){
        accNum = to_string(newAccNum());
    }
    numList.push_back(accNum);

    for (int i = 0; i < numList.size(); i++){
        cout << numList[i] << endl;
    }

    cout << "Please enter an initial balance for your new SAVINGS account.\n*Note a minimum initial balance of 50 is required." << endl;
    while(initBal < 50){
        cin >> initBal;
    }
    c.savAcc = Savings(initBal, bankRate, accNum);
    cout << "New SAVINGS account created.\nYour account number for this account is " << c.savAcc.getAccountNum() << endl;


    initBal = 0;
    cout << "Please enter an initial balance for your new CHECKING account.\n*Note a minimum initial balance of 1 is required." << endl;
    while(initBal < 1){
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
            bankRate = stod(line[1]);
        }

        else if (line[0] == "Account"){ //Gets account information from file
            numList.push_back(line[1]);
            client newClient;

            vector <string> accLine = stringToVector(file[i+1]);

            bool stat;
            if (accLine[2] == "false"){
                stat = false;
            }
            else{
                stat = true;
            }

            bool clsFlg;
            if (accLine[3] == "false"){
                clsFlg = false;
            }
            else{
                clsFlg = true;
            }

            newClient.savAcc = Savings(stod(accLine[1]), bankRate, line[1], stat, clsFlg);

            accLine = stringToVector(file[i+2]);

            if(accLine[2] == "empty"){
                accLine[2] = "";
            }

            if (accLine[2] == "false"){
                clsFlg = false;
            }
            else{
                clsFlg = true;
            }
            newClient.chkAcc = Checking(stod(accLine[1]), bankRate, line[1], accLine[2], clsFlg);

            bank.push_back(newClient);
        }
    }

}
