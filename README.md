# Library Management System

C++ ile terminal tabanlı kütüphane yönetim sistemi.

## Derleme

```bash
clang++ -std=c++17 src/main.cpp src/models/Book.cpp src/models/User.cpp src/models/Transaction.cpp src/services/AuthService.cpp src/services/CatalogService.cpp src/services/TransactionService.cpp -o library
