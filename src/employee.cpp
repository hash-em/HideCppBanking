#include <iostream>
#include "../headers/employee_list.h"
#include <fstream>
#include <sstream>
using namespace std;

employeeList employees;

employeeList newEmployeeList() {
    employeeList list;
    list.head = nullptr;
    list.size = 0;
    return list;
}

void addEmployee(employeeList& list, Employee emp) {
    Employee* node = new Employee;
    node->id = emp.id;
    node->firstName = emp.firstName;
    node->lastName = emp.lastName;
    node->address = emp.address;
    node->salary = emp.salary;
    node->hireDate = emp.hireDate;
    node->branchCode = emp.branchCode;
    node->next = nullptr;
    if (!list.head) {
        list.head = node;
    } else {
        Employee* temp = list.head;
        while (temp->next) temp = temp->next;
        temp->next = node;
    }
    list.size++;
}

bool deleteEmployee(employeeList& list, int id) {
    if (!list.head) return false;
    Employee* curr = list.head;
    Employee* prev = nullptr;
    if (curr->id == id) {
        list.head = curr->next;
        delete curr;
        list.size--;
        return true;
    }
    while (curr && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return false;
    prev->next = curr->next;
    delete curr;
    list.size--;
    return true;
}

bool modifyEmployee(employeeList& list, int id) {
    Employee* emp = findEmployeeById(list, id);
    if (!emp) return false;
    cout << "New First Name: ";
    cin >> emp->firstName;
    cout << "New Last Name: ";
    cin >> emp->lastName;
    cout << "New Address: ";
    cin.ignore();
    getline(cin, emp->address);
    cout << "New Salary: ";
    cin >> emp->salary;
    cout << "New Hire Date (YYYY-MM-DD): ";
    cin >> emp->hireDate;
    cout << "New Branch Code: ";
    cin >> emp->branchCode;
    return true;
}

void displayEmployeesAlphabetically(const employeeList& list) {
    if (!list.head) {
        cout << "No employees.\n";
        return;
    }
    Employee* arr[1000];
    Employee* temp = list.head;
    int n = 0;
    while (temp && n < 1000) {
        arr[n++] = temp;
        temp = temp->next;
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j]->lastName > arr[j+1]->lastName) {
                Employee* t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
    cout << "\n=== Alphabetical by Last Name ===\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i]->id << " | " << arr[i]->firstName << " " << arr[i]->lastName
             << " | " << arr[i]->salary << " | " << arr[i]->branchCode << " | " << arr[i]->hireDate << "\n";
    }
}

void displayEmployeesByBranch(const employeeList& list) {
    if (!list.head) return;
    Employee* arr[1000];
    Employee* temp = list.head;
    int n = 0;
    while (temp && n < 1000) {
        arr[n++] = temp;
        temp = temp->next;
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j]->branchCode > arr[j+1]->branchCode) {
                Employee* t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
        }
    }
    string cur = "";
    for (int i = 0; i < n; i++) {
        if (arr[i]->branchCode != cur) {
            cur = arr[i]->branchCode;
            cout << "\n--- Branch " << cur << " ---\n";
        }
        cout << "  " << arr[i]->id << " | " << arr[i]->firstName << " " << arr[i]->lastName << "\n";
    }
}

void displayEarliestAndLatest(const employeeList& list) {
    if (!list.head) return;
    Employee* earliest = list.head;
    Employee* latest = list.head;
    Employee* temp = list.head->next;
    while (temp) {
        if (temp->hireDate < earliest->hireDate) earliest = temp;
        if (temp->hireDate > latest->hireDate) latest = temp;
        temp = temp->next;
    }
    cout << "Earliest: " << earliest->firstName << " " << earliest->lastName << " (" << earliest->hireDate << ")\n";
    cout << "Latest: " << latest->firstName << " " << latest->lastName << " (" << latest->hireDate << ")\n";
}

Employee* findEmployeeById(const employeeList& list, int id) {
    Employee* temp = list.head;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void freeEmployeeList(employeeList& list) {
    Employee* cur = list.head;
    while (cur) {
        Employee* next = cur->next;
        delete cur;
        cur = next;
    }
    list.head = nullptr;
    list.size = 0;
}

void initEmployeeSystem() {
    employees = newEmployeeList();
    loadEmployeesFromFile();
}

void saveEmployeesToFile() {
    ofstream f("../data/employees.json");
    f << "[\n";
    Employee* p = employees.head;
    bool first = true;
    while (p) {
        if (!first) f << ",\n";
        first = false;
        f << "  {\"id\":" << p->id
          << ",\"firstName\":\"" << p->firstName
          << "\",\"lastName\":\"" << p->lastName
          << "\",\"address\":\"" << p->address
          << "\",\"salary\":" << p->salary
          << ",\"hireDate\":\"" << p->hireDate
          << "\",\"branchCode\":\"" << p->branchCode << "\"}";
        p = p->next;
    }
    f << "\n]\n";
    f.close();
}

void loadEmployeesFromFile() {
    ifstream f("../data/employees.json");
    if (!f.is_open()) return;
    stringstream buffer;
    buffer << f.rdbuf();
    string s = buffer.str();
    const char* c = s.c_str();
    while (*c && *c != '[') c++;
    if (*c == '[') c++;
    while (*c) {
        if (*c != '{') { c++; continue; }
        Employee emp;
        string key, val;
        while (*c && *c != '}') {
            if (*c != '"') { c++; continue; }
            c++;
            key = "";
            while (*c && *c != '"') key += *c++;
            c += 3;
            if (*c == '"') {
                c++;
                val = "";
                while (*c && *c != '"') val += *c++;
                c++;
            } else {
                val = "";
                while (*c && (*c == '.' || isdigit(*c) || *c == '-')) val += *c++;
            }
            if (key == "id") emp.id = stoi(val);
            else if (key == "firstName") emp.firstName = val;
            else if (key == "lastName") emp.lastName = val;
            else if (key == "address") emp.address = val;
            else if (key == "salary") emp.salary = stod(val);
            else if (key == "hireDate") emp.hireDate = val;
            else if (key == "branchCode") emp.branchCode = val;
            c++;
        }
        addEmployee(employees, emp);
        c++;
    }
    f.close();
}
