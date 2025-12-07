#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "customer_activities.h"

// customer - core account holder data structure
// - Uses pointer-based collections defined in customer_activities.h
// - Does not pull in `using namespace std;` to avoid polluting includers.
struct customer {
    std::string acc_num;
    std::string acc_type;
    std::string iban;
    std::string branch_code;
    std::string name;
    std::string opening_date;
    std::string status;
    float balance;
    loanList loans;
    tranStack transactions;
};

#endif // CUSTOMER_H