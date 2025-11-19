#include "../headers/helpers.h"
#include "../headers/customer_lists.h"
#include "fstream"
using namespace std;
void clearScreen() {
#ifdef _WIN32 // For Windows
    system("cls");
#else // For Unix-based systems (Linux, macOS)
    system("clear");
#endif
}

void printLine(string text){
    for (int i = 0 ; i < 100 ; i++) cout << '-'; cout << endl;
    cout << "\t\t\t\t\t\t"<<text <<endl;
    for (int i = 0 ; i < 100 ; i++) cout << '-'; cout << endl;

}






////////////////////// FILE PARSING ///////////////////////////

string parseKey(const char *&c)
{
    string key;
    while(*c != '"')
    {
        key =+ *c;
        c++;
    }
    return key;
};
string parseStringValue(const char *&c){
    string value;
    while(*c != '"')
    {
        value =+ *c;
        c++;
    }
    c++;
    return value;
}

float parseFloatValue(const char *&c){
    string value;
    while(*c != ',')
    {
        value =+ *c;
        c++;
    }
    // convert string to float
    return std::stof(value);
};


loanList parseLoans(const char *&c)
{
  loanList loans;
  string key;
  while(c)
      {
          if(*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') c++;
          if(*c == '{')
          {
              Loan object; // KIFKIF (chouf louta)
              while(*c != '}')
                  {
                      if(*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') c++;
                      if(*c == '"')
                      {
                          key = parseKey(*&c);
                          if (key == "id") object.id = parseStringValue(*&c);
                          if (key == "type") object.type = parseStringValue(*&c);
                          if (key == "remain_balance") object.remain_balance = parseFloatValue(*&c);
                          if (key == "amount") object.amount = parseFloatValue(*&c);
                          if (key == "start") object.start = parseStringValue(*&c);
                          if (key == "end") object.end = parseStringValue(*&c);
                          if (key == "status") object.status = parseStringValue(*&c);

                      }
                      addLoan(loans,object);
                      c++;
                  }
          }
          c++;
      }
  return loans;


};

tranStack parseTrans(const char *&c)
{
  tranStack stack;
  string key;
  while(c)
      {
          if(*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') c++;
          if(*c == '{')
          {
              tran object; // KIFKIF (chouf louta)
              while(*c != '}')
                  {
                      if(*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') c++;
                      if(*c == '"')
                      {
                          key = parseKey(*&c);
                          if (key == "acc_num") object.acc_num = parseStringValue(*&c);
                          if (key == "id") object.id = parseStringValue(*&c);
                          if (key == "type") object.type = parseStringValue(*&c);
                          if (key == "amount") object.amount = parseFloatValue(*&c);
                          if (key == "date") object.date = parseStringValue(*&c);
                          if (key == "undone")
                            {
                                string undone = parseStringValue(*&c);
                                if (undone == "false") object.undone = false;
                                else object.undone = true;
                            }
                      }
                      addTran(stack,object);
                      c++;
                  }
          }
          c++;
      }
  return stack;
};


customerList  parse(const char*c)
{
    customerList customers;
    string key;
    while(c)
        {
            if(*c == ' ') c++;
            if(*c == '{')
            {
                customer object; // MBA3ED KI TZIDOU A3ML NEW CUSTOMER fel liste w 7ot fih el we7din
                while(*c != '}')
                    {
                        if(*c == ' ' || *c == '\n' || *c == '\t' || *c == '\r' || *c == ',') c++;
                        if(*c == '"')
                        {
                            key = parseKey(*&c);
                            if (key == "acc_num") object.acc_num = parseStringValue(*&c);
                            if (key == "acc_type") object.acc_type = parseStringValue(*&c);
                            if (key == "iban") object.iban = parseStringValue(*&c);
                            if (key == "branch_code") object.branch_code = parseStringValue(*&c);
                            if (key == "name") object.name = parseStringValue(*&c);
                            if (key == "status") object.status = parseStringValue(*&c);
                            if (key == "balance") object.balance = parseFloatValue(*&c);
                            if (key == "loans") object.loans = parseLoans(*&c);
                            if (key == "transaction") object.transactions = parseTrans(*&c) ;
                            c++;
                        }

                        c++;
                    }
                addCustomer(customers,object) ;// TODO
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
    string buffer((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
    const char *c = buffer.c_str();
    customers = parse(c);

    // UNDONE , TODO
    return customers;
}
