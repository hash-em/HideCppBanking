"use strict";

//////////////////////////////////////////////////////////////////////////
// ELKHAZNA BANK - Complete Banking Management System

// Data Structures as per project requirements
const account1 = {
  id: "CUST001",
  owner: "Paul Fadayo",
  username: "pf",
  pin: 1111,

  // Account details
  account: {
    accountNumber: "ACC001",
    accountType: "Savings",
    IBAN: "TN59 1000 1001 1234 5678 9012",
    branchCode: "001",
    holderName: "Paul Fadayo",
    openingDate: "2022-08-20",
    status: "active",
    balance: 25000.75,
    currency: "TND",
    locale: "en-GB",
  },

  // Movements (transactions)
  movements: [200, 455.23, -306.5, 25000, -642.21, -133.9, 79.97, 1300],
  movementsDates: [
    "2022-08-20T21:31:17.178Z",
    "2022-08-23T07:42:02.383Z",
    "2022-08-28T09:15:04.904Z",
    "2022-09-13T10:17:24.185Z",
    "2022-09-14T14:11:59.604Z",
    "2022-09-15T17:01:17.194Z",
    "2022-09-16T23:36:17.929Z",
    "2022-09-17T10:51:36.790Z",
  ],
  interestRate: 1.2,

  // Loans (doubly linked list simulation)
  loans: [
    {
      loanID: "LOAN001",
      loanType: "car",
      principalAmount: 50000,
      interestRate: 5.5,
      amountPaid: 12500,
      remainingBalance: 37500,
      startDate: "2024-01-15",
      endDate: "2026-01-15",
      status: "active",
    },
    {
      loanID: "LOAN002",
      loanType: "home",
      principalAmount: 150000,
      interestRate: 4.2,
      amountPaid: 30000,
      remainingBalance: 120000,
      startDate: "2023-06-10",
      endDate: "2033-06-10",
      status: "active",
    },
  ],

  // Daily transactions stack (LIFO for undo)
  dailyTransactions: [
    {
      transactionID: "TXN001",
      type: "deposit",
      amount: 5000,
      date: "2025-12-10T09:30:00",
    },
    {
      transactionID: "TXN002",
      type: "withdrawal",
      amount: 1000,
      date: "2025-12-10T14:45:00",
    },
  ],
};

const account2 = {
  id: "CUST002",
  owner: "Guest Account",
  username: "ga",
  pin: 2222,

  account: {
    accountNumber: "ACC002",
    accountType: "Current",
    IBAN: "TN59 1000 1001 8765 4321 0987",
    branchCode: "002",
    holderName: "Guest Account",
    openingDate: "2022-08-28",
    status: "active",
    balance: 18500.3,
    currency: "TND",
    locale: "en-US",
  },

  movements: [5000, 3400, -150, -790.54, -3210, -1000, 8500, -30],
  movementsDates: [
    "2022-08-28T13:15:33.035Z",
    "2022-08-30T09:48:16.867Z",
    "2022-08-31T06:04:23.907Z",
    "2022-09-11T14:18:46.235Z",
    "2022-09-12T16:33:06.386Z",
    "2022-09-14T14:43:26.374Z",
    "2022-09-14T18:49:59.371Z",
    "2022-09-17T12:01:20.894Z",
  ],
  interestRate: 1.5,

  loans: [
    {
      loanID: "LOAN003",
      loanType: "student",
      principalAmount: 20000,
      interestRate: 3.5,
      amountPaid: 5000,
      remainingBalance: 15000,
      startDate: "2024-03-01",
      endDate: "2028-03-01",
      status: "active",
    },
  ],

  dailyTransactions: [],
};

// Employees array (as per project requirement)
const employees = [
  {
    id: "EMP001",
    username: "admin",
    password: "admin123",
    firstName: "Mohamed",
    lastName: "Ali",
    address: "Tunis, Tunisia",
    salary: 3500,
    hireDate: "2020-05-15",
    branchCode: "1",
    role: "head-office",
  },
  {
    id: "EMP002",
    username: "emp001",
    password: "emp001",
    firstName: "Sara",
    lastName: "Ben Ahmed",
    address: "Sousse, Tunisia",
    salary: 2800,
    hireDate: "2022-09-10",
    branchCode: "001",
    role: "branch-manager",
  },
  {
    id: "EMP003",
    username: "emp002",
    password: "emp002",
    firstName: "Ahmed",
    lastName: "Ben Salem",
    address: "Sfax, Tunisia",
    salary: 2500,
    hireDate: "2023-03-20",
    branchCode: "002",
    role: "teller",
  },
];

// Bank branches
const branches = [
  { code: "1", name: "Head Office", location: "Tunis" },
  { code: "001", name: "Tunis Central", location: "Tunis" },
  { code: "002", name: "Sousse Branch", location: "Sousse" },
  { code: "003", name: "Sfax Branch", location: "Sfax" },
];

// Loan requests queue (FIFO)
const loanRequests = [
  {
    requestID: "REQ001",
    customerID: "CUST001",
    customerName: "Paul Fadayo",
    loanType: "business",
    amount: 75000,
    requestDate: "2025-12-09",
    status: "pending",
  },
];

// Archived accounts array
const archivedAccounts = [];

// Completed loans list
const completedLoans = [];

// All customer accounts
const accounts = [account1, account2];

// Global variables
let currentAccount = null;
let currentEmployee = null;
let timer;

//////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS

// Format currency
const formatCur = function (value, locale = "en-US", currency = "TND") {
  return new Intl.NumberFormat(locale, {
    style: "currency",
    currency: currency,
  }).format(value);
};

// Format date
const formatDate = function (dateString) {
  const date = new Date(dateString);
  return new Intl.DateTimeFormat("en-US", {
    year: "numeric",
    month: "short",
    day: "numeric",
  }).format(date);
};

// Format movement date
const formatMovementDate = function (date, locale) {
  const calcDaysPassed = (date1, date2) =>
    Math.round(Math.abs(date2 - date1) / (1000 * 60 * 60 * 24));
  const daysPassed = calcDaysPassed(new Date(), date);

  if (daysPassed === 0) return "Today";
  if (daysPassed === 1) return "Yesterday";
  if (daysPassed <= 7) return `${daysPassed} days ago`;

  return new Intl.DateTimeFormat(locale).format(date);
};

// Generate usernames
const createUsernames = function (accounts) {
  accounts.forEach(function (acc) {
    acc.username = acc.owner
      .toLowerCase()
      .split(" ")
      .map(function (name) {
        return name[0];
      })
      .join("");
  });
};
createUsernames(accounts);

// Logout timer
const startLogOutTimer = function () {
  let time = 300; // 5 minutes

  const tick = function () {
    const min = String(Math.trunc(time / 60)).padStart(2, 0);
    const sec = String(time % 60).padStart(2, 0);

    // Update timer in both interfaces
    const custTimer = document.getElementById("custTimer");
    const empTimer = document.getElementById("empTimer");
    if (custTimer) custTimer.textContent = `${min}:${sec}`;
    if (empTimer) empTimer.textContent = `${min}:${sec}`;

    if (time === 0) {
      clearInterval(timer);
      logout();
    }

    time--;
  };

  tick();
  const timerId = setInterval(tick, 1000);
  return timerId;
};

// Logout function
const logout = function () {
  // Reset current account/employee
  currentAccount = null;
  currentEmployee = null;

  // Clear timer
  if (timer) clearInterval(timer);

  // Hide dashboards
  document.getElementById("customerDashboard").classList.add("hidden");
  document.getElementById("employeeDashboard").classList.add("hidden");

  // Show login section
  document.getElementById("loginSection").classList.remove("hidden");
  document.getElementById("heroSection").classList.remove("hidden");

  // Reset forms
  document.getElementById("customerLoginForm").reset();
  document.getElementById("employeeLoginForm").reset();
};

// Update current date and time
const updateCurrentDateTime = function () {
  const now = new Date();
  const dateStr = now.toLocaleDateString("en-US", {
    weekday: "long",
    year: "numeric",
    month: "long",
    day: "numeric",
  });
  const timeStr = now.toLocaleTimeString("en-US", {
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
  });

  // Update customer dashboard
  const custDateTime = document.getElementById("currentDateTime");
  if (custDateTime) {
    custDateTime.innerHTML = `<i class="fas fa-calendar-alt"></i> ${dateStr} | <i class="fas fa-clock"></i> ${timeStr}`;
  }

  // Update employee dashboard
  const empDateTime = document.getElementById("empDateTime");
  if (empDateTime) {
    empDateTime.innerHTML = `<i class="fas fa-calendar-alt"></i> ${dateStr} | <i class="fas fa-clock"></i> ${timeStr}`;
  }
};

// Scroll to login
const scrollToLogin = function () {
  document.getElementById("loginSection").scrollIntoView({
    behavior: "smooth",
  });
};

// Fill demo customer credentials
const fillCustomerDemo = function (username, pin) {
  document.getElementById("customerUsername").value = username;
  document.getElementById("customerPin").value = pin;
};

// Fill demo employee credentials
const fillEmployeeDemo = function (username, password) {
  document.getElementById("employeeUsername").value = username;
  document.getElementById("employeePassword").value = password;
};

//////////////////////////////////////////////////////////////////////////
// CUSTOMER INTERFACE FUNCTIONS

// Update customer dashboard
const updateCustomerDashboard = function (acc) {
  // Update welcome message
  document.getElementById("customerName").textContent = `Welcome, ${
    acc.owner.split(" ")[0]
  }`;

  // Update account info
  document.getElementById("custAccountNumber").textContent =
    acc.account.accountNumber;
  document.getElementById(
    "custAccountType"
  ).textContent = `${acc.account.accountType} Account`;
  document.getElementById("custBalance").textContent = formatCur(
    acc.account.balance,
    acc.locale,
    acc.currency
  );

  // Update statistics
  const incomes = acc.movements
    .filter((mov) => mov > 0)
    .reduce((sum, mov) => sum + mov, 0);
  const expenses = acc.movements
    .filter((mov) => mov < 0)
    .reduce((sum, mov) => sum + mov, 0);
  const interest = acc.movements
    .filter((mov) => mov > 0)
    .map((mov) => (mov * acc.interestRate) / 100)
    .filter((int) => int >= 1)
    .reduce((sum, int) => sum + int, 0);

  document.getElementById("totalIncome").textContent = formatCur(
    incomes,
    acc.locale,
    acc.currency
  );
  document.getElementById("totalExpense").textContent = formatCur(
    Math.abs(expenses),
    acc.locale,
    acc.currency
  );
  document.getElementById("totalInterest").textContent = formatCur(
    interest,
    acc.locale,
    acc.currency
  );
  document.getElementById("activeLoans").textContent = acc.loans.filter(
    (loan) => loan.status === "active"
  ).length;

  // Update account info in settings
  document.getElementById("accountFullName").textContent =
    acc.account.holderName;
  document.getElementById("accountNumber").textContent =
    acc.account.accountNumber;
  document.getElementById("accountIBAN").textContent = acc.account.IBAN;
  document.getElementById("accountType").textContent = acc.account.accountType;
  document.getElementById("accountBranch").textContent = acc.account.branchCode;
  document.getElementById("accountOpenDate").textContent = formatDate(
    acc.account.openingDate
  );

  // Display recent transactions
  displayRecentTransactions(acc);

  // Display loans
  displayCustomerLoans(acc);

  // Update current date and time
  updateCurrentDateTime();
};

// Display recent transactions
const displayRecentTransactions = function (acc) {
  const container = document.getElementById("recentTransactions");
  if (!container) return;

  container.innerHTML = "";

  // Get last 5 transactions
  const recentMovements = acc.movements.slice(-5).reverse();
  const recentDates = acc.movementsDates.slice(-5).reverse();

  if (recentMovements.length === 0) {
    container.innerHTML = `
      <div class="transaction-item">
        <div class="transaction-details">
          <div class="transaction-title">No transactions yet</div>
          <div class="transaction-date">-</div>
        </div>
        <div class="transaction-amount">0.00 TND</div>
      </div>
    `;
    return;
  }

  recentMovements.forEach((mov, i) => {
    const type = mov > 0 ? "deposit" : "withdrawal";
    const date = new Date(recentDates[i]);
    const displayDate = formatMovementDate(date, acc.locale);

    const html = `
      <div class="transaction-item ${type}">
        <div class="transaction-icon">
          <i class="fas fa-${
            type === "deposit" ? "arrow-down" : "arrow-up"
          }"></i>
        </div>
        <div class="transaction-details">
          <div class="transaction-title">${
            type === "deposit" ? "Money Deposited" : "Money Withdrawn"
          }</div>
          <div class="transaction-date">${displayDate}</div>
        </div>
        <div class="transaction-amount ${type}">
          ${type === "deposit" ? "+" : "-"}${formatCur(
      Math.abs(mov),
      acc.locale,
      acc.currency
    )}
        </div>
      </div>
    `;
    container.insertAdjacentHTML("beforeend", html);
  });
};

// Display customer loans
const displayCustomerLoans = function (acc) {
  const container = document.getElementById("loansContainer");
  if (!container) return;

  container.innerHTML = "";

  if (acc.loans.length === 0) {
    container.innerHTML = `
      <div class="empty-state">
        <i class="fas fa-money-bill-wave"></i>
        <h3>No Active Loans</h3>
        <p>You don't have any active loans at the moment.</p>
      </div>
    `;
    return;
  }

  acc.loans.forEach((loan) => {
    const progress = ((loan.amountPaid / loan.principalAmount) * 100).toFixed(
      1
    );
    const html = `
      <div class="loan-card">
        <div class="loan-header">
          <h4>${loan.loanType.toUpperCase()} LOAN</h4>
          <span class="loan-status ${loan.status}">${loan.status}</span>
        </div>
        <div class="loan-details">
          <div class="loan-info">
            <div class="loan-info-item">
              <span>Loan Amount:</span>
              <strong>${formatCur(loan.principalAmount)}</strong>
            </div>
            <div class="loan-info-item">
              <span>Remaining:</span>
              <strong>${formatCur(loan.remainingBalance)}</strong>
            </div>
            <div class="loan-info-item">
              <span>Interest Rate:</span>
              <strong>${loan.interestRate}%</strong>
            </div>
            <div class="loan-info-item">
              <span>Due Date:</span>
              <strong>${formatDate(loan.endDate)}</strong>
            </div>
          </div>
          <div class="loan-progress">
            <div class="progress-bar">
              <div class="progress-fill" style="width: ${progress}%"></div>
            </div>
            <div class="progress-text">${progress}% paid (${formatCur(
      loan.amountPaid
    )})</div>
          </div>
        </div>
      </div>
    `;
    container.insertAdjacentHTML("beforeend", html);
  });
};

// Show section in dashboard
const showSection = function (sectionId) {
  // Hide all sections
  const sections = document.querySelectorAll(".content-section");
  sections.forEach((section) => section.classList.remove("active"));

  // Remove active from all sidebar links
  const links = document.querySelectorAll(".sidebar-link");
  links.forEach((link) => link.classList.remove("active"));

  // Show selected section
  const targetSection = document.getElementById(`${sectionId}Section`);
  if (targetSection) {
    targetSection.classList.add("active");
  }

  // Activate corresponding sidebar link
  const targetLink = document.querySelector(
    `.sidebar-link[data-section="${sectionId}"]`
  );
  if (targetLink) {
    targetLink.classList.add("active");
  }
};

//////////////////////////////////////////////////////////////////////////
// CUSTOMER OPERATIONS

// Handle customer login - FIXED VERSION
const handleCustomerLogin = function () {
  console.log("Customer login clicked!");

  const username = document.getElementById("customerUsername").value;
  const pin = parseInt(document.getElementById("customerPin").value);

  console.log("Login attempt:", { username, pin });

  // Find account
  const account = accounts.find(
    (acc) =>
      (acc.username === username || acc.id === username) && acc.pin === pin
  );

  if (account) {
    console.log("Login successful for:", account.owner);
    currentAccount = account;

    // Hide hero and login sections
    document.getElementById("heroSection").classList.add("hidden");
    document.getElementById("loginSection").classList.add("hidden");

    // Show dashboard
    document.getElementById("customerDashboard").classList.remove("hidden");

    // Update dashboard
    updateCustomerDashboard(account);

    // Start logout timer
    if (timer) clearInterval(timer);
    timer = startLogOutTimer();

    // Clear form
    document.getElementById("customerLoginForm").reset();

    // Set active section
    showSection("overview");
  } else {
    alert(
      "Invalid username or PIN!\nTry:\nUsername: pf / PIN: 1111\nor\nUsername: ga / PIN: 2222"
    );
  }
};

// Handle employee login - FIXED VERSION
const handleEmployeeLogin = function () {
  console.log("Employee login clicked!");

  const username = document.getElementById("employeeUsername").value;
  const password = document.getElementById("employeePassword").value;

  console.log("Employee login attempt:", { username, password });

  // Find employee
  const employee = employees.find(
    (emp) => emp.username === username && emp.password === password
  );

  if (employee) {
    console.log("Employee login successful for:", employee.firstName);
    currentEmployee = employee;

    // Hide hero and login sections
    document.getElementById("heroSection").classList.add("hidden");
    document.getElementById("loginSection").classList.add("hidden");

    // Show dashboard
    document.getElementById("employeeDashboard").classList.remove("hidden");

    // Update employee dashboard
    updateEmployeeDashboard(employee);

    // Start logout timer
    if (timer) clearInterval(timer);
    timer = startLogOutTimer();

    // Clear form
    document.getElementById("employeeLoginForm").reset();

    // Set active section
    showEmployeeSection("emp-dashboard");
  } else {
    alert(
      "Invalid username or password!\nTry:\nUsername: admin / Password: admin123\nor\nUsername: emp001 / Password: emp001"
    );
  }
};

// Handle transfer
const handleTransfer = function () {
  if (!currentAccount) return;

  const receiverUsername = document.getElementById("transferTo").value;
  const amount = parseFloat(document.getElementById("transferAmount").value);

  // Find receiver account by username
  const receiverAccount = accounts.find(
    (acc) => acc.username === receiverUsername
  );

  // Validate
  if (!receiverAccount) {
    alert("Receiver account not found!");
    return;
  }

  if (amount <= 0) {
    alert("Amount must be positive!");
    return;
  }

  if (amount > currentAccount.account.balance) {
    alert("Insufficient balance!");
    return;
  }

  if (receiverAccount === currentAccount) {
    alert("Cannot transfer to your own account!");
    return;
  }

  // Perform transfer
  currentAccount.account.balance -= amount;
  receiverAccount.account.balance += amount;

  // Add movements
  currentAccount.movements.push(-amount);
  receiverAccount.movements.push(amount);

  // Add movement dates
  const now = new Date().toISOString();
  currentAccount.movementsDates.push(now);
  receiverAccount.movementsDates.push(now);

  // Add to daily transactions
  currentAccount.dailyTransactions.push({
    transactionID: `TXN${Date.now()}`,
    type: "transfer_out",
    amount: amount,
    date: now,
    description: `Transfer to ${receiverAccount.owner}`,
    receiver: receiverAccount.account.accountNumber,
  });

  receiverAccount.dailyTransactions.push({
    transactionID: `TXN${Date.now() + 1}`,
    type: "transfer_in",
    amount: amount,
    date: now,
    description: `Transfer from ${currentAccount.owner}`,
    sender: currentAccount.account.accountNumber,
  });

  // Update dashboard
  updateCustomerDashboard(currentAccount);

  // Clear form
  document.getElementById("transferTo").value = "";
  document.getElementById("transferAmount").value = "";

  // Show success message
  alert(
    `Successfully transferred ${formatCur(amount)} to ${receiverAccount.owner}`
  );
};

// Handle loan request
const handleLoanRequest = function () {
  if (!currentAccount) return;

  const loanType = document.getElementById("loanType").value;
  const amount = parseFloat(document.getElementById("loanAmount").value);

  if (!amount || amount <= 0) {
    alert("Loan amount must be positive!");
    return;
  }

  // Create loan request
  const request = {
    requestID: `REQ${Date.now()}`,
    customerID: currentAccount.id,
    customerName: currentAccount.owner,
    loanType: loanType,
    amount: amount,
    requestDate: new Date().toISOString().split("T")[0],
    status: "pending",
  };

  // Add to queue
  loanRequests.push(request);

  // Clear form
  document.getElementById("loanAmount").value = "";

  // Show success message
  alert(
    `Loan request submitted successfully!\nRequest ID: ${
      request.requestID
    }\nAmount: ${formatCur(amount)}\nType: ${loanType}`
  );

  // Go back to loans section
  showSection("loans");
};

// Handle deposit
const handleDeposit = function () {
  if (!currentAccount) return;

  const amount = parseFloat(document.getElementById("depositAmount").value);

  if (!amount || amount <= 0) {
    alert("Deposit amount must be positive!");
    return;
  }

  // Update balance
  currentAccount.account.balance += amount;

  // Add movement
  currentAccount.movements.push(amount);
  currentAccount.movementsDates.push(new Date().toISOString());

  // Add to daily transactions
  currentAccount.dailyTransactions.push({
    transactionID: `TXN${Date.now()}`,
    type: "deposit",
    amount: amount,
    date: new Date().toISOString(),
    description: "Cash deposit",
  });

  // Update dashboard
  updateCustomerDashboard(currentAccount);

  // Clear form
  document.getElementById("depositAmount").value = "";

  // Show success message
  alert(`Successfully deposited ${formatCur(amount)}`);
};

// Handle withdrawal
const handleWithdrawal = function () {
  if (!currentAccount) return;

  const amount = parseFloat(document.getElementById("withdrawAmount").value);

  if (!amount || amount <= 0) {
    alert("Withdrawal amount must be positive!");
    return;
  }

  if (amount > currentAccount.account.balance) {
    alert("Insufficient balance!");
    return;
  }

  // Update balance
  currentAccount.account.balance -= amount;

  // Add movement
  currentAccount.movements.push(-amount);
  currentAccount.movementsDates.push(new Date().toISOString());

  // Add to daily transactions
  currentAccount.dailyTransactions.push({
    transactionID: `TXN${Date.now()}`,
    type: "withdrawal",
    amount: amount,
    date: new Date().toISOString(),
    description: "Cash withdrawal",
  });

  // Update dashboard
  updateCustomerDashboard(currentAccount);

  // Clear form
  document.getElementById("withdrawAmount").value = "";

  // Show success message
  alert(`Successfully withdrew ${formatCur(amount)}`);
};

// Undo last transaction
const undoLastTransaction = function () {
  if (!currentAccount) return;

  if (currentAccount.dailyTransactions.length === 0) {
    alert("No transactions to undo!");
    return;
  }

  const lastTransaction = currentAccount.dailyTransactions.pop();

  // Reverse the transaction
  if (
    lastTransaction.type === "deposit" ||
    lastTransaction.type === "transfer_in"
  ) {
    currentAccount.account.balance -= lastTransaction.amount;
    // Remove last movement
    currentAccount.movements.pop();
    currentAccount.movementsDates.pop();
  } else if (
    lastTransaction.type === "withdrawal" ||
    lastTransaction.type === "transfer_out"
  ) {
    currentAccount.account.balance += lastTransaction.amount;
    // Remove last movement
    currentAccount.movements.pop();
    currentAccount.movementsDates.pop();
  }

  // Update dashboard
  updateCustomerDashboard(currentAccount);

  alert(
    `Undid last transaction: ${lastTransaction.type} of ${formatCur(
      lastTransaction.amount
    )}`
  );
};

//////////////////////////////////////////////////////////////////////////
// EMPLOYEE INTERFACE FUNCTIONS

// Show employee section
const showEmployeeSection = function (sectionId) {
  // Hide all sections
  const sections = document.querySelectorAll(".emp-content-section");
  sections.forEach((section) => section.classList.remove("active"));

  // Remove active from all sidebar links
  const links = document.querySelectorAll(".emp-sidebar-link");
  links.forEach((link) => link.classList.remove("active"));

  // Show selected section
  const targetSection = document.getElementById(`${sectionId}Section`);
  if (targetSection) {
    targetSection.classList.add("active");
  }

  // Activate corresponding sidebar link
  const targetLink = document.querySelector(
    `.emp-sidebar-link[data-section="${sectionId}"]`
  );
  if (targetLink) {
    targetLink.classList.add("active");
  }
};

// Update employee dashboard
const updateEmployeeDashboard = function (emp) {
  // Update welcome message
  document.getElementById(
    "empName"
  ).textContent = `${emp.firstName} ${emp.lastName}`;
  document.getElementById("empRole").textContent = `${emp.role
    .split("-")
    .map((word) => word.charAt(0).toUpperCase() + word.slice(1))
    .join(" ")} • ${
    branches.find((b) => b.code === emp.branchCode)?.name || "Unknown Branch"
  }`;

  // Update statistics
  document.getElementById("totalCustomers").textContent = accounts.length;
  document.getElementById("totalEmployees").textContent = employees.length;
  document.getElementById("pendingRequests").textContent = loanRequests.filter(
    (req) => req.status === "pending"
  ).length;
  document.getElementById("totalLoans").textContent = accounts.reduce(
    (total, acc) => total + acc.loans.length,
    0
  );

  // Update current date and time
  updateCurrentDateTime();

  // Load employee data
  displayEmployeesTable();
  displayAccountsTable();
  displayLoanRequests();
};

// Display employees table
const displayEmployeesTable = function () {
  const tableBody = document.getElementById("employeesTable");
  if (!tableBody) return;

  tableBody.innerHTML = "";

  employees.forEach((emp) => {
    const html = `
      <tr>
        <td>${emp.id}</td>
        <td>${emp.firstName} ${emp.lastName}</td>
        <td>${
          branches.find((b) => b.code === emp.branchCode)?.name ||
          emp.branchCode
        }</td>
        <td>${formatDate(emp.hireDate)}</td>
        <td>${formatCur(emp.salary)}</td>
        <td>
          <button class="btn-edit" onclick="editEmployee('${emp.id}')">
            <i class="fas fa-edit"></i>
          </button>
          ${
            emp.id !== currentEmployee?.id
              ? `<button class="btn-delete" onclick="deleteEmployee('${emp.id}')">
              <i class="fas fa-trash"></i>
            </button>`
              : '<button class="btn-disabled" disabled>Current</button>'
          }
        </td>
      </tr>
    `;
    tableBody.insertAdjacentHTML("beforeend", html);
  });
};

// Display accounts table
const displayAccountsTable = function () {
  const tableBody = document.getElementById("accountsTable");
  if (!tableBody) return;

  tableBody.innerHTML = "";

  accounts.forEach((acc) => {
    const html = `
      <tr>
        <td>${acc.account.accountNumber}</td>
        <td>${acc.owner}</td>
        <td>${acc.account.branchCode}</td>
        <td>${formatCur(acc.account.balance)}</td>
        <td><span class="status-${acc.account.status}">${
      acc.account.status
    }</span></td>
        <td>
          <button class="btn-view" onclick="viewAccountDetails('${acc.id}')">
            <i class="fas fa-eye"></i>
          </button>
          <button class="btn-edit" onclick="editAccount('${acc.id}')">
            <i class="fas fa-edit"></i>
          </button>
        </td>
      </tr>
    `;
    tableBody.insertAdjacentHTML("beforeend", html);
  });
};

// Display loan requests
const displayLoanRequests = function () {
  const container = document.getElementById("loanQueue");
  if (!container) return;

  container.innerHTML = "";

  const pendingRequests = loanRequests.filter(
    (req) => req.status === "pending"
  );

  if (pendingRequests.length === 0) {
    container.innerHTML = `
      <div class="empty-queue">
        <i class="fas fa-check-circle"></i>
        <p>No pending loan requests</p>
      </div>
    `;
    return;
  }

  pendingRequests.forEach((request) => {
    const html = `
      <div class="queue-item" data-id="${request.requestID}">
        <div class="queue-header">
          <span class="queue-number">#${request.requestID}</span>
          <span class="queue-status pending">Pending</span>
        </div>
        <div class="queue-body">
          <p><strong>Customer:</strong> ${request.customerName}</p>
          <p><strong>Loan Type:</strong> ${request.loanType}</p>
          <p><strong>Amount:</strong> ${formatCur(request.amount)}</p>
          <p><strong>Request Date:</strong> ${formatDate(
            request.requestDate
          )}</p>
        </div>
        <div class="queue-actions">
          <button class="btn-approve" onclick="approveLoan('${
            request.requestID
          }')">
            <i class="fas fa-check"></i> Approve
          </button>
          <button class="btn-reject" onclick="rejectLoan('${
            request.requestID
          }')">
            <i class="fas fa-times"></i> Reject
          </button>
        </div>
      </div>
    `;
    container.insertAdjacentHTML("beforeend", html);
  });
};

// Approve loan request
const approveLoan = function (requestId) {
  const requestIndex = loanRequests.findIndex(
    (req) => req.requestID === requestId
  );

  if (requestIndex === -1) {
    alert("Loan request not found!");
    return;
  }

  const request = loanRequests[requestIndex];
  const customer = accounts.find((acc) => acc.id === request.customerID);

  if (!customer) {
    alert("Customer not found!");
    return;
  }

  // Calculate interest rate based on loan type
  const interestRates = {
    car: 5.5,
    home: 4.2,
    student: 3.5,
    business: 6.0,
    personal: 7.5,
  };

  // Create new loan
  const newLoan = {
    loanID: `LOAN${Date.now()}`,
    loanType: request.loanType,
    principalAmount: request.amount,
    interestRate: interestRates[request.loanType] || 6.0,
    amountPaid: 0,
    remainingBalance: request.amount,
    startDate: new Date().toISOString().split("T")[0],
    endDate: new Date(
      new Date().setFullYear(
        new Date().getFullYear() +
          (request.loanType === "home"
            ? 10
            : request.loanType === "car"
            ? 2
            : 3)
      )
    )
      .toISOString()
      .split("T")[0],
    status: "active",
  };

  // Add loan to customer
  customer.loans.push(newLoan);

  // Update request status
  loanRequests[requestIndex].status = "approved";

  // Update dashboard
  if (currentEmployee) {
    updateEmployeeDashboard(currentEmployee);
  }

  alert(
    `Loan approved successfully!\nLoan ID: ${
      newLoan.loanID
    }\nAmount: ${formatCur(request.amount)}\nInterest Rate: ${
      newLoan.interestRate
    }%`
  );
};

// Reject loan request
const rejectLoan = function (requestId) {
  const requestIndex = loanRequests.findIndex(
    (req) => req.requestID === requestId
  );

  if (requestIndex === -1) {
    alert("Loan request not found!");
    return;
  }

  // Update request status
  loanRequests[requestIndex].status = "rejected";

  // Update dashboard
  if (currentEmployee) {
    updateEmployeeDashboard(currentEmployee);
  }

  alert("Loan request rejected!");
};

// Edit account (employee side)
const editAccount = function (customerId) {
  const account = accounts.find((acc) => acc.id === customerId);

  if (!account) {
    alert("Account not found!");
    return;
  }

  const newStatus = prompt(
    "Enter new status (active/inactive/suspended):",
    account.account.status
  );
  if (newStatus && ["active", "inactive", "suspended"].includes(newStatus)) {
    account.account.status = newStatus;

    if (currentEmployee) {
      updateEmployeeDashboard(currentEmployee);
    }

    alert("Account updated successfully!");
  }
};

// View account details (employee side)
const viewAccountDetails = function (customerId) {
  const account = accounts.find((acc) => acc.id === customerId);

  if (!account) {
    alert("Account not found!");
    return;
  }

  const details = `
    Customer: ${account.owner}
    Account: ${account.account.accountNumber}
    Type: ${account.account.accountType}
    Balance: ${formatCur(account.account.balance)}
    Status: ${account.account.status}
    Branch: ${account.account.branchCode}
    Loans: ${account.loans.length} active
    Last Login: ${account.lastLogin || "Never"}
  `;

  alert(details);
};

// Edit employee
const editEmployee = function (employeeId) {
  const employee = employees.find((emp) => emp.id === employeeId);

  if (!employee) {
    alert("Employee not found!");
    return;
  }

  const newSalary = prompt("Enter new salary:", employee.salary);
  if (newSalary && !isNaN(newSalary)) {
    employee.salary = parseFloat(newSalary);

    if (currentEmployee) {
      updateEmployeeDashboard(currentEmployee);
    }

    alert("Employee updated successfully!");
  }
};

// Delete employee
const deleteEmployee = function (employeeId) {
  if (employeeId === currentEmployee?.id) {
    alert("You cannot delete your own account!");
    return;
  }

  if (!confirm("Are you sure you want to delete this employee?")) {
    return;
  }

  const employeeIndex = employees.findIndex((emp) => emp.id === employeeId);

  if (employeeIndex === -1) {
    alert("Employee not found!");
    return;
  }

  employees.splice(employeeIndex, 1);

  if (currentEmployee) {
    updateEmployeeDashboard(currentEmployee);
  }

  alert("Employee deleted successfully!");
};

// Add new account (employee)
const addNewAccount = function () {
  const fullName = prompt("Enter customer full name:");
  if (!fullName) return;

  const pin = prompt("Enter 4-digit PIN:");
  if (!pin || pin.length !== 4 || isNaN(pin)) {
    alert("Invalid PIN! Must be 4 digits.");
    return;
  }

  const accountType = prompt("Account type (Savings/Current):", "Savings");
  const initialDeposit = parseFloat(prompt("Initial deposit amount:", "1000"));

  if (isNaN(initialDeposit) || initialDeposit < 0) {
    alert("Invalid deposit amount!");
    return;
  }

  // Generate account details
  const accountNumber = `ACC${String(accounts.length + 1).padStart(3, "0")}`;
  const customerId = `CUST${String(accounts.length + 1).padStart(3, "0")}`;
  const username = fullName
    .toLowerCase()
    .split(" ")
    .map((name) => name[0])
    .join("");

  const newAccount = {
    id: customerId,
    owner: fullName,
    username: username,
    pin: parseInt(pin),

    account: {
      accountNumber: accountNumber,
      accountType: accountType || "Savings",
      IBAN: `TN59 1000 1001 ${Math.random()
        .toString()
        .slice(2, 6)} ${Math.random().toString().slice(2, 6)}`,
      branchCode: currentEmployee?.branchCode || "001",
      holderName: fullName,
      openingDate: new Date().toISOString().split("T")[0],
      status: "active",
      balance: initialDeposit,
      currency: "TND",
      locale: "en-US",
    },

    movements: initialDeposit > 0 ? [initialDeposit] : [],
    movementsDates: initialDeposit > 0 ? [new Date().toISOString()] : [],
    interestRate: accountType === "Savings" ? 1.2 : 0.1,

    loans: [],
    dailyTransactions: [],
  };

  accounts.push(newAccount);

  if (currentEmployee) {
    updateEmployeeDashboard(currentEmployee);
  }

  alert(
    `New account created!\nAccount: ${accountNumber}\nCustomer ID: ${customerId}\nUsername: ${username}\nPIN: ${pin}`
  );
};

// Add new employee
const addNewEmployee = function () {
  const firstName = prompt("Enter first name:");
  if (!firstName) return;

  const lastName = prompt("Enter last name:");
  if (!lastName) return;

  const username = prompt("Enter username:");
  if (!username) return;

  const password = prompt("Enter password:");
  if (!password) return;

  const role = prompt(
    "Enter role (head-office/branch-manager/teller):",
    "teller"
  );
  const salary = parseFloat(prompt("Enter salary:", "2500"));

  if (isNaN(salary)) {
    alert("Invalid salary!");
    return;
  }

  const newEmployee = {
    id: `EMP${String(employees.length + 1).padStart(3, "0")}`,
    username: username,
    password: password,
    firstName: firstName,
    lastName: lastName,
    address: "Tunis, Tunisia",
    salary: salary,
    hireDate: new Date().toISOString().split("T")[0],
    branchCode: currentEmployee?.branchCode || "001",
    role: role || "teller",
  };

  employees.push(newEmployee);

  if (currentEmployee) {
    updateEmployeeDashboard(currentEmployee);
  }

  alert(
    `New employee added!\nID: ${newEmployee.id}\nName: ${firstName} ${lastName}\nUsername: ${username}`
  );
};

//////////////////////////////////////////////////////////////////////////
// EVENT LISTENERS AND INITIALIZATION

// Initialize the application
const initApp = function () {
  console.log("Initializing ELKHAZNA BANK system...");

  // Add event listeners for customer login
  const customerLoginBtn = document.getElementById("customerLoginBtn");
  if (customerLoginBtn) {
    customerLoginBtn.addEventListener("click", handleCustomerLogin);
    console.log("Customer login button listener added");
  }

  // Add event listeners for employee login
  const employeeLoginBtn = document.getElementById("employeeLoginBtn");
  if (employeeLoginBtn) {
    employeeLoginBtn.addEventListener("click", handleEmployeeLogin);
    console.log("Employee login button listener added");
  }

  // Add event listeners for customer dashboard buttons
  const customerLogoutBtn = document.getElementById("customerLogoutBtn");
  if (customerLogoutBtn) {
    customerLogoutBtn.addEventListener("click", logout);
  }

  const employeeLogoutBtn = document.getElementById("employeeLogoutBtn");
  if (employeeLogoutBtn) {
    employeeLogoutBtn.addEventListener("click", logout);
  }

  // Add sidebar navigation
  const sidebarLinks = document.querySelectorAll(".sidebar-link");
  sidebarLinks.forEach((link) => {
    link.addEventListener("click", function (e) {
      e.preventDefault();
      const section = this.getAttribute("data-section");
      showSection(section);
    });
  });

  // Add employee sidebar navigation
  const empSidebarLinks = document.querySelectorAll(".emp-sidebar-link");
  empSidebarLinks.forEach((link) => {
    link.addEventListener("click", function (e) {
      e.preventDefault();
      const section = this.getAttribute("data-section");
      showEmployeeSection(section);
    });
  });

  // Add transaction buttons
  const depositBtn = document.getElementById("depositBtn");
  if (depositBtn) {
    depositBtn.addEventListener("click", handleDeposit);
  }

  const withdrawBtn = document.getElementById("withdrawBtn");
  if (withdrawBtn) {
    withdrawBtn.addEventListener("click", handleWithdrawal);
  }

  const transferBtn = document.getElementById("transferBtn");
  if (transferBtn) {
    transferBtn.addEventListener("click", handleTransfer);
  }

  const submitLoanBtn = document.getElementById("submitLoanBtn");
  if (submitLoanBtn) {
    submitLoanBtn.addEventListener("click", handleLoanRequest);
  }

  const undoBtn = document.getElementById("undoBtn");
  if (undoBtn) {
    undoBtn.addEventListener("click", undoLastTransaction);
  }

  // Add employee action buttons
  const addEmployeeBtn = document.getElementById("addEmployeeBtn");
  if (addEmployeeBtn) {
    addEmployeeBtn.addEventListener("click", addNewEmployee);
  }

  const addAccountBtn = document.getElementById("addAccountBtn");
  if (addAccountBtn) {
    addAccountBtn.addEventListener("click", addNewAccount);
  }

  // Update date and time
  updateCurrentDateTime();
  setInterval(updateCurrentDateTime, 1000);

  // Add quick withdrawal buttons
  const denomButtons = document.querySelectorAll(".denom-btn");
  denomButtons.forEach((button) => {
    button.addEventListener("click", function () {
      const amount = this.getAttribute("data-amount");
      document.getElementById("withdrawAmount").value = amount;
    });
  });

  // Add duration buttons for loans
  const durationButtons = document.querySelectorAll(".duration-btn");
  durationButtons.forEach((button) => {
    button.addEventListener("click", function () {
      const years = this.getAttribute("data-years");
      alert(`Loan duration set to ${years} years`);
    });
  });

  console.log("System initialized successfully!");
  console.log(
    "Available accounts:",
    accounts.map((a) => ({ username: a.username, pin: a.pin }))
  );
  console.log(
    "Available employees:",
    employees.map((e) => ({ username: e.username, password: e.password }))
  );
};

// Start the application when DOM is loaded
document.addEventListener("DOMContentLoaded", initApp);

// Make functions available globally for onclick attributes
window.scrollToLogin = scrollToLogin;
window.fillCustomerDemo = fillCustomerDemo;
window.fillEmployeeDemo = fillEmployeeDemo;
window.showSection = showSection;
window.approveLoan = approveLoan;
window.rejectLoan = rejectLoan;
window.editEmployee = editEmployee;
window.deleteEmployee = deleteEmployee;
window.viewAccountDetails = viewAccountDetails;
window.editAccount = editAccount;
