# Library Management System

A simple C++ console-based library management system for learning OOP, file handling, and terminal UI.

## Features

- User authentication (admin/user)
- Book add, update, delete, search, list
- Borrow/return books, transaction history
- All data in plain `.dat` files

## Quick Start

```bash
# Clone and enter project folder
git clone https://github.com/yourusername/LibraryManagementSystem.git
cd LibraryManagementSystem

# Build
clang++ -std=c++17 src/main.cpp src/models/Book.cpp src/models/User.cpp src/models/Transaction.cpp src/services/AuthService.cpp src/services/CatalogService.cpp src/services/TransactionService.cpp -o library

# Run
./library
