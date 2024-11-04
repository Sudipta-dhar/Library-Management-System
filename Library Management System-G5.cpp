// Library Management System-G5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*Library System, Group No 5
Group Members Name & student Id:
1.Sudipta - 202169990264,
2.Subodh - 202169990044,
3.Ibrahin - 202169990079,
4.Walid - 202169990015,
*/
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Base class for different types of books
class Book {
protected:
    string title;
    string author;
    string ISBN;
    string type;
    int available_copies;
    vector<int> reserved_id;

public:
    Book(const string& title, const string& author, const string& ISBN,
        const string& type, const int& available_copies)
        : title(title), author(author), ISBN(ISBN), type(type),
        available_copies(available_copies) {}


    void display() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Type: " << type << endl;
        cout << "Available Copies: " << type << endl;
        cout << "Reserved ids:" << endl;
        if (reserved_id.size() == 0) {
            cout << "No reservation";
        }
        for (int i = 0; i < reserved_id.size(); i++) {
            cout << "Id number:" << reserved_id[i] << endl;
        }
    }

    // Getter methods
    string getTitle() const { return title; }

    string getAuthor() const { return author; }

    string getISBN() const { return ISBN; }

    string getType() const { return type; }

    int getAvailableCopies() const { return available_copies; }

    vector<int> getReservedIds() const { return reserved_id; }

    // Setter methods
    void setTitle(const string& title) { this->title = title; }

    void setAuthor(const string& author) { this->author = author; }

    void setISBN(const string& ISBN) { this->ISBN = ISBN; }

    void setType(const string& type) { this->type = type; }

    void setAvailableCopies(int copies) { available_copies = copies; }
    void setReservedIds(const vector<int>& ids) { reserved_id = ids; }

    void addReservedId(int userID) { reserved_id.push_back(userID); }
};

// User base class
class User {
private:
    int id;
    string name;
    string type;
    string password;

public:
    User(int id, const string& name, const string& type, const string& password)
        : id(id), name(name), type(type), password(password) {}

    // Getter methods
    int getId() const { return id; }

    string getName() const { return name; }

    string getType() const { return type; }

    string getPassword() const { return password; }

    // Setter methods
    void setId(int id) { this->id = id; }

    void setName(const string& name) { this->name = name; }

    void setType(const string& type) { this->type = type; }

    void setPassword(const string& password) { this->password = password; }

    void display() const {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
    }
};

// Borrower class
class Borrower {
private:
    int id;
    string type;
    vector<string> borrowedBooks;

public:
    Borrower(const int& id, const string& type) : id(id), type(type) {}

    // Getter methods
    int getId() const { return id; }

    string getType() const { return type; }

    vector<string> getBorrowedBooks() const { return borrowedBooks; }

    // Setter methods
    void setId(const string& name) { this->id = id; }

    void setType(const string& type) { this->type = type; }

    void borrowBook(string bookId) { borrowedBooks.push_back(bookId); }
    void setBorrowedBooks(const vector<string>& ids) { borrowedBooks = ids; }
    void returnBook(string bookId) {
        // Find and remove the book from the borrowedBooks vector
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == bookId) {
                borrowedBooks.erase(it);
                return;
            }
        }
    }

    bool hasBorrowedBook(string bookId) const {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        return it != borrowedBooks.end();
    }

    void addBorrowedBook(string bookId) {
        if (!hasBorrowedBook(bookId)) {
            borrowedBooks.push_back(bookId);
        }
    }

    void removeBorrowedBook(const string& bookId) {
        // Find and remove the book from the borrowedBooks vector
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }

    void display() const {
        cout << "Id: " << id << endl;
        cout << "Type: " << type << endl;
        cout << "Borrowed Books: " << endl;
        if (borrowedBooks.empty()) {
            cout << "None" << endl;
        }
        else {
            for (string bookId : borrowedBooks) {
                cout << "Book ID: " << bookId << endl;
            }
        }
    }
};

// Library Class
class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<User> users;

public:
    //Load All information & Data from Text file
    void load(const string& bookFile, const string& borrowerFile,
        const string& userFile) {
        loadBooks(bookFile);
        loadBorrowers(borrowerFile);
        loadUsers(userFile);
    }

    //Load Book Data
    void loadBooks(const string& bookFile) {
        ifstream file(bookFile);
        if (!file.is_open()) {
            cout << "Failed to open book file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string title, author, ISBN, type, availableCopiesStr, reservedIdsStr;

            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, ISBN, ',');
            getline(ss, type, ',');
            getline(ss, availableCopiesStr, ',');
            getline(ss, reservedIdsStr, ',');

            int availableCopies = stoi(availableCopiesStr);
            vector<int> reservedIds;

            if (!reservedIdsStr.empty()) {
                stringstream reservedIdsStream(reservedIdsStr);
                string reservedIdStr;
                while (getline(reservedIdsStream, reservedIdStr, ',')) {
                    reservedIds.push_back(stoi(reservedIdStr));
                }
            }

            Book book(title, author, ISBN, type, availableCopies);
            book.setReservedIds(reservedIds);

            books.push_back(book);
        }

        file.close();
    }

    //Load Borrowers Information
    void loadBorrowers(const string& borrowerFile) {
        ifstream file(borrowerFile);
        if (!file.is_open()) {
            cout << "Failed to open borrower file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, type, borrowedBooksStr;

            getline(ss, idStr, ',');
            getline(ss, type, ',');
            getline(ss, borrowedBooksStr, ',');

            int id = stoi(idStr);
            vector<string> borrowedBooks;

            if (!borrowedBooksStr.empty()) {
                stringstream borrowedBooksStream(borrowedBooksStr);
                string borrowedBookStr;
                while (getline(borrowedBooksStream, borrowedBookStr, ',')) {
                    borrowedBooks.push_back(borrowedBookStr);
                }
            }

            Borrower borrower(id, type);
            borrower.setBorrowedBooks(borrowedBooks);

            borrowers.push_back(borrower);
        }

        file.close();
    }

    //Add User Information
    void addUser() {
        int userId;
        string userName, userType, userPassword;

        cout << "Enter user ID: ";
        cin >> userId;
        cin.ignore();

        // Check if the user ID is already present
        auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getId() == userId;
            });

        if (userIt != users.end()) {
            cout << "User ID " << userId << " is already taken. Please choose a different ID." << endl;
            return;
        }

        cout << "Enter user name: ";
        getline(cin, userName);
        bool correct = false;
        do
        {
            cout << "Enter user type: ";
            getline(cin, userType);

            if (userType != "student" && userType != "teacher" && userType != "researcher")
            {
                cout << "Invalid userType(it can be student , teacher or researcher)" << endl;

            }
            else
            {
                correct = true;
            }

        } while (correct == false);
        cout << "Enter user password: ";
        getline(cin, userPassword);
        User newUser(userId, userName, userType, userPassword);
        users.push_back(newUser);

        cout << "New user added successfully!" << endl;
    }

    //Modify User
    void modifyuser() {
        int userid;
        cout << "Enter user ID to modify: ";
        cin >> userid;
        bool found = false;
        for (User& user : users) {
            if (user.getId() == userid) {
                string username;
                cout << "Enter user name: ";
                cin.ignore();
                getline(cin, username);
                user.setName(username);
                found = true;
                cout << "user Name modified successfully." << endl;
                break;
            }
        }
    }

    //delete user
    void deleteuser(int userId) {
        auto it = std::find_if(users.begin(), users.end(),
            [&](const User& user) {
                return user.getId() == userId;
            });

        if (it != users.end()) {
            users.erase(it);
            cout << "User with ID " << userId << " has been deleted." << endl;
        }
        else {
            cout << "User with ID " << userId << " not found." << endl;
        }
    }


    //Load User Data
    void loadUsers(const string& userFile) {
        ifstream file(userFile);
        if (!file.is_open()) {
            cout << "Failed to open user file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, name, type, password;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, type, ',');
            getline(ss, password, ',');

            int id = stoi(idStr);
            User user = User(id, name, type, password);
            users.push_back(user);
        }
        file.close();
    }

    //Save Books
    void saveBooks(const string& bookFile) {
        ofstream file(bookFile);
        if (!file.is_open()) {
            cout << "Failed to open book file for saving." << endl;
            return;
        }

        for (const Book& book : books) {
            file << book.getTitle() << "," << book.getAuthor() << ","
                << book.getISBN() << "," << book.getType() << ","
                << book.getAvailableCopies() << ",";

            vector<int> reservedIds = book.getReservedIds();
            if (!reservedIds.empty()) {
                for (int i = 0; i < reservedIds.size() - 1; i++) {
                    file << reservedIds[i] << ",";
                }
                file << reservedIds[reservedIds.size() - 1];
            }
            file << endl;
        }

        file.close();
    }

    //Save Borrowers
    void saveBorrowers(const string& borrowerFile) {
        ofstream file(borrowerFile);
        if (!file.is_open()) {
            cout << "Failed to open borrower file for saving." << endl;
            return;
        }

        for (const Borrower& borrower : borrowers) {
            file << borrower.getId() << "," << borrower.getType() << ",";

            vector<string> borrowedBooks = borrower.getBorrowedBooks();
            if (!borrowedBooks.empty()) {
                for (int i = 0; i < borrowedBooks.size() - 1; i++) {
                    file << borrowedBooks[i] << ",";
                }
                file << borrowedBooks[borrowedBooks.size() - 1];
            }
            file << endl;
        }

        file.close();
    }

    //Save User
    void saveUsers(const string& userFile) {
        ofstream file(userFile);
        if (!file.is_open()) {
            cout << "Failed to open user file for saving." << endl;
            return;
        }

        for (const User& user : users) {
            file << user.getId() << "," << user.getName() << "," << user.getType()
                << "," << user.getPassword() << endl;
        }

        file.close();
    }

    //Save data on text file
    void save(const string& bookFile, const string& borrowerFile,
        const string& userFile) {
        saveBooks(bookFile);
        saveBorrowers(borrowerFile);
        saveUsers(userFile);
    }

    //book deleteMethod
    void deleteBook(const string& ISBN) {
        // Find the book with the specified ISBN
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getISBN() == ISBN;
            });

        if (it != books.end()) {
            // Book found, erase it from the vector
            books.erase(it);
            cout << "Book with ISBN " << ISBN << " has been deleted." << endl;
        }
        else {
            cout << "Book with ISBN " << ISBN << " not found." << endl;
        }
    }

    //Insert Book
    void insertBook() {
        string title, author, ISBN, type;
        int availableCopies;

        cout << "Enter book details:" << endl;
        cout << "Title: ";
        getline(cin, title);

        cout << "Author: ";
        getline(cin, author);

        cout << "ISBN: ";
        getline(cin, ISBN);

        cout << "Type: ";
        getline(cin, type);

        cout << "Available Copies: ";
        cin >> availableCopies;
        cin.ignore(); // Ignore the newline character

        Book book(title, author, ISBN, type, availableCopies);
        books.push_back(book);

        cout << "Book inserted successfully." << endl;
    }

    //Book Modify
    void modifyBook(const string& ISBN) {
        auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getISBN() == ISBN;
            });

        if (it != books.end()) {
            string newTitle, newAuthor, newType;
            int newAvailableCopies;

            cout << "Enter new book details:" << endl;
            cout << "Title: ";
            getline(cin, newTitle);

            cout << "Author: ";
            getline(cin, newAuthor);

            cout << "Type: ";
            getline(cin, newType);

            cout << "Available Copies: ";
            cin >> newAvailableCopies;
            cin.ignore(); // Ignore the newline character

            // Update the book with the new information
            it->setTitle(newTitle);
            it->setAuthor(newAuthor);
            it->setType(newType);
            it->setAvailableCopies(newAvailableCopies);

            cout << "Book modified successfully." << endl;
        }
        else {
            cout << "Book with ISBN " << ISBN << " not found." << endl;
        }
    }

    //Search Book
    void searchBook() {
        string searchType;
        string searchTerm;

        cout << "Enter the search type (name or ISBN): ";
        cin >> searchType;
        cin.ignore(); // Ignore the newline character

        cout << "Enter the search term (bookname or ISBN#: ";
        getline(cin, searchTerm);

        vector<Book> foundBooks;

        if (searchType == "name") {
            for (const Book& book : books) {
                if (book.getTitle() == searchTerm) {
                    foundBooks.push_back(book);
                }
            }
        }
        else if (searchType == "ISBN") {
            auto it = std::find_if(books.begin(), books.end(), [&](const Book& book) {
                return book.getISBN() == searchTerm;
                });

            if (it != books.end()) {
                foundBooks.push_back(*it);
            }
        }

        if (!foundBooks.empty()) {
            cout << "Found " << foundBooks.size()
                << " book(s) matching the search criteria:" << endl;
            for (const Book& book : foundBooks) {
                book.display();
            }
        }
        else {
            cout << "No books found matching the search criteria." << endl;
        }
    }

    //Delete Borrower
    void deleteBorrower(int borrowerId) {
        auto it = std::find_if(borrowers.begin(), borrowers.end(),
            [&](const Borrower& borrower) {
                return borrower.getId() == borrowerId;
            });

        if (it != borrowers.end()) {
            borrowers.erase(it);
            cout << "Borrower with ID " << borrowerId << " has been deleted." << endl;
        }
        else {
            cout << "Borrower with ID " << borrowerId << " not found." << endl;
        }
    }

    //Insert Borrower
    void insertBorrower() {
        int id;
        string type;
        cout << "Enter borrower ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter borrower type: ";
        getline(cin, type);

        Borrower borrower(id, type);
        borrowers.push_back(borrower);

        cout << "Borrower inserted successfully." << endl;
    }

    //Modify Borrower
    void modifyBorrower() {
        int id;
        cout << "Enter borrower ID to modify: ";
        cin >> id;

        bool found = false;
        for (Borrower& borrower : borrowers) {
            if (borrower.getId() == id) {
                string newType;
                cout << "Enter new borrower type: ";
                cin.ignore();
                getline(cin, newType);

                borrower.setType(newType);
                found = true;
                cout << "Borrower modified successfully." << endl;
                break;
            }
        }

        if (!found) {
            cout << "Borrower not found." << endl;
        }
    }

    //Search Borrower By ID
    void searchBorrowerByID(int borrowerID) {
        auto it = find_if(borrowers.begin(), borrowers.end(),
            [&](const Borrower& borrower) {
                return borrower.getId() == borrowerID;
            });

        if (it != borrowers.end()) {
            Borrower& borrower = *it;
            cout << "Borrower ID: " << borrower.getId() << endl;
            cout << "Borrower Type: " << borrower.getType() << endl;

            // Display borrowed books, if any
            vector<string> borrowedBooks = borrower.getBorrowedBooks();
            if (!borrowedBooks.empty()) {
                cout << "Borrowed Books: ";
                for (string bookID : borrowedBooks) {
                    cout << bookID << " ";
                }
                cout << endl;
            }
            else {
                cout << "No books currently borrowed." << endl;
            }
        }
        else {
            cout << "Borrower with ID " << borrowerID << " not found." << endl;
        }
    }

    //Check User Login
    void checkUserLogin(int userID, const string& userType) {
        auto it = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getId() == userID && user.getType() == userType;
            });

        if (it != users.end()) {
            cout << "Login successful" << endl;
        }
        else {
            cout << "User not found or incorrect credentials" << endl;
        }
    }

    //Reserve Book
    void reserveBook(const string& ISBN, int userID) {
        // Find the book by ISBN
        auto bookIt = find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getISBN() == ISBN;
            });

        // Find the user by ID
        auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getId() == userID;
            });

        // Check if both book and user exist
        if (bookIt != books.end() && userIt != users.end()) {
            Book& book = *bookIt;
            User& user = *userIt;

            // Add the user ID to the reserved IDs of the book
            book.addReservedId(userID);

            cout << "Book with ISBN " << ISBN << " reserved for user with ID "
                << userID << endl;
        }
        else {
            cout << "Invalid ISBN or user ID. Reservation failed." << endl;
        }
    }

    //Borrow Book
    void borrowBook(const string& ISBN, int userID) {
        // Find the book with the given ISBN
        auto bookIt = find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.getISBN() == ISBN;
            });

        // Check if the book exists
        if (bookIt != books.end()) {
            Book& book = *bookIt;

            // Find the borrower with the given user ID
            auto borrowerIt = find_if(
                borrowers.begin(), borrowers.end(),
                [&](const Borrower& borrower) { return borrower.getId() == userID; });

            // Check if the borrower exists
            if (borrowerIt != borrowers.end()) {
                Borrower& borrower = *borrowerIt;

                // Decrease the available copies of the book
                int availableCopies = book.getAvailableCopies();
                if (availableCopies > 0) {
                    book.setAvailableCopies(availableCopies - 1);

                    // Check if the user is already a borrower
                    if (borrower.hasBorrowedBook(ISBN)) {
                        borrower.addBorrowedBook(ISBN);
                        cout << "Book borrowed successfully." << endl;
                    }
                    else {
                        // Add the book to the borrower's borrowed books vector
                        borrower.addBorrowedBook(ISBN);
                        cout << "User is a new borrower. Book borrowed successfully."
                            << endl;
                    }
                }
                else {
                    cout << "Sorry, no available copies of the book." << endl;
                }
            }
            else {
                cout << "Borrower not found." << endl;
            }
        }
        else {
            cout << "Book not found." << endl;
        }
    }

    //Return Book
    void returnBook(int userID) {
        // Find the borrower by ID
        auto borrowerIt = find_if(borrowers.begin(), borrowers.end(), [&](const Borrower& borrower) {
            return borrower.getId() == userID;
            });

        if (borrowerIt != borrowers.end()) {
            Borrower& borrower = *borrowerIt;

            // Display borrowed books
            borrower.display();

            // Ask for the book to be returned
            cout << "Enter the ID of the book you want to return: ";
            string bookID;
            cin >> bookID;
            if (borrower.hasBorrowedBook(bookID)) {
                cout << "The book with ID " << bookID << " is borrowed by the borrower." << endl;
            }
            else {
                cout << "The book with ID " << bookID << " is not borrowed by the borrower." << endl;
                return;
            }
            // Remove the book from the borrower's borrowed books
            borrower.returnBook(bookID);

            cout << "Book with ID " << bookID << " returned by user with ID " << userID << endl;
        }
        else {
            cout << "Invalid user ID. Return book failed." << endl;
        }
    }

    //Check Password & login 
    bool checkUserPresence(int userID, const string& userType,
        const string& password) {
        // Find the user with the given ID and type
        auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.getId() == userID && user.getType() == userType;
            });
        // Check if the user exists and verify the password
        if (userIt == users.end() || userIt->getPassword() != password) {
            cout << userType << " with ID " << userID
                << " and provided password is not valid." << endl;
            return false;
        }
        else {
            cout << userIt->getName() << " Login Successful" << endl;
            return true;
        }
    }
};

// Main Fubction
int main() {
    Library library;
    library.load("books.txt", "borrowers.txt", "users.txt");

    string userType;
    bool correction = false;
    do
    {
        cout << "***********************************************************" << endl;
        cout << "****************** Welcome to our Library *****************" << endl;
        cout << "***********************************************************" << endl;
        cout << "->> Please Select Your Choice " << endl;
        cout << "->> Want to enter as( a user) or  (an admin) ? ";
        getline(cin, userType);

        if (userType == "admin") {
            correction = true;
            string adminPassword;
            cout << "Enter admin password: ";
            cin >> adminPassword;
            cin.ignore();
            // Check if the admin password is correct
            if (adminPassword == "admin123") {
                string adminChoice;
                while (true) {
                    cout << "Admin Menu:" << endl;
                    cout << "1. Insert Book" << endl;
                    cout << "2. Modify Book" << endl;
                    cout << "3. Delete Book" << endl;
                    cout << "4. Search Book" << endl;
                    cout << "5. Add User" << endl;
                    cout << "6. Modify User" << endl;
                    cout << "7. Delete User" << endl;
                    cout << "8. Insert Borrower" << endl;
                    cout << "9. Modify Borrower" << endl;
                    cout << "10. Delete Borrower" << endl;
                    cout << "11. Save and Exit" << endl;

                    cout << "Enter your choice: ";
                    getline(cin, adminChoice);

                    if (adminChoice == "1") {
                        library.insertBook();
                    }
                    else if (adminChoice == "2") {
                        string ISBN;
                        cout << "Enter the ISBN of the book to modify: ";
                        getline(cin, ISBN);
                        library.modifyBook(ISBN);
                    }
                    else if (adminChoice == "3") {
                        string ISBN;
                        cout << "Enter the ISBN of the book to delete: ";
                        getline(cin, ISBN);
                        library.deleteBook(ISBN);
                    }
                    else if (adminChoice == "4") {
                        library.searchBook();
                    }
                    else if (adminChoice == "5") {
                        library.addUser();
                    }
                    else if (adminChoice == "6") {
                        library.modifyuser();
                    }
                    else if (adminChoice == "7") {
                        int userId;
                        cout << "Enter user Id: ";
                        cin >> userId;
                        cin.ignore();
                        library.deleteuser(userId);
                    }
                    else if (adminChoice == "8") {
                        library.insertBorrower();
                    }
                    else if (adminChoice == "9") {
                        library.modifyBorrower();
                    }
                    else if (adminChoice == "10") {
                        int borrowerId;
                        cout << "Enter the ID of the borrower to delete: ";
                        cin >> borrowerId;
                        cin.ignore();
                        library.deleteBorrower(borrowerId);
                    }
                    else if (adminChoice == "11") {
                        library.save("books.txt", "borrowers.txt", "users.txt");
                        break;
                    }
                    else {
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            else {
                cout << "Invalid admin password. Access denied." << endl;
            }
        }
        else if (userType == "user") {
            correction = true;
            // Check if the user wants to create a new account
            string createAccountChoice;
            cout << "Do you want to create a new account? (yes/no): ";
            cin >> createAccountChoice;
            cin.ignore();

            if (createAccountChoice == "yes") {
                library.addUser();
                correction = false;
            }
            else {

                bool pcheck = false;
                do
                {
                    int userId;
                    string userT, userpass;
                    cout << "Enter your ID: ";
                    cin >> userId;
                    cout << "Enter user option (teacher ,student, researcher):";
                    cin >> userT;
                    cout << "Enter Password:";
                    cin >> userpass;
                    cin.ignore();
                    if (library.checkUserPresence(userId, userT, userpass)) {
                        string userChoice;
                        pcheck = true;
                        while (true) {
                            cout << "User Menu:" << endl;
                            cout << "1. Borrow Book" << endl;
                            cout << "2. Reserve Book" << endl;
                            cout << "3. Return Book" << endl;
                            cout << "4. Search Book" << endl;
                            cout << "5. Exit" << endl;

                            cout << "Enter your choice: ";
                            getline(cin, userChoice);

                            if (userChoice == "1") {
                                string ISBN;
                                cout << "Enter the ISBN of the book to borrow: ";
                                getline(cin, ISBN);
                                library.borrowBook(ISBN, userId);
                            }
                            else if (userChoice == "2") {
                                string ISBN;
                                cout << "Enter the ISBN of the book to reserve: ";
                                getline(cin, ISBN);
                                library.reserveBook(ISBN, userId);
                            }
                            else if (userChoice == "3") {

                                library.returnBook(userId);

                            }
                            else if (userChoice == "4") {
                                library.searchBook();

                            }
                            else if (userChoice == "5") {
                                library.save("books.txt", "borrowers.txt", "users.txt");
                                break;
                            }
                            else {
                                cout << "Invalid choice. Please try again." << endl;
                            }
                        }
                    }
                } while (pcheck == false);
            }
        }
        else
        {
            cout << "Invalid choose" << endl;
        }
    } while (correction == false);
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
