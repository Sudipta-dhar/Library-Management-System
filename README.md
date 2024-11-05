# Library Management System

## Overview

The **Library Management System** is a comprehensive C++ application designed to manage library operations efficiently. It features robust functionality for managing books, users, and borrowers, making it an ideal solution for academic and public libraries. The system leverages role-based access control, ensuring different levels of access for administrators and regular users, while also providing a persistent data management system that loads and saves records from text files.

## Key Features

### 1. **Role-Based Access Control**
   - Differentiates between **admin** and **user** roles.
   - **Admins** can:
     - Add, modify, delete, and search for books.
     - Manage borrower information and system data.
   - **Users** (students, teachers, researchers) have restricted access based on their role, with tailored permissions for borrowing and reserving books.

### 2. **Comprehensive User and Book Management**
   - Admins can perform full CRUD (Create, Read, Update, Delete) operations on book and user records.
   - Users are categorized into types (student, teacher, researcher), providing an organized system to handle different user requirements.
   - Book details include title, author, ISBN, type, available copies, and reservation information.

### 3. **Reservation and Borrowing System**
   - Users can **reserve books**, and the system tracks the IDs of users who have reserved each book.
   - The borrowing feature ensures that the number of available copies is updated in real-time, and users can return books to make them available for others.

### 4. **Data Persistence**
   - The system reads and writes data to external text files (`books.txt`, `borrowers.txt`, `users.txt`), making sure that all records are preserved between sessions.
   - Efficient data parsing and saving mechanisms ensure data integrity and easy recovery.

### 5. **Interactive Console Interface**
   - A user-friendly, menu-driven interface guides both admins and users through various operations.
   - Admins have access to a detailed admin menu, while regular users are prompted based on their specific permissions.

### 6. **Error Handling and Input Validation**
   - The program includes checks for invalid input, such as incorrect user roles or passwords.
   - Clear error messages are displayed for file loading issues, invalid operations, and incorrect credentials.

### 7. **Efficient Use of Algorithms and Data Structures**
   - Uses **linear search** (`find_if`) for searching through books, users, and borrowers.
   - Utilizes the **Erase-Remove Idiom** for efficient removal of elements from `std::vector`.
   - Employs `std::vector` for dynamic and efficient data management.

## Technologies Used

- **C++**: Core programming language used for implementing the system.
- **Standard Template Library (STL)**: Utilized for efficient data management and algorithmic operations.
- **File I/O**: Used for persistent data storage and retrieval.

## Installation and Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/library-management-system.git
   ```
2. **Compile the Code**:
   - Use a C++ compiler like `g++` to compile the code:
     ```bash
     g++ -o library_management LibraryManageSystem.cpp
     ```
3. **Run the Program**:
   ```bash
   ./library_management
   ```

## Usage

1. **Admin Access**:
   - Enter "admin" when prompted and use the default admin password ("admin123").
   - Admin functionalities include inserting, modifying, deleting, and searching for books, as well as managing borrowers.

2. **User Access**:
   - Users can log in with their ID and type to borrow or reserve books.
   - User roles include:
     - **Student**: Can borrow and return books.
     - **Teacher**: Can borrow and reserve books.
     - **Researcher**: Special privileges based on system setup.

3. **Data Management**:
   - The system loads data from `books.txt`, `borrowers.txt`, and `users.txt` at startup and saves any changes upon exit.

## Example Operations

### Admin Menu
1. Insert a new book.
2. Modify book details.
3. Delete a book by ISBN.
4. Search for a book by name or ISBN.
5. Manage borrower records.

### User Menu
- Borrow a book by ISBN.
- Return a borrowed book.
- Reserve a book for future borrowing.

## Contributing

Contributions are welcome! To contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/your-feature`).
3. Commit your changes (`git commit -m 'Add your message here'`).
4. Push to the branch (`git push origin feature/your-feature`).
5. Open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- **Other Group Members**: Subodh, Ibrahim, and Walid for developing this system.
- **C++ Standard Library**: For providing efficient data structures and algorithms.

---

Feel free to customize this README to fit your project specifics better or add any additional information!
