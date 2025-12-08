#include "employee_list.h"
#include "customer_lists.h"
#include <string>

int numberOfLoans(const customerList& l);
int loansType(const customerList& l, string type);
int loansStatus(const customerList& l, string status);
bool compareDates(string s1, string s2);
customer highestNbLoans(const customerList& l);
customer highestBalance(const customerList& l);
customer lowestBalance(const customerList& l);
int activeLoans(const customerList& l, string start, string end);
int numberOfEmployees(const EmployeeArray& l);
int numEmployeesByBranch(const EmployeeArray& l, string branch);
void statistics();
