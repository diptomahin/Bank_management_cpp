# Bank Management System

## Overview
This is a simple **Bank Management System** implemented in **C++**. The system allows users to create accounts, log in, deposit money, withdraw funds, transfer funds between accounts, check balance, and close accounts.

## Features
- Open a new bank account
- Login with account number and password
- Deposit funds
- Withdraw funds (maintaining a minimum balance)
- Transfer funds to another account
- Check account balance
- View all accounts
- Close an account

## Prerequisites
To compile and run this program, you need:
- A C++ compiler (G++ recommended)
- A command-line interface (CLI)

## Compilation and Execution
Follow these steps to compile and run the program:

1. Open a terminal or command prompt.
2. Navigate to the folder containing the source code.
3. Compile the program using:
   ```sh
   g++ -o bank_management_system main.cpp
   ```
4. Run the executable:
   ```sh
   ./bank_management_system
   ```

## File Structure
```
├── main.cpp          # Main source code for the banking system
├── Bank.data         # Stores account information (if created during execution)
├── README.md         # Documentation for the project
```

## How to Use
1. Run the program.
2. Select a bank (Bank 1 or Bank 2).
3. Choose to **Open an Account** or **Login**.
4. After login, you can:
   - Deposit money
   - Withdraw money
   - Transfer money to another account
   - Check balance
   - View all accounts
   - Close your account
5. Logout when done.

## Data Storage
- The system stores account details in a file named **Bank.data**.
- When the program starts, it reads from **Bank.data** to restore account information.
- When an account is created, modified, or deleted, changes are written back to the file.

## Error Handling
- The system checks for **insufficient balance** before allowing withdrawals.
- Account authentication requires the correct **password**.
- Transfers verify both sender and receiver accounts before proceeding.


## License
This project is open-source. Feel free to use and modify it as needed.

---
**Author:** Mahin

