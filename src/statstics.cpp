#include <iostream>
#include "../headers/statstics.h"
using namespace std;

int numberOfLoans(const customerList& l) {
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = loanList.head;
		while (current1) {
			s = s + 1;
			current1 = current1->next;
		}
		current = current->next;
	}
	return s;
}

int loansType(const customerList& l, string type) {
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = loanList.head;
		while (current1) {
			if (current1->data.type == type) {
				s = s + 1;
			}
			current1 = current1->next;
		}
		current = current->next;
	}
	return s;
}

int loansStatus(const customerList& l, string status) {
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = loanList.head;
		while (current1) {
			if (current1->data.status == status) {
				s = s + 1;
			}
			current1 = current1->next;
		}
		current = current->next;
	}
	return s;
}

bool compareDates(string s1, string s2) {
	string date1 = "";
	string date2 = "";
	for (int i = 0; i < 2; i++) {
		date1 = s1.substr(0, s1.find("/")) + "/" + date1;
		date2 = s2.substr(0, s2.find("/")) + "/" + date2;
		s1 = s1.substr(s1.find("/") + 1);
		s2 = s2.substr(s2.find("/") + 1);
	}
	date1 = s1 + "/" + date1;
	date2 = s2 + "/" + date2;
	date1 = date1.substr(0, date1.size() - 1);
	date2 = date2.substr(0, date2.size() - 1);
	if (date1.substr(0, date1.find("/")) != date2.substr(0, date2.find("/"))) {
		return date1.substr(0, date1.find("/")) < date2.substr(0, date2.find("/"));
	}
	date1 = date1.substr(date1.find("/") + 1);
	date2 = date2.substr(date2.find("/") + 1);
	string m1 = date1.substr(0, date1.find("/"));
	string m2 = date2.substr(0, date2.find("/"));
	if (m1 != m2) {
		if (m1.size() != m2.size()) {
			if (m1.size() < m2.size()) {
				m1 = "0" + m1;
			}
			else {
				m2 = "0" + m2;
			}
		}
		return m1 < m2;
	}
	date1 = date1.substr(date1.find("/") + 1);
	date2 = date2.substr(date2.find("/") + 1);
	if (date1 != date2) {
		if (date1.size() != date2.size()) {
			if (date1.size() < date2.size()) {
				date1 = "0" + date1;
			}
			else {
				date2 = "0" + date2;
			}
		}
		return date1 < date2;
	}
}

int activeLoans(const customerList& l, string start, string end) {
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = loanList.head;
		while (current1) {
			if (current1->data.status == "active") {
				if (compareDates(start, current1->data.start) && compareDates(current1->data.end, end)) {
					s = s + 1;
				}
			}
			current1 = current1->next;
		}
		current = current->next;
	}
	return s;
}

customer highestNbLoans(const customerList& l) {
	customerNode* current = l.head;
	customer Max = current->data;
	int maxLoans = 0;
	while (current) {
		int s = 0;
		LoanNode* current1 = loanList.head;
		while (current1) {
			s = s + 1;
			current1 = current1->next;
		}
		if (maxLoans < s) {
			maxLoans = s;
			Max = current->data;
		}
	}
	return Max;
}

customer highestBalance(const customerList& l) {
	customerNode* current = l.head;
	customer Max = current->data;
	float maxBalance = current->data.balance;
	current = current->next;
	while (current) {
		if (current->data.balance > maxBalance) {
			Max = current->data;
		}
	}
	return Max;
}

customer lowestBalance(const customerList& l) {
	customerNode* current = l.head;
	customer Low = current->data;
	float minBalance = current->data.balance;
	current = current->next;
	while (current) {
		if (current->data.balance < minBalance) {
			Low = current->data;
		}
	}
	return Low;
}

int numberOfEmployees(const EmployeeArray& arr) {
	return arr.size;
}

int numEmployeesByBranch(const EmployeeArray& arr, string branch) {
	int s = 0;
	int i = 0;
	while (i < arr.size) {
		if (arr.employees->branchCode[i] == branch) {
			s = s + 1;
		}
		i = i + 1;
	}
	return s;
}

void statstics()
{
	string options[9] = { "Number of Loans","Number of Loans by Type","Number of Loans by Status",
		"Customer with Highest Number of Loans","Customer with Highest Balance",
		"Customer with Lowest Balance","Number of Active Loans in Date Range","Number of Employees",
		"Number of Employees by Branch" };
	printOptions(options, 9);
	customerList custs = parseCustomers();
	EmployeeArray emps = loadEmployeesFromFile("../data/employees.json");
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Total number of loans: " << numberOfLoans(custs) << endl;
		break;
	case 2:
	{
		string type;
		cout << "Enter loan type: ";
		cin >> type;
		cout << "Number of loans of type " << type << ": " << loansType(custs, type) << endl;
		break;
	}
	case 3:
	{
		string status;
		cout << "Enter loan status: ";
		cin >> status;
		cout << "Number of loans with status " << status << ": " << loansStatus(custs, status) << endl;
		break;
	}
	case 4:
	{
		customer cust = highestNbLoans(custs);
		cout << "Customer with highest number of loans: " << cust.name << " (Account#: " << cust.acc_num << ")" << endl;
		break;
	}
	case 5:
	{
		customer cust = highestBalance(custs);
		cout << "Customer with highest balance: " << cust.name << " (Account#: " << cust.acc_num << ", Balance: " << cust.balance << ")" << endl;
		break;
	}
	case 6:
	{
		customer cust = lowestBalance(custs);
		cout << "Customer with lowest balance: " << cust.name << " (Account#: " << cust.acc_num << ", Balance: " << cust.balance << ")" << endl;
		break;
	}
	case 7:
	{
		string start, end;
		cout << "Enter start date (DD/MM/YYYY): ";
		cin >> start;
		cout << "Enter end date (DD/MM/YYYY): ";
		cin >> end;
		cout << "Number of active loans between " << start << " and " << end << ": " << activeLoans(custs, start, end) << endl;
		break;
	}
	case 8: {
		cout << "Total number of employees: " << numberOfEmployees(emps) << endl;
		break;
	}
	case 9:
	{
		string branch;
		cout << "Enter branch code: ";
		cin >> branch;
		cout << "Number of employees in branch " << branch << ": " << numEmployeesByBranch(emps, branch) << endl;
		break;
	}
	}
