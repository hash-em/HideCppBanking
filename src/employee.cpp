#include "../headers/employee.h"
#include "../headers/employeearr.h"
#include <iostream>
#include <fstream>
#include <algorithm>

EmployeeArray createEmployeeArray() {
    EmployeeArray arr;
    arr.capacity = 10;
    arr.size = 0;
    arr.employees = new Employee[arr.capacity];
    return arr;
}

void resizeEmployeeArray(EmployeeArray& arr) {
    int newCapacity = arr.capacity * 2;
    Employee* newEmployees = new Employee[newCapacity];
    for (int i = 0; i < arr.size; i++) {
        newEmployees[i] = arr.employees[i];
    }
    delete[] arr.employees;
    arr.employees = newEmployees;
    arr.capacity = newCapacity;
}

void addEmployee(EmployeeArray& arr, const Employee& emp) {
    // Check if ID already exists
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == emp.id) {
            cout << "Error: Employee ID already exists!" << endl;
            return;
        }
    }

    if (arr.size >= arr.capacity) {
        resizeEmployeeArray(arr);
    }

    arr.employees[arr.size] = emp;
    arr.size++;
    cout << "Employee added successfully!" << endl;
}

bool deleteEmployee(EmployeeArray& arr, const string& id) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == id) {
            // Shift elements to remove the employee
            for (int j = i; j < arr.size - 1; j++) {
                arr.employees[j] = arr.employees[j + 1];
            }
            arr.size--;
            cout << "Employee deleted successfully!" << endl;
            return true;
        }
    }
    cout << "Error: Employee not found!" << endl;
    return false;
}

bool modifyEmployee(EmployeeArray& arr, const string& id, const Employee& newData) {
    for (int i = 0; i < arr.size; i++) {
        if (arr.employees[i].id == id) {
            arr.employees[i] = newData;
            cout << "Employee modified successfully!" << endl;
            return true;
        }
    }
    cout << "Error: Employee not found!" << endl;
    return false;
}

void displayEmployeesAlphabetical(const EmployeeArray& arr) {
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    // Create a temporary array for sorting
    Employee* temp = new Employee[arr.size];
    for (int i = 0; i < arr.size; i++) {
        temp[i] = arr.employees[i];
    }

    // Bubble sort by last name
    for (int i = 0; i < arr.size - 1; i++) {
        for (int j = 0; j < arr.size - i - 1; j++) {
            if (temp[j].lastName > temp[j + 1].lastName) {
                Employee tempEmp = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = tempEmp;
            }
        }
    }

    cout << "Employees sorted by last name:" << endl;
    for (int i = 0; i < arr.size; i++) {
        cout << "ID: " << temp[i].id
            << ", Name: " << temp[i].name
            << " " << temp[i].lastName
            << ", Branch: " << temp[i].branchCode << endl;
    }

    delete[] temp;
}

void displayEmployeesByBranch(const EmployeeArray& arr) {
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    cout << "Employees grouped by branch:" << endl;

    // Simple grouping by branch
    for (int i = 0; i < arr.size; i++) {
        string currentBranch = arr.employees[i].branchCode;
        bool branchPrinted = false;

        // Check if we already printed this branch
        for (int j = 0; j < i; j++) {
            if (arr.employees[j].branchCode == currentBranch) {
                branchPrinted = true;
                break;
            }
        }

        if (!branchPrinted) {
            cout << "\nBranch " << currentBranch << ":" << endl;
            for (int k = 0; k < arr.size; k++) {
                if (arr.employees[k].branchCode == currentBranch) {
                    cout << "  - " << arr.employees[k].name
                        << " " << arr.employees[k].lastName
                        << " (ID: " << arr.employees[k].id << ")" << endl;
                }
            }
        }
    }
}

void displayEarliestLatestEmployees(const EmployeeArray& arr) {
    if (arr.size == 0) {
        cout << "No employees to display!" << endl;
        return;
    }

    int earliestIndex = 0;
    int latestIndex = 0;

    for (int i = 1; i < arr.size; i++) {
        if (arr.employees[i].hireDate < arr.employees[earliestIndex].hireDate) {
            earliestIndex = i;
        }
        if (arr.employees[i].hireDate > arr.employees[latestIndex].hireDate) {
            latestIndex = i;
        }
    }

    cout << "Earliest recruited employee:" << endl;
    cout << "ID: " << arr.employees[earliestIndex].id
        << ", Name: " << arr.employees[earliestIndex].name
        << " " << arr.employees[earliestIndex].lastName
        << ", Hire Date: " << arr.employees[earliestIndex].hireDate << endl;

    cout << "Most recently recruited employee:" << endl;
    cout << "ID: " << arr.employees[latestIndex].id
        << ", Name: " << arr.employees[latestIndex].name
        << " " << arr.employees[latestIndex].lastName
        << ", Hire Date: " << arr.employees[latestIndex].hireDate << endl;
}

void saveEmployeesToFile(const EmployeeArray& arr, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file for writing!" << endl;
        return;
    }

    for (int i = 0; i < arr.size; i++) {
        file << arr.employees[i].id << ","
            << arr.employees[i].name << ","
            << arr.employees[i].lastName << ","
            << arr.employees[i].address << ","
            << arr.employees[i].salary << ","
            << arr.employees[i].hireDate << ","
            << arr.employees[i].branchCode << "\n";
    }

    file.close();
    cout << "Employees saved to file successfully!" << endl;
}

EmployeeArray loadEmployeesFromFile(const string& filename) {
    EmployeeArray arr = createEmployeeArray();
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "No existing employee file found. Starting fresh." << endl;
        return arr;
    }

    string line;
    while (getline(file, line)) {
        Employee emp;
        size_t pos = 0;
        size_t lastPos = 0;

        // Parse CSV line
        pos = line.find(',', lastPos);
        emp.id = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.name = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.lastName = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.address = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.salary = stod(line.substr(lastPos, pos - lastPos));

        lastPos = pos + 1;
        pos = line.find(',', lastPos);
        emp.hireDate = line.substr(lastPos, pos - lastPos);

        lastPos = pos + 1;
        emp.branchCode = line.substr(lastPos);

        addEmployee(arr, emp);
    }

    file.close();
    cout << "Employees loaded from file successfully!" << endl;
    return arr;
}
