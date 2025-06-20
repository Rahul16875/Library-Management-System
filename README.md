# 📚 Library Management System

A comprehensive C++ console-based Library Management System that demonstrates object-oriented programming principles, data structures, file handling, and robust error management.

---

## 🌟 Features

### 📖 Book Management
✅ Add new books to the library  
✅ View all available books  
✅ Update book information (title, author, ISBN)  
✅ Delete books from the system  
✅ Search books by title, author, or ISBN  
✅ Track book availability status  

### 👥 User Management
✅ Add regular users and administrators  
✅ View all registered users  
✅ Track books issued to each user  
✅ Role-based access control  

### 📋 Library Operations
✅ Issue books to users  
✅ Return books to the library  
✅ Track which books are issued to which users  
✅ Prevent deletion of issued books 🔐  

### 🔐 Authentication
✅ Secure admin login system  
✅ Default admin account (username: `admin`, password: `admin123`)  
✅ Session management  

### 💾 Data Persistence
✅ Automatic save/load functionality  
✅ File-based storage (`books.txt`, `users.txt`)  
✅ Graceful handling of missing or corrupted files  

---

## 🏗️ Technical Architecture

### Object-Oriented Design
- **Inheritance**: `Admin` class inherits from `User` class  
- **Encapsulation**: Private data members with controlled access  
- **Polymorphism**: Virtual functions for display behaviors  
- **Constructor Overloading**  
- **Function Overloading**

### Data Structures Used
- `std::vector<Book>` – Dynamic array for book storage  
- `std::vector<User*>` – Dynamic array for user storage  
- `std::unordered_map<int, int>` – Fast O(1) book ID lookups  
- `std::map<int, int>` – Ordered user ID mappings  

### Error Handling
- Try-catch blocks  
- Input validation with retry  
- Graceful file I/O error handling  
- Memory leak prevention with proper destructors  

---

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++11 support (GCC, Clang, or MSVC)  
- STL (Standard Template Library)

### Compilation

Using GCC/Clang:
```bash
g++ -std=c++11 main.cpp -o library_system
