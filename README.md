# Bookshop Inventory Management System

## Description
The Bookshop Inventory Management System is a C++ application designed to streamline the management of books, magazines, customers, and staff in a bookshop. It provides functionality for inventory management, sales, user interactions, and analytics. The system allows managers, cashiers, and customers to perform tasks efficiently while ensuring data integrity.

## Features

### Books and Magazines Management
- Add new books and magazines.
- Search and browse by name, author, series, genre, or collection status.
- Display all available books and magazines with detailed information.

### Customer Management
- Register new customers.
- View and manage customer details and purchase history.

### Transactions
- Add items to a transaction and generate receipts.
- Update stock dynamically after each sale.

### User Roles
- Different interfaces for customers, cashiers, and the manager.
- Guest mode for browsing inventory without registration.

### Data Analytics
- Display statistics for total books, magazines, customers, and cashiers.
- Rating system for books.

### File Handling
- Load inventory and user data from external files:
  - `books.txt`
  - `magazines.txt`
  - `customers.txt`
  - `cashiers.txt`

## How to Run
1. Clone or download the project.
2. Open the source files in your C++ development environment.
3. Compile the `main.cpp` file with your preferred compiler.
4. Run the program and follow the interactive menu for various functionalities.

## Dependencies
- **Language**: C++
- **Standard libraries**:
  - `<iostream>`
  - `<vector>`
  - `<string>`
  - `<unordered_map>`
  - `<fstream>`
  - `<sstream>`
  - `<thread>`
  - `<chrono>`
  
  Ensure your compiler supports C++11 or later for multithreading and modern syntax.

## Usage Instructions
1. Launch the program.
2. Choose your role (Manager, Cashier, Customer, or Guest).
3. Follow the intuitive menu system for operations like inventory management, customer registration, or browsing.
4. Exit the program when done.

## Contributors
- Sharvani
