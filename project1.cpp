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
void infoToFile();

// controls the program
int main() {
    string x;
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
    infoToFile();
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
        cout << "SAVINGS" << endl;
        // savings
        for (int i = 0; i < bank.size(); i++) {
            if (bank[i].savAcc.getCloseFlag() == false && stoi(inputAccNum.substr(1, inputAccNum.length())) == stoi(bank[i].savAcc.getAccountNum().substr(1, bank[i].savAcc.getAccountNum().length()))) {
                clientNum = i;
                accessSavings(clientNum);
            }
            else {
                cout << "Account has been closed." << endl;
            }
        }
    }

    else if (inputAccNum.substr(0, 1) == "C") {
        cout << "Checkings" << endl;
        // checking
        for (int i = 0; i < bank.size(); i++) {
            if (bank[i].chkAcc.getCloseFlag() == false && stoi(inputAccNum.substr(1, inputAccNum.length())) == stoi(bank[i].chkAcc.getAccountNum().substr(1, bank[i].chkAcc.getAccountNum().length()))) {
                clientNum = i;
                cout << "inside checkings" << endl;
                accessChecking(clientNum);
            }
        }
    }

    else {
        cout << "Account number invalid or closed, try again." << endl;
        accessAccount();
    }
}

void accessSavings(int clientNum){
    int choice;
    double depositAmm;
    double withdrawAmm;

    while (choice != 4) {
        cout << "[1] Deposit\n"
        << "[2] Withdraw\n"
        << "[3] Check Balance\n"
        << "[4] Go back" << endl;
        cin >> choice;
        
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
        }
    }

    if (choice == 4) {
        int choice2 = 0;
        while (choice2 != 1 and choice2 != 2) {
            if (bank[clientNum].savAcc.getBalance() < 1) {
                cout << "ALERT\n"
                << "The account will shut down permanently unless more money deposited.\n"
                << "[1] Continue and close account?\n" 
                << "[2] Deposit\n";
                cin >> choice2;

                if (choice2 == 1) {
                    cout << "Closing account permanently." << endl;
                    bank[clientNum].savAcc.closeAcc();
                    break;
                }

                if (choice2 == 2) {
                    cout << "Enter deposit amount: " << endl;
                    cin >> depositAmm;
                    bank[clientNum].savAcc.deposit(depositAmm);
                    break;
                }
            }
            else {
                choice2 = 1;
                break;
            }
        }
    }
}

void accessChecking(int clientNum) {
    int choice;
    double depositAmm;
    double withdrawAmm;

    while (choice != 4) {
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
            if (accLine[3].substr(0, 5) == "false"){
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

            if (accLine[3].substr(0, 5) == "false"){
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

void infoToFile(){
    ofstream delOutFile("new.txt", ofstream::trunc);
    delOutFile.close();

    ofstream outFile ("new.txt", ofstream::app);

    outFile << "Rate " << bankRate << "\n";

    for (int clnt = 0; clnt < bank.size(); clnt++){
        string aNum = bank[clnt].savAcc.getAccountNum().substr(1,4);

        string stat;
        string flg;
        string cFlag;

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
        outFile << "Account " << bank[clnt].savAcc.getAccountNum().erase(0,1) << "\n";
        outFile << "S" << aNum << " " << bank[clnt].savAcc.getBalance() << " " << stat << " " << cFlag << "\n";

        if (bank[clnt].savAcc.getCloseFlag()){
            cFlag = "true";
        }
        else{
            cFlag = "false";
        }

        outFile << "C" << aNum << " " << bank[clnt].chkAcc.getBalance() << " " << flg << " " << cFlag << "\n";

    }
    outFile.close();
}    
