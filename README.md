# cpp-bank-simulator

A lightweight, console-based C++ application that simulates core banking operations. This project demonstrates basic Object-Oriented Programming (OOP) principles in C++, file handling (optional), and robust input validation to prevent crashes from invalid user inputs.

---

## 🚀 Features

* **Deposit Funds:** Safely add a specific amount to an account balance.
* **Withdraw Funds:** Subtract an amount from the account (with insufficient funds checks).
* **Fund Transfer:** Move money securely between two different bank accounts.
* **Robust Input Validation:** Prevents application crashes. If a user accidentally types an alphabet (e.g., 'abc') instead of a number for balances or account IDs, the system catches the error and displays: `"Error: Invalid input! Please enter a valid number."`

---

## 🛠️ Tech Stack & Concepts Used

* **Language:** C++ (Standard ISO/IEC 14882)
* **Concepts:** Stream manipulation (`std::cin.fail()`), loops for input handling, and basic data structures to hold account records.

---

## 📦 How to Run the Project

### Prerequisites
Make sure you have a C++ compiler installed (like `g++` via GCC or Clang).

### Installation & Execution

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/YOUR_REPOSITORY_NAME.git](https://github.com/YOUR_USERNAME/YOUR_REPOSITORY_NAME.git)
   cd YOUR_REPOSITORY_NAME
