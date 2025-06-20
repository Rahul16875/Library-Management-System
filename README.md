📚 Library Management System
A comprehensive C++ console-based Library Management System that demonstrates object-oriented programming principles, data structures, file handling, and robust error management.

🌟 Features
📖 Book Management
✅ Add new books to the library
✅ View all available books
✅ Update book information (title, author, ISBN)
✅ Delete books from the system
✅ Search books by title, author, or ISBN
✅ Track book availability status
👥 User Management
✅ Add regular users and administrators
✅ View all registered users
✅ Track books issued to each user
✅ Role-based access control
📋 Library Operations
✅ Issue books to users
✅ Return books to the library
✅ Track which books are issued to which users
✅ Prevent deletion of issued books
🔐 Authentication
✅ Secure admin login system
✅ Default admin account (username: admin, password: admin123)
✅ Session management
💾 Data Persistence
✅ Automatic save/load functionality
✅ File-based storage (books.txt, users.txt)
✅ Graceful handling of missing or corrupted files
🏗️ Technical Architecture
Object-Oriented Design
Inheritance: Admin class inherits from User class
Encapsulation: Private data members with controlled access
Polymorphism: Virtual functions for different display behaviors
Constructor Overloading: Multiple ways to create objects
Function Overloading: Multiple versions of key functions
Data Structures Used
std::vector<Book> - Dynamic array for book storage
std::vector<User*> - Dynamic array for user storage
std::unordered_map<int, int> - Fast O(1) book ID lookups
std::map<int, int> - Ordered user ID mappings
Error Handling
Try-catch blocks for exception safety
Input validation with retry mechanisms
Graceful handling of file I/O errors
Memory leak prevention with proper destructors
🚀 Getting Started
Prerequisites
C++ compiler with C++11 support (GCC, Clang, or MSVC)
Standard Template Library (STL)
Compilation
Using GCC/Clang:
g++ -std=c++11 main.cpp -o library_system
Using MSVC (Visual Studio):
cl /EHsc main.cpp
Running the Application
./library_system
📋 Usage Guide
First Time Setup
Run the application
The system creates a default admin account:
Username: admin
Password: admin123
Admin Functions
Login: Use admin credentials to access administrative features
Book Management: Add, update, delete, and search books
User Management: Add new users and administrators
Library Operations: Issue and return books
View Reports: See all books and users in the system
Public Functions
View available books
Search books by title, author, or ISBN
📁 File Structure
library_system/
├── main.cpp           # Main application source code
├── books.txt          # Book data storage (auto-generated)
├── users.txt          # User data storage (auto-generated)
└── README.md          # This file
🗃️ Data Format
Books File Format
BookID,Title,Author,ISBN,IsIssued,IssuedToUserID
Users File Format
UserID,Name,Email,UserType,IssuedBooks,Username,Password
🎯 Menu Navigation
Main Menu
1. Admin Login
2. View Available Books
3. Search Books
4. Exit
Admin Panel
1. Add Book
2. View All Books
3. Update Book
4. Delete Book
5. Issue Book
6. Return Book
7. Add User
8. View All Users
9. Search Books
10. Logout
🔧 Configuration
Default Admin Account
Username: admin
Password: admin123
Email: admin@library.com
Name: System Admin
File Locations
Books data: books.txt (same directory as executable)
Users data: users.txt (same directory as executable)
🛡️ Security Features
Password-protected admin access
Input validation and sanitization
Prevention of unauthorized operations
Session-based authentication
🐛 Error Handling
The system handles various error conditions:

Invalid user input
File I/O errors
Memory allocation failures
Attempting to delete issued books
Duplicate book/user IDs
Missing data files
🔄 Data Backup
The system automatically saves data when:

The application exits normally
Administrative operations are performed
Data is modified
Recommendation: Regularly backup books.txt and users.txt files.

🚀 Advanced Features
Search Functionality
Title Search: Find books by partial or complete title
Author Search: Locate books by author name
ISBN Search: Direct lookup by ISBN number
Book Status Tracking
Real-time availability status
User assignment tracking
Prevention of double-issuing
User Role Management
Regular users vs. administrators
Different access levels
Secure credential storage
🔮 Future Enhancements
Potential improvements for the system:

GUI interface using Qt or similar framework
Database integration (SQLite/MySQL)
Due date tracking and overdue notifications
Book categories and genres
Advanced reporting features
Barcode scanning support
Multi-library support
🤝 Contributing
To contribute to this project:

Fork the repository
Create a feature branch
Make your changes
Test thoroughly
Submit a pull request
📝 Code Structure
Core Classes
Book Class
Manages book information and status
Handles file serialization/deserialization
Provides display functionality
User Class
Base class for system users
Manages user information and issued books
Virtual functions for polymorphism
Admin Class
Inherits from User class
Adds authentication capabilities
Administrative privileges
LibrarySystem Class
Main system controller
Handles all business logic
Manages data persistence
Provides user interface
🔍 Testing
Test Scenarios
Book Operations: Add, update, delete, search books
User Management: Create users, assign roles
Library Operations: Issue/return books
Authentication: Login/logout functionality
Data Persistence: Save/load operations
Error Handling: Invalid inputs, edge cases
Sample Test Data
// Sample books to add:
Title: "The C++ Programming Language", Author: "Bjarne Stroustrup", ISBN: "978-0321563842"
Title: "Effective C++", Author: "Scott Meyers", ISBN: "978-0321334879"
Title: "Design Patterns", Author: "Gang of Four", ISBN: "978-0201633610"
📊 Performance Considerations
Book Lookup: O(1) average time complexity using hash maps
User Lookup: O(log n) time complexity using ordered maps
Memory Usage: Dynamic allocation with proper cleanup
File I/O: Efficient text-based storage format
🔧 Troubleshooting
Common Issues
Compilation Errors
Ensure C++11 or later standard
Check for missing headers
Verify compiler compatibility
Runtime Issues
Check file permissions for data files
Ensure sufficient disk space
Verify input format compliance
Data Corruption
Delete books.txt and users.txt to reset
System will recreate with default admin account
📞 Support
For issues, questions, or contributions:

Create an issue in the project repository
Review the troubleshooting section
Check the code comments for implementation details
📄 License
This project is provided as-is for educational purposes. Feel free to modify and distribute according to your needs.

Happy Coding! 📚✨


This comprehensive README file provides:

- **Complete feature overview** with checkmarks
- **Technical architecture** explanation
- **Step-by-step setup** instructions
- **Detailed usage guide** for both admins and users
- **File structure** and data format documentation
- **Security and error handling** information
- **Future enhancement** suggestions
- **Testing scenarios** and troubleshooting tips
- **Performance considerations** and technical details

The README is structured to help both beginners understand how to use the system and developer
