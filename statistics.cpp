#include <iostream>
#include "../headers/customer_lists.h"
#include "../headers/employee.h"
using namespace std;

int numberOfLoans(const customerList& l,loanList list) {
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = list.head;
		while (current1) {
			s = s + 1;
			current1 = current1->next;
		}
		current = current->next;
	}
	return s;
}

int loansType(const customerList& l,string type,loanList list){
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = list.head;
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

int loansStatus(const customerList& l, string status, loanList list) {
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = list.head;
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
	for (int i = 0; i <2 ; i++) {
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

int activeLoans(const customerList& l, string start, string end,loanList list) {
	int s = 0;
	customerNode* current = l.head;
	while (current) {
		LoanNode* current1 = list.head;
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

customer highestNbLoans(const customerList& l , loanList list) {
	customerNode* current = l.head;
	customer Max = current->data;
	int maxLoans = 0;
	while (current) {
		int s = 0;
		LoanNode* current1 = list.head;
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

int numberOfEmployees(const EmployeeArray& l) {
	return l.size;
}

int numEmployeesByBranch(EmployeeArray& l, int branch) {
	int s = 0;
	int i = 0;
	while(i<l.size){
		if(l.employees->branchCode[i] == branch){
			s=s+1;
		}
		i=i+1;
	}
	return s;
}