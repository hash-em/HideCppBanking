#include "customer_activities.h"

int numberOfLoans(const customerList& l);
int loansType(const customerList& l, string type);
int loansStatus(const customerList& l, string status);
bool compareDates(string s1, string s2);
customer highestNbLoans(const customerList& l);
customer highestBalance(const customerList& l);
customer lowestBalance(const customerList& l);
int activeLoans(const customerList& l, string start, string end);
int numberOfEmployees(const employeeList& l);
int numEmployeesByBranch(const employeeList& l, string branch);

a