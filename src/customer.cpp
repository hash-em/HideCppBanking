#include "../headers/customer_lists.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

using namespace std;

int userInterface(customer &cust)
{

    if (cust.acc_num == "0") return 8;
    displayCustomer(cust);
    printLine("Options");
    int choice;
    string options[7] = {"View loans",
        "Submit new loan request",
        "View Daily Transactions",
        "Cancel Last Transaction",
        "Withdaw Money",
        "Deposit money",
        "logout"
    };
    printOptions(options, 7);
    cin >> choice;
    do{
        if (choice < 1 || choice > 7)
        {
            printLine("Invalid choice. Please enter 1-7");
            printOptions(options, 7);
            cin >> choice;
        }
    }while(choice < 1 || choice > 7);
    switch (choice) {
        case 1 :
        {
            viewLoans(cust);
            printLine("Loans ↑");
            break;
        }
        case 2 :
        {
            submitNewLoan(cust);
            printLine("Loan submitted for review");
            break;
        }
        case 3 :
        {
            viewDay(cust);
            printLine("Daily transactions ↑");
            break;
        }
        case 4 :
        {
            undoLast(cust);
            break;
        }
        case 5 :
        {
            withdraw(cust);
            break;
        }
        case 6 :
        {
            deposit(cust);
            break;
        }
        case 7 :
        {
            return 67;
        }


    }
    updateData(cust);
    int next = userInterface(cust);
    return next;
}

customerList newCustomerList(){
    return customerList{nullptr,0};
}
loanList newLoanList(){
    return loanList{nullptr,0};
}
tranStack newTranStack(){
    return tranStack{nullptr,0};
}

void addCustomer(customerList &customers , customer cust) // Hash
{
    customerNode * curr = customers.head;
    if (!curr)
    {
        customers.head = new customerNode{cust,nullptr};customers.size++;
        return;
    ;};
    while(curr->next) curr = curr->next;
    customerNode * new_c = new customerNode{cust,nullptr};
    curr->next = new_c;
    customers.size++;
};
void addLoan(loanList &loans , Loan loan) // Hash
{
    LoanNode * curr = loans.head;
    if (!curr)
    {
        loans.size++;
        loans.head = new LoanNode{loan,nullptr,nullptr};
        return;
    ;};
    while(curr->next) curr = curr->next;
    LoanNode * new_l = new LoanNode{loan,curr,nullptr};
    curr->next = new_l;
    loans.size++;
};
void addTran(tranStack &trans , tran transaction) // Hash
{
    tranNode * new_t = new tranNode{transaction,trans.last};
    trans.last = new_t;
    trans.size++;
};

int submitNewLoan(customer &cust)
{
    string type,id,start,end,status;
    float amount,remain;
    printLine("New loan submission");
    do{
        cout << "Loan type (car, home, student, business) : ";
        cin >> type;
        if(type != "car" && type != "home" && type != "student" && type != "business" )
            cout << "Invalid type. Please enter: car, home, student, or business\n";
    }while(type != "car" && type != "home" && type != "student" && type != "business" );
    do{
        cout << "Loan amount (must be positive) : ";
        cin >> amount;
        if(amount <= 0)
            cout << "Invalid amount. Please enter a positive number\n";
    }while(amount <= 0);
    do{
        cout << "Loan start date (YYYY-MM-DD) : ";
        cin >> start;
        if(start.length() != 10)
            cout << "Invalid date format. Use YYYY-MM-DD\n";
    }while(start.length() != 10);
    do{
        cout << "Loan end date (YYYY-MM-DD) : ";
        cin >> end;
        if(end.length() != 10)
            cout << "Invalid date format. Use YYYY-MM-DD\n";
    }while(end.length() != 10);
    status = "";
    id = "1x"+ to_string((abs(std::rand()*10000)%1000));
    remain = cust.balance - amount;
    Loan loan = {id,cust.acc_num,type,amount,remain,1,start,end,status};
    string content = "";
    string path = "../data/loans.json";
    ifstream file(path, ios::binary);
    if (!file.is_open()) return 1;
    string buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char *c = buffer.c_str();
    while(*(c+1) != ']')
    {
        content += *c;
        c++;
    }
    content += ("\n\t\t {"
        "\n\t\t\t  \"id\":\""+loan.id+'"'+','+
        "\n\t\t\t  \"acc_num\":\""+loan.acc_num+'"'+','+
        "\n\t\t\t  \"type\":\""+loan.type+'"'+','+
        "\n\t\t\t  \"amount\":"+to_string(loan.amount)+','+
        "\n\t\t\t  \"interest\":"+to_string(loan.interest)+','+
        "\n\t\t\t  \"remain_balance\":"+to_string(loan.remain_balance)+','+
        "\n\t\t\t  \"start\":\""+loan.start+'"'+','+
        "\n\t\t\t  \"end\":\""+loan.end+'"'+','+
        "\n\t\t\t  \"status\":\""+loan.status+'"'+
        "\n\t\t\t },"
    );
    while(*c) {
        content += *c;
        c++;
    }
    std::ofstream outf;
    outf.open("../data/loans.json");
    if (!outf.is_open())
    {
        cout << "Unable to write data , exiting with no save";
        return 1;
    }
    outf << content;
    outf.close();
    //addLoan(cust.loans, loan);
    //updateData(cust);
    return 0;
};

int withdraw(customer &cust){
    clearScreen();
    printLine("Select withdraw amount");
    string options[3] = {"10.0","20.0","50.0"};
    float amounts[3] = {10.0,20.0,50.0};
    printOptions(options, 3);
    int choice;
    do{
        cout << "Enter choice (1-3): ";
        cin >> choice;
        if(choice < 1 || choice > 3)
            cout << "Invalid option. Please enter 1, 2, or 3\n";
    }while (choice < 1 || choice > 3);

    if (amounts[choice-1] > cust.balance)
    {
        printLine("Not enough balance");
        return 0;
    }
    tran new_t = {"0x"+to_string(abs((std::rand())%10000)),cust.acc_num,"withdraw",amounts[choice-1],DateNow(),false};
    addTran(cust.transactions, new_t);
    cust.balance -= amounts[choice-1];
    printLine("Withdraw Transaction Approved");
    return 0;
}

int deposit(customer &cust){
        clearScreen();
        printLine("Input deposit amount");
        float amount;
        do {
            cout << "Enter amount (must be positive): ";
            cin >> amount;
            if(amount <= 0)
                cout << "Invalid amount. Please enter a positive number\n";
        }while (amount <= 0);
        tran new_t = {"0x"+to_string( abs((std::rand()*1000000)%10000)),cust.acc_num,"deposit",amount,DateNow(),false};
        addTran(cust.transactions, new_t);
        cust.balance += amount;
        printLine("Deposit Transaction Approved");
        return 0;

}

void displayCustomer(customer cust)
{
    cout << cust.acc_num+"|" + cust.name +
    "\nIban : "+ cust.iban+
    "\nBalance : " + to_string(cust.balance) << endl
    ;
};


void viewLoans(customer cust){
    clearScreen();
    LoanNode * curr = cust.loans.head;
    Loan loan;
    while(curr)
    {
        loan = curr->data;
        printLine("loan id : " +loan.id);
        cout <<"Type : " + loan.type +
        "\nacc_num : " + loan.acc_num +
        "\nAmount : " + to_string(loan.amount) +
        "\nRemaining balance : " + to_string(loan.remain_balance)   +
        "\ninterest : " + to_string(loan.interest) +
        "\nStart date : " + loan.start +
        "\nEnd date : " + loan.end +
        "\nStatus : " + loan.status  << endl;
       curr = curr->next;
    }

    // TODO
}


void viewDay(customer cust){
    clearScreen();
    tranStack trans = cust.transactions;
    tran tr;
    tranNode*curr = trans.last;
    string today = DateNow();

    if (!(curr && curr->data.date == today))
    {
        printLine("No transactions today");
    }
    while (curr && curr->data.date == today)
    {
        tr = curr->data;
        printLine("Transaction id : " +tr.id);
        cout <<
        "Account number : " + tr.acc_num +
        "\nType : " + tr.type +
        "\nAmount : " + to_string(tr.amount) +
        "\nDate : " + today
        << endl;
        curr = curr->prev;
    }
    return;
}

int undoLast(customer &cust){
    clearScreen();
    tranStack tr = cust.transactions;
    if(!tr.last)
    {
        printLine("Nothing done , no previous transaction");
        return 0;
    }
    float prev = cust.balance;
    if (tr.last->data.type == "withdraw")
    {
        cust.balance += tr.last->data.amount;
    }
    else {
        cust.balance -= tr.last->data.amount;
    }
    addUndone(tr.last->data);
    popTran(cust.transactions);
    printLine("Last transaction Undone ,Old balance : "+ to_string(prev) + ",New balance : "+to_string(cust.balance));
    return 0;
}
void addUndone(tran trans)
{
    string content = "";
    string path = "../data/undone.json";
    ifstream file(path, ios::binary);
    if (!file.is_open()) return;
    string buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char *c = buffer.c_str();
    while(*(c+1) != ']')
    {
        content += *c;
        c++;
    }
    content += ("\n\t\t {"
        "\n\t\t\t  \"id\":\""+trans.id+'"'+','+
        "\n\t\t\t  \"acc_num\":\""+trans.acc_num+'\"'+','+
        "\n\t\t\t  \"type\":\""+trans.type+'\"'+','+
        "\n\t\t\t  \"amount\":"+to_string(trans.amount)+','+
        "\n\t\t\t  \"date\":\""+trans.date+'"'+
        "\n\t\t\t },"
    );
    while(*c) {
        content += *c;
        c++;
    }
    std::ofstream outf;
    outf.open("../data/undone.json");
    if (!outf.is_open())
    {
        cout << "Unable to write data , exiting with no save";
        return;
    }
    outf << content;
    outf.close();

}
void popTran(tranStack &tr)
{
    if (!tr.last) {return;}
    if(!tr.last->prev)
    {
        tranNode *tmp = tr.last;
        tr.last = nullptr;
        delete tmp;
        tr.size--;
        return;
    }
    tranNode *tmp = tr.last;
    tr.last = tr.last->prev;
    tr.size--;
    delete tmp;
    return;
}


////////////////////// FILE PARSING ///////////////////////////

string parseKey(const char *&c)
{
    string key;
    c++;  // Skip opening "
    while (*c && *c != '"') {
        key += *c;
        c++;
    }
    if (*c == '"') c++;  // Skip closing "
    return key;
}

string parseStringValue(const char *&c)
{
    string value;
    c++; // Skip opening "
    while (*c && *c != '"') {
        value += *c;
        c++;
    }
    if (*c == '"') c++; // Skip closing "
    return value;
}

float parseFloatValue(const char *&c)
    {
    string value;
    while (*c && *c != ',' && *c != ']' && *c != '}' && *c != '\n' && *c != '\r' && *c != ' ') {
        value += *c;
        c++;
    }
    return std::stof(value);
}

loanList parseLoans(const char *&c)
{
    loanList loans = newLoanList();
    string key;

    while (*c)
    {
        if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') { c++; continue; }
        if (*c == ']') break;

        if (*c == '{')
        {
            Loan object;
            while (*c && *c != '}')
            {
                if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') { c++; continue; }
                if (*c == '"')
                {
                    key = parseKey(c);
                    c++; // Skip ':'

                    if (key == "id") object.id = parseStringValue(c);
                    else if (key == "acc_num") object.acc_num = parseStringValue(c);
                    else if (key == "type") object.type = parseStringValue(c);
                    else if (key == "remain_balance") object.remain_balance = parseFloatValue(c);
                    else if (key == "amount") object.amount = parseFloatValue(c);
                    else if (key == "start") object.start = parseStringValue(c);
                    else if (key == "interest") object.interest = parseFloatValue(c);
                    else if (key == "end") object.end = parseStringValue(c);
                    else if (key == "status") object.status = parseStringValue(c);
                }
                c++;
            }
            addLoan(loans, object);
        }
        c++;
    }
    return loans;
}

tranStack parseTrans(const char *&c)
{
    tranStack stack = newTranStack();
    string key;

    while (*c)
    {
        if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') { c++; continue; }
        if (*c == ']') break;

        if (*c == '{')
        {
            tran object;
            while (*c && *c != '}')
            {
                if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') { c++; continue; }
                if (*c == '"')
                {
                    key = parseKey(c);
                    c++; // Skip ':'

                    if (key == "acc_num") object.acc_num = parseStringValue(c);
                    else if (key == "id") object.id = parseStringValue(c);
                    else if (key == "type") object.type = parseStringValue(c);
                    else if (key == "amount") object.amount = parseFloatValue(c);
                    else if (key == "date") object.date = parseStringValue(c);
                }
                c++;
            }
            addTran(stack, object);
        }
        c++;
    }
    return stack;
}

customerList parse(const char *c)
{
    customerList customers = newCustomerList();
    string key;

    while (*c && *c != '[') c++;
    if (*c == '[') c++;

    while (*c)
    {
        if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') { c++; continue; }
        if (*c == ']') break;

        if (*c == '{')
        {
            customer object;
            while (*c && *c != '}')
            {
                if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') { c++; continue; }
                if (*c == '"')
                {
                    key = parseKey(c);
                    c++; // Skip ':'

                    if (key == "acc_num") object.acc_num = parseStringValue(c);
                    else if (key == "acc_type") object.acc_type = parseStringValue(c);
                    else if (key == "iban") object.iban = parseStringValue(c);
                    else if (key == "branch_code") object.branch_code = parseStringValue(c);
                    else if (key == "name") object.name = parseStringValue(c);
                    else if (key == "opening_date") object.opening_date = parseStringValue(c);
                    else if (key == "status") object.status = parseStringValue(c);
                    else if (key == "balance") object.balance = parseFloatValue(c);
                    else if (key == "loans") object.loans = parseLoans(c);
                    else if (key == "transactions") object.transactions = parseTrans(c);
                }
                c++;
            }
            addCustomer(customers, object);
        }
        c++;
    }

    return customers;
}

customerList parseCustomers()
{
    customerList customers = newCustomerList();
    string customer_path = "../data/customers.json";

    ifstream file(customer_path, ios::binary);
    if (!file.is_open()) return customers;

    string buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char *c = buffer.c_str();
    return parse(c);
}

loanList parseLoansFile()
{
    loanList loans = newLoanList();
    string loans_path = "../data/loans.json";

    ifstream file(loans_path, ios::binary);
    if (!file.is_open()) return loans;

    string buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char *c = buffer.c_str();
    
    // Find the "loans" array in the JSON
    while (*c && *c != '[') c++;
    
    if (*c == '[') {
        c++; // skip '['
        loans = parseLoans(c);
    }
    
    return loans;
}

//////////////////////////////// FILE DUMPING /////////////////////////////////////////
void updateData(customer cust)
{
    customerList customers = parseCustomers();
    customerNode*curr = customers.head;
    bool found = false;
    while(curr && !found)
    {
        if (curr->data.acc_num == cust.acc_num)
        {
            curr->data=cust;
            found = true;
        }
        curr = curr->next;
    }
    dumpCustomers(customers);
}


void dumpCustomers(customerList customers)
{
    std::ofstream outf;
    outf.open("../data/customers.json");
    if (!outf.is_open())
    {
        cout << "Unable to write data , exiting with no save";
        return;
    }
    customerNode*curr = customers.head;
    LoanNode* currLoan;
    customer cust;
    string tmp;
    string content = "{\n\t\"Customers\" :[";
    while(curr)
    {
        tmp = "";
        cust = curr->data;
        LoanNode* currLoan = cust.loans.head;
        tranNode* currTran = cust.transactions.last;
        tmp += ("\n\t {"
            "\n\t  \"acc_num\":\""+cust.acc_num+'"'+','+
            "\n\t  \"acc_type\":\""+cust.acc_type+'"'+','+
            "\n\t  \"iban\":\""+cust.iban+'"'+','+
            "\n\t  \"branch_code\":\""+cust.branch_code+'"'+','+
            "\n\t  \"name\":\""+cust.name+'"'+','+
            "\n\t  \"opening_date\":\""+cust.opening_date+'"'+','+
            "\n\t  \"status\":\""+cust.status+'"'+','+
            "\n\t  \"balance\":"+to_string(cust.balance)+','
        );
        tmp += "\n\t  \"loans\":[";
        while(currLoan)
            {
                Loan loan = currLoan->data;
                tmp += ("\n\t\t {"
                    "\n\t\t\t  \"id\":\""+loan.id+'"'+','+
                    "\n\t\t\t  \"acc_num\":\""+loan.acc_num+'"'+','+
                    "\n\t\t\t  \"type\":\""+loan.type+'"'+','+
                    "\n\t\t\t  \"amount\":"+to_string(loan.amount)+','+
                    "\n\t\t\t  \"interest\":"+to_string(loan.interest)+','+
                    "\n\t\t\t  \"remain_balance\":"+to_string(loan.remain_balance)+','+
                    "\n\t\t\t  \"start\":\""+loan.start+'"'+','+
                    "\n\t\t\t  \"end\":\""+loan.end+'"'+','+
                    "\n\t\t\t  \"status\":\""+loan.status+'"'+
                    "\n\t\t\t }"
                );
                if (currLoan->next) tmp += ',';
                currLoan = currLoan->next;
            }
        tmp += "\n\t\t ],";
        tmp += "\n\t  \"transactions\":[";
        while(currTran)
            {
                tran trans = currTran->data;
                tmp += ("\n\t\t {"
                    "\n\t\t\t  \"id\":\""+trans.id+'"'+','+
                    "\n\t\t\t  \"acc_num\":\""+trans.acc_num+'\"'+','+
                    "\n\t\t\t  \"type\":\""+trans.type+'\"'+','+
                    "\n\t\t\t  \"amount\":"+to_string(trans.amount)+','+
                    "\n\t\t\t  \"date\":\""+trans.date+'"' +
                    "\n\t\t\t }"
                );
                if (currTran->prev) tmp += ',';
                currTran = currTran->prev;
            }
        ;
        tmp += "\n\t\t  ]";
        tmp += "\n  \t}";
        if (curr->next) tmp += ',';
        content += tmp;
        curr = curr->next;
    }
    content += "\n ]\n}";
    outf << content;
    outf.close();
}
