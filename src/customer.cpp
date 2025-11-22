#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
#include "fstream"

int userInterface()
{
    clearScreen();
    // TODO
    return 1;
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

int submitNewLoan()
{
    //TODO (do addLoan(...,...) then write loan in files) for HASHEM
    return 1;
};

int withdraw(){
    //TODO
    return 1;
}

int deposit(){
    //TODO
    return 1;
}

int viewDay(){
    // TODO
    return 1;
}

int undoLast(){
    // TODO
    return 1;
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
                    else if (key == "type") object.type = parseStringValue(c);
                    else if (key == "remain_balance") object.remain_balance = parseFloatValue(c);
                    else if (key == "amount") object.amount = parseFloatValue(c);
                    else if (key == "start") object.start = parseStringValue(c);
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
                    else if (key == "undone")
                    {
                        string undone = parseStringValue(c);
                        object.undone = (undone != "false");
                    }
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
