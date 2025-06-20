#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <limits>

// Forward declarations
class Book;
class User;
class Admin;
class LibrarySystem;

// Book class
class Book {
private:
    int bookId;
    std::string title;
    std::string author;
    std::string isbn;
    bool isIssued;
    int issuedToUserId;

public:
    // Default constructor
    Book() : bookId(0), title(""), author(""), isbn(""), isIssued(false), issuedToUserId(-1) {}
    
    // Parameterized constructor
    Book(int id, const std::string& t, const std::string& a, const std::string& i) 
        : bookId(id), title(t), author(a), isbn(i), isIssued(false), issuedToUserId(-1) {}
    
    // Constructor overloading
    Book(int id, const std::string& t, const std::string& a, const std::string& i, bool issued, int userId)
        : bookId(id), title(t), author(a), isbn(i), isIssued(issued), issuedToUserId(userId) {}

    // Getters
    int getBookId() const { return bookId; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }
    bool getIsIssued() const { return isIssued; }
    int getIssuedToUserId() const { return issuedToUserId; }

    // Setters
    void setBookId(int id) { bookId = id; }
    void setTitle(const std::string& t) { title = t; }
    void setAuthor(const std::string& a) { author = a; }
    void setIsbn(const std::string& i) { isbn = i; }
    void setIsIssued(bool issued) { isIssued = issued; }
    void setIssuedToUserId(int userId) { issuedToUserId = userId; }

    // Virtual display function for polymorphism
    virtual void display() const {
        std::cout << std::left << std::setw(5) << bookId 
                  << std::setw(25) << title 
                  << std::setw(20) << author 
                  << std::setw(15) << isbn 
                  << std::setw(10) << (isIssued ? "Issued" : "Available");
        if (isIssued) {
            std::cout << std::setw(10) << issuedToUserId;
        }
        std::cout << std::endl;
    }

    // Function to save book data to file
    std::string toFileString() const {
        return std::to_string(bookId) + "," + title + "," + author + "," + isbn + "," + 
               std::to_string(isIssued) + "," + std::to_string(issuedToUserId);
    }

    // Function to load book data from file string
    void fromFileString(const std::string& data) {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> tokens;
        std::string temp = data;
        
        while ((pos = temp.find(',')) != std::string::npos) {
            token = temp.substr(0, pos);
            tokens.push_back(token);
            temp.erase(0, pos + 1);
        }
        tokens.push_back(temp);

        if (tokens.size() >= 6) {
            bookId = std::stoi(tokens[0]);
            title = tokens[1];
            author = tokens[2];
            isbn = tokens[3];
            isIssued = std::stoi(tokens[4]);
            issuedToUserId = std::stoi(tokens[5]);
        }
    }
};

// User class
class User {
protected:
    int userId;
    std::string name;
    std::string email;
    std::vector<int> issuedBooks;

public:
    // Default constructor
    User() : userId(0), name(""), email("") {}
    
    // Parameterized constructor
    User(int id, const std::string& n, const std::string& e) 
        : userId(id), name(n), email(e) {}

    // Virtual destructor
    virtual ~User() {}

    // Getters
    int getUserId() const { return userId; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    const std::vector<int>& getIssuedBooks() const { return issuedBooks; }

    // Setters
    void setUserId(int id) { userId = id; }
    void setName(const std::string& n) { name = n; }
    void setEmail(const std::string& e) { email = e; }

    // Virtual display function for polymorphism
    virtual void display() const {
        std::cout << std::left << std::setw(5) << userId 
                  << std::setw(20) << name 
                  << std::setw(25) << email 
                  << std::setw(15) << "Regular User"
                  << std::setw(10) << issuedBooks.size() << std::endl;
    }

    // Function to add issued book
    void addIssuedBook(int bookId) {
        issuedBooks.push_back(bookId);
    }

    // Function to remove issued book
    void removeIssuedBook(int bookId) {
        issuedBooks.erase(std::remove(issuedBooks.begin(), issuedBooks.end(), bookId), issuedBooks.end());
    }

    // Function to save user data to file
    virtual std::string toFileString() const {
        std::string booksStr = "";
        for (size_t i = 0; i < issuedBooks.size(); ++i) {
            booksStr += std::to_string(issuedBooks[i]);
            if (i < issuedBooks.size() - 1) booksStr += ";";
        }
        return std::to_string(userId) + "," + name + "," + email + ",USER," + booksStr;
    }

    // Function to load user data from file string
    virtual void fromFileString(const std::string& data) {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> tokens;
        std::string temp = data;
        
        while ((pos = temp.find(',')) != std::string::npos) {
            token = temp.substr(0, pos);
            tokens.push_back(token);
            temp.erase(0, pos + 1);
        }
        tokens.push_back(temp);

        if (tokens.size() >= 5) {
            userId = std::stoi(tokens[0]);
            name = tokens[1];
            email = tokens[2];
            // tokens[3] is user type
            
            // Parse issued books
            if (!tokens[4].empty()) {
                std::string booksStr = tokens[4];
                size_t bookPos = 0;
                while ((bookPos = booksStr.find(';')) != std::string::npos) {
                    issuedBooks.push_back(std::stoi(booksStr.substr(0, bookPos)));
                    booksStr.erase(0, bookPos + 1);
                }
                if (!booksStr.empty()) {
                    issuedBooks.push_back(std::stoi(booksStr));
                }
            }
        }
    }
};

// Admin class inheriting from User
class Admin : public User {
private:
    std::string username;
    std::string password;

public:
    // Default constructor
    Admin() : User(), username(""), password("") {}
    
    // Parameterized constructor
    Admin(int id, const std::string& n, const std::string& e, const std::string& u, const std::string& p) 
        : User(id, n, e), username(u), password(p) {}

    // Getters
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }

    // Setters
    void setUsername(const std::string& u) { username = u; }
    void setPassword(const std::string& p) { password = p; }

    // Override display function (polymorphism)
    void display() const override {
        std::cout << std::left << std::setw(5) << userId 
                  << std::setw(20) << name 
                  << std::setw(25) << email 
                  << std::setw(15) << "Administrator"
                  << std::setw(10) << issuedBooks.size() << std::endl;
    }

    // Override file operations
    std::string toFileString() const override {
        std::string booksStr = "";
        for (size_t i = 0; i < issuedBooks.size(); ++i) {
            booksStr += std::to_string(issuedBooks[i]);
            if (i < issuedBooks.size() - 1) booksStr += ";";
        }
        return std::to_string(userId) + "," + name + "," + email + ",ADMIN," + booksStr + "," + username + "," + password;
    }

    void fromFileString(const std::string& data) override {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> tokens;
        std::string temp = data;
        
        while ((pos = temp.find(',')) != std::string::npos) {
            token = temp.substr(0, pos);
            tokens.push_back(token);
            temp.erase(0, pos + 1);
        }
        tokens.push_back(temp);

        if (tokens.size() >= 7) {
            userId = std::stoi(tokens[0]);
            name = tokens[1];
            email = tokens[2];
            // tokens[3] is user type
            
            // Parse issued books
            if (!tokens[4].empty()) {
                std::string booksStr = tokens[4];
                size_t bookPos = 0;
                while ((bookPos = booksStr.find(';')) != std::string::npos) {
                    issuedBooks.push_back(std::stoi(booksStr.substr(0, bookPos)));
                    booksStr.erase(0, bookPos + 1);
                }
                if (!booksStr.empty()) {
                    issuedBooks.push_back(std::stoi(booksStr));
                }
            }
            
            username = tokens[5];
            password = tokens[6];
        }
    }

    // Function to authenticate admin
    bool authenticate(const std::string& u, const std::string& p) const {
        return (username == u && password == p);
    }
};

// Library Management System class
class LibrarySystem {
private:
    std::vector<Book> books;
    std::vector<User*> users;
    std::unordered_map<int, int> bookIdToIndex;
    std::map<int, int> userIdToIndex;
    int nextBookId;
    int nextUserId;
    Admin* currentAdmin;

    // File names
    const std::string BOOKS_FILE = "books.txt";
    const std::string USERS_FILE = "users.txt";

public:
    // Constructor
    LibrarySystem() : nextBookId(1), nextUserId(1), currentAdmin(nullptr) {
        // Create default admin
        Admin* defaultAdmin = new Admin(0, "System Admin", "admin@library.com", "admin", "admin123");
        users.push_back(defaultAdmin);
        userIdToIndex[0] = 0;
        
        loadData();
    }

    // Destructor
    ~LibrarySystem() {
        saveData();
        for (User* user : users) {
            delete user;
        }
    }

    // Function overloading for adding books
    void addBook(const std::string& title, const std::string& author, const std::string& isbn) {
        addBook(nextBookId++, title, author, isbn);
    }

    void addBook(int id, const std::string& title, const std::string& author, const std::string& isbn) {
        try {
            Book newBook(id, title, author, isbn);
            books.push_back(newBook);
            bookIdToIndex[id] = books.size() - 1;
            if (id >= nextBookId) nextBookId = id + 1;
            std::cout << "Book added successfully!" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error adding book: " << e.what() << std::endl;
        }
    }

    // View all books
    void viewBooks() const {
        if (books.empty()) {
            std::cout << "No books available in the library." << std::endl;
            return;
        }

        std::cout << "\n" << std::string(90, '=') << std::endl;
        std::cout << "LIBRARY BOOKS" << std::endl;
        std::cout << std::string(90, '=') << std::endl;
        std::cout << std::left << std::setw(5) << "ID" 
                  << std::setw(25) << "Title" 
                  << std::setw(20) << "Author" 
                  << std::setw(15) << "ISBN" 
                  << std::setw(10) << "Status"
                  << std::setw(10) << "User ID" << std::endl;
        std::cout << std::string(90, '-') << std::endl;

        for (const auto& book : books) {
            book.display(); // Polymorphism in action
        }
        std::cout << std::string(90, '=') << std::endl;
    }

    // Search books (function overloading)
    void searchBooks(const std::string& query, const std::string& searchType) {
        std::vector<Book> results;
        
        for (const auto& book : books) {
            if (searchType == "title" && book.getTitle().find(query) != std::string::npos) {
                results.push_back(book);
            } else if (searchType == "author" && book.getAuthor().find(query) != std::string::npos) {
                results.push_back(book);
            } else if (searchType == "isbn" && book.getIsbn().find(query) != std::string::npos) {
                results.push_back(book);
            }
        }

        if (results.empty()) {
            std::cout << "No books found matching your search criteria." << std::endl;
            return;
        }

        std::cout << "\nSearch Results:" << std::endl;
        std::cout << std::string(90, '-') << std::endl;
        std::cout << std::left << std::setw(5) << "ID" 
                  << std::setw(25) << "Title" 
                  << std::setw(20) << "Author" 
                  << std::setw(15) << "ISBN" 
                  << std::setw(10) << "Status" << std::endl;
        std::cout << std::string(90, '-') << std::endl;

        for (const auto& book : results) {
            book.display();
        }
    }

    // Update book
    void updateBook(int bookId) {
        try {
            auto it = bookIdToIndex.find(bookId);
            if (it == bookIdToIndex.end()) {
                throw std::runtime_error("Book not found!");
            }

            Book& book = books[it->second];
            std::string input;
            
            std::cout << "Current Title: " << book.getTitle() << std::endl;
            std::cout << "Enter new title (or press Enter to keep current): ";
            std::cin.ignore();
            std::getline(std::cin, input);
            if (!input.empty()) book.setTitle(input);

            std::cout << "Current Author: " << book.getAuthor() << std::endl;
            std::cout << "Enter new author (or press Enter to keep current): ";
            std::getline(std::cin, input);
            if (!input.empty()) book.setAuthor(input);

            std::cout << "Current ISBN: " << book.getIsbn() << std::endl;
            std::cout << "Enter new ISBN (or press Enter to keep current): ";
            std::getline(std::cin, input);
            if (!input.empty()) book.setIsbn(input);

            std::cout << "Book updated successfully!" << std::endl;

        } catch (const std::exception& e) {
            std::cout << "Error updating book: " << e.what() << std::endl;
        }
    }

    // Delete book
    void deleteBook(int bookId) {
        try {
            auto it = bookIdToIndex.find(bookId);
            if (it == bookIdToIndex.end()) {
                throw std::runtime_error("Book not found!");
            }

            int index = it->second;
            if (books[index].getIsIssued()) {
                throw std::runtime_error("Cannot delete an issued book!");
            }

            books.erase(books.begin() + index);
            bookIdToIndex.erase(it);

            // Update indices
            bookIdToIndex.clear();
            for (size_t i = 0; i < books.size(); ++i) {
                bookIdToIndex[books[i].getBookId()] = i;
            }

            std::cout << "Book deleted successfully!" << std::endl;

        } catch (const std::exception& e) {
            std::cout << "Error deleting book: " << e.what() << std::endl;
        }
    }

    // Issue book
    void issueBook(int bookId, int userId) {
        try {
            auto bookIt = bookIdToIndex.find(bookId);
            if (bookIt == bookIdToIndex.end()) {
                throw std::runtime_error("Book not found!");
            }

            auto userIt = userIdToIndex.find(userId);
            if (userIt == userIdToIndex.end()) {
                throw std::runtime_error("User not found!");
            }

            Book& book = books[bookIt->second];
            if (book.getIsIssued()) {
                throw std::runtime_error("Book is already issued!");
            }

            User* user = users[userIt->second];
            book.setIsIssued(true);
            book.setIssuedToUserId(userId);
            user->addIssuedBook(bookId);

            std::cout << "Book issued successfully to " << user->getName() << std::endl;

        } catch (const std::exception& e) {
            std::cout << "Error issuing book: " << e.what() << std::endl;
        }
    }

    // Return book
    void returnBook(int bookId) {
        try {
            auto bookIt = bookIdToIndex.find(bookId);
            if (bookIt == bookIdToIndex.end()) {
                throw std::runtime_error("Book not found!");
            }

            Book& book = books[bookIt->second];
            if (!book.getIsIssued()) {
                throw std::runtime_error("Book is not currently issued!");
            }

            int userId = book.getIssuedToUserId();
            auto userIt = userIdToIndex.find(userId);
            if (userIt != userIdToIndex.end()) {
                users[userIt->second]->removeIssuedBook(bookId);
            }

            book.setIsIssued(false);
            book.setIssuedToUserId(-1);

            std::cout << "Book returned successfully!" << std::endl;

        } catch (const std::exception& e) {
            std::cout << "Error returning book: " << e.what() << std::endl;
        }
    }

    // Add user
    void addUser(const std::string& name, const std::string& email, bool isAdmin = false, 
                 const std::string& username = "", const std::string& password = "") {
        try {
            User* newUser;
            if (isAdmin) {
                newUser = new Admin(nextUserId, name, email, username, password);
            } else {
                newUser = new User(nextUserId, name, email);
            }
            
            users.push_back(newUser);
            userIdToIndex[nextUserId] = users.size() - 1;
            nextUserId++;

            std::cout << (isAdmin ? "Admin" : "User") << " added successfully!" << std::endl;

        } catch (const std::exception& e) {
            std::cout << "Error adding user: " << e.what() << std::endl;
        }
    }

    // View all users
    void viewUsers() const {
        if (users.empty()) {
            std::cout << "No users registered in the system." << std::endl;
            return;
        }

        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "REGISTERED USERS" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        std::cout << std::left << std::setw(5) << "ID" 
                  << std::setw(20) << "Name" 
                  << std::setw(25) << "Email" 
                  << std::setw(15) << "Type"
                  << std::setw(10) << "Books" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        for (const auto& user : users) {
            user->display(); // Polymorphism in action
        }
        std::cout << std::string(80, '=') << std::endl;
    }

    // Admin login
    bool adminLogin(const std::string& username, const std::string& password) {
        for (User* user : users) {
            Admin* admin = dynamic_cast<Admin*>(user);
            if (admin && admin->authenticate(username, password)) {
                currentAdmin = admin;
                return true;
            }
        }
        return false;
    }

    // Admin logout
    void adminLogout() {
        currentAdmin = nullptr;
    }

    // Check if admin is logged in
    bool isAdminLoggedIn() const {
        return currentAdmin != nullptr;
    }

    // Get current admin
    Admin* getCurrentAdmin() const {
        return currentAdmin;
    }

    // Save data to files
    void saveData() {
        try {
            // Save books
            std::ofstream booksFile(BOOKS_FILE);
            if (booksFile.is_open()) {
                for (const auto& book : books) {
                    booksFile << book.toFileString() << std::endl;
                }
                booksFile.close();
            }

            // Save users
            std::ofstream usersFile(USERS_FILE);
            if (usersFile.is_open()) {
                for (const auto& user : users) {
                    usersFile << user->toFileString() << std::endl;
                }
                usersFile.close();
            }

        } catch (const std::exception& e) {
            std::cout << "Error saving data: " << e.what() << std::endl;
        }
    }

    // Load data from files
    void loadData() {
        try {
            // Load books
            std::ifstream booksFile(BOOKS_FILE);
            if (booksFile.is_open()) {
                std::string line;
                while (std::getline(booksFile, line)) {
                    if (!line.empty()) {
                        Book book;
                        book.fromFileString(line);
                        books.push_back(book);
                        bookIdToIndex[book.getBookId()] = books.size() - 1;
                        if (book.getBookId() >= nextBookId) {
                            nextBookId = book.getBookId() + 1;
                        }
                    }
                }
                booksFile.close();
            }

            // Load users (skip default admin at index 0)
            std::ifstream usersFile(USERS_FILE);
            if (usersFile.is_open()) {
                std::string line;
                while (std::getline(usersFile, line)) {
                    if (!line.empty()) {
                        // Determine user type
                        if (line.find(",ADMIN,") != std::string::npos) {
                            Admin* admin = new Admin();
                            admin->fromFileString(line);
                            // Don't add if it's the default admin
                            if (admin->getUserId() != 0) {
                                users.push_back(admin);
                                userIdToIndex[admin->getUserId()] = users.size() - 1;
                                if (admin->getUserId() >= nextUserId) {
                                    nextUserId = admin->getUserId() + 1;
                                }
                            } else {
                                delete admin;
                            }
                        } else {
                            User* user = new User();
                            user->fromFileString(line);
                            users.push_back(user);
                            userIdToIndex[user->getUserId()] = users.size() - 1;
                            if (user->getUserId() >= nextUserId) {
                                nextUserId = user->getUserId() + 1;
                            }
                        }
                    }
                }
                usersFile.close();
            }

        } catch (const std::exception& e) {
            std::cout << "Error loading data: " << e.what() << std::endl;
        }
    }

    // Get input with validation
    int getValidatedInput(int min, int max) {
        int choice;
        while (true) {
            std::cout << "Enter your choice (" << min << "-" << max << "): ";
            if (std::cin >> choice) {
                if (choice >= min && choice <= max) {
                    return choice;
                } else {
                    std::cout << "Invalid choice! Please enter a number between " << min << " and " << max << "." << std::endl;
                }
            } else {
                std::cout << "Invalid input! Please enter a valid number." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    // Main menu
    void showMainMenu() {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "    LIBRARY MANAGEMENT SYSTEM" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "1. Admin Login" << std::endl;
        std::cout << "2. View Available Books" << std::endl;
        std::cout << "3. Search Books" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    }

    // Admin menu
    void showAdminMenu() {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "    ADMIN PANEL" << std::endl;
        std::cout << "    Welcome, " << currentAdmin->getName() << "!" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "1. Add Book" << std::endl;
        std::cout << "2. View All Books" << std::endl;
        std::cout << "3. Update Book" << std::endl;
        std::cout << "4. Delete Book" << std::endl;
        std::cout << "5. Issue Book" << std::endl;
        std::cout << "6. Return Book" << std::endl;
        std::cout << "7. Add User" << std::endl;
        std::cout << "8. View All Users" << std::endl;
        std::cout << "9. Search Books" << std::endl;
        std::cout << "10. Logout" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    }

    // Run the system
    void run() {
        std::cout << "Welcome to the Library Management System!" << std::endl;
        
        while (true) {
            try {
                if (!isAdminLoggedIn()) {
                    showMainMenu();
                    int choice = getValidatedInput(1, 4);

                    switch (choice) {
                        case 1: {
                            std::string username, password;
                            std::cout << "Enter username: ";
                            std::cin >> username;
                            std::cout << "Enter password: ";
                            std::cin >> password;

                            if (adminLogin(username, password)) {
                                std::cout << "Login successful!" << std::endl;
                            } else {
                                std::cout << "Invalid credentials!" << std::endl;
                            }
                            break;
                        }
                        case 2:
                            viewBooks();
                            break;
                        case 3: {
                            std::string query, searchType;
                            std::cout << "Search by (title/author/isbn): ";
                            std::cin >> searchType;
                            std::cout << "Enter search query: ";
                            std::cin.ignore();
                            std::getline(std::cin, query);
                            searchBooks(query, searchType);
                            break;
                        }
                        case 4:
                            std::cout << "Thank you for using Library Management System!" << std::endl;
                            return;
                    }
                } else {
                    showAdminMenu();
                    int choice = getValidatedInput(1, 10);

                    switch (choice) {
                        case 1: {
                            std::string title, author, isbn;
                            std::cout << "Enter book title: ";
                            std::cin.ignore();
                            std::getline(std::cin, title);
                            std::cout << "Enter author: ";
                            std::getline(std::cin, author);
                            std::cout << "Enter ISBN: ";
                            std::getline(std::cin, isbn);
                            addBook(title, author, isbn);
                            break;
                        }
                        case 2:
                            viewBooks();
                            break;
                        case 3: {
                            int bookId;
                            std::cout << "Enter book ID to update: ";
                            std::cin >> bookId;
                            updateBook(bookId);
                            break;
                        }
                        case 4: {
                            int bookId;
                            std::cout << "Enter book ID to delete: ";
                            std::cin >> bookId;
                            deleteBook(bookId);
                            break;
                        }
                        case 5: {
                            int bookId, userId;
                            std::cout << "Enter book ID: ";
                            std::cin >> bookId;
                            std::cout << "Enter user ID: ";
                            std::cin >> userId;
                            issueBook(bookId, userId);
                            break;
                        }
                        case 6: {
                            int bookId;
                            std::cout << "Enter book ID to return: ";
                            std::cin >> bookId;
                            returnBook(bookId);
                            break;
                        }
                        case 7: {
                            std::string name, email, username, password;
                            char isAdminChoice;
                            
                            std::cout << "Enter user name: ";
                            std::cin.ignore();
                            std::getline(std::cin, name);
                            std::cout << "Enter email: ";
                            std::getline(std::cin, email);
                            std::cout << "Is this an admin user? (y/n): ";
                            std::cin >> isAdminChoice;
                            
                            bool isAdmin = (isAdminChoice == 'y' || isAdminChoice == 'Y');
                            if (isAdmin) {
                                std::cout << "Enter username: ";
                                std::cin >> username;
                                std::cout << "Enter password: ";
                                std::cin >> password;
                            }
                            
                            addUser(name, email, isAdmin, username, password);
                            break;
                        }
                        case 8:
                            viewUsers();
                            break;
                        case 9: {
                            std::string query, searchType;
                            std::cout << "Search by (title/author/isbn): ";
                            std::cin >> searchType;
                            std::cout << "Enter search query: ";
                            std::cin.ignore();
                            std::getline(std::cin, query);
                            searchBooks(query, searchType);
                            break;
                        }
                        case 10:
                            adminLogout();
                            std::cout << "Logged out successfully!" << std::endl;
                            break;
                    }
                }
            } catch (const std::exception& e) {
                std::cout << "An error occurred: " << e.what() << std::endl;
            }
        }
    }
};

// Main function
int main() {
    try {
        LibrarySystem library;
        library.run();
    } catch (const std::exception& e) {
        std::cout << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}