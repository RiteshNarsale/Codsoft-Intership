#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Book class to store book details
class Book {
public:
    int bookID;
    string title;
    string author;
    string isbn;
    bool isAvailable;

    Book(int id, string t, string a, string i) {
        bookID = id;
        title = t;
        author = a;
        isbn = i;
        isAvailable = true;
    }
};

// Transaction class to manage checkouts and returns
class Transaction {
public:
    int bookID;
    string borrowerName;
    time_t checkoutDate;
    time_t returnDate;

    Transaction(int bID, string name) {
        bookID = bID;
        borrowerName = name;
        checkoutDate = time(0);
        returnDate = 0;
    }

    // Set return date and calculate fine if overdue
    double calculateFine(time_t returnTime) {
        double finePerDay = 1.0; // Fine of $1 per day
        double fine = 0.0;

        // If the book is returned late
        if (returnTime > checkoutDate) {
            int daysOverdue = difftime(returnTime, checkoutDate) / (60 * 60 * 24);
            fine = daysOverdue * finePerDay;
        }
        return fine;
    }
};

// Library class to manage the collection and transactions
class Library {
private:
    vector<Book> books;
    vector<Transaction> transactions;

public:
    // Add a new book to the library
    void addBook(int bookID, string title, string author, string isbn) {
        books.push_back(Book(bookID, title, author, isbn));
    }

    // Search books by title, author, or ISBN
    void searchBooks(string searchTerm) {
        bool found = false;
        for (auto &book : books) {
            if (book.title.find(searchTerm) != string::npos ||
                book.author.find(searchTerm) != string::npos ||
                book.isbn.find(searchTerm) != string::npos) {
                cout << "Book Found: " << book.title << " by " << book.author << " (ISBN: " << book.isbn << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No books found with that search term.\n";
        }
    }

    // Check out a book
    void checkoutBook(int bookID, string borrowerName) {
        for (auto &book : books) {
            if (book.bookID == bookID && book.isAvailable) {
                book.isAvailable = false;
                transactions.push_back(Transaction(bookID, borrowerName));
                cout << borrowerName << " successfully checked out " << book.title << ".\n";
                return;
            }
        }
        cout << "Book not available for checkout.\n";
    }

    // Return a book and calculate fine if overdue
    void returnBook(int bookID) {
        for (auto &book : books) {
            if (book.bookID == bookID) {
                if (!book.isAvailable) {
                    book.isAvailable = true;
                    time_t returnTime = time(0);

                    // Find the transaction for this book
                    for (auto &transaction : transactions) {
                        if (transaction.bookID == bookID && transaction.returnDate == 0) {
                            transaction.returnDate = returnTime;
                            double fine = transaction.calculateFine(returnTime);
                            cout << "Book " << book.title << " returned.\n";
                            if (fine > 0) {
                                cout << "Fine for overdue: $" << fine << "\n";
                            } else {
                                cout << "No fine, book returned on time.\n";
                            }
                            return;
                        }
                    }
                } else {
                    cout << "This book was not checked out.\n";
                }
            }
        }
        cout << "Book not found.\n";
    }

    // List all available books
    void listAvailableBooks() {
        bool found = false;
        for (auto &book : books) {
            if (book.isAvailable) {
                cout << "Available: " << book.title << " by " << book.author << " (ISBN: " << book.isbn << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No books are available.\n";
        }
    }
};

int main() {
    Library library;

    // Sample Books
    library.addBook(1, "C++ Programming", "Bjarne Stroustrup", "978-0321563842");
    library.addBook(2, "The Catcher in the Rye", "J.D. Salinger", "978-0316769488");
    library.addBook(3, "1984", "George Orwell", "978-0451524935");

    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Search Book\n";
        cout << "2. Checkout Book\n";
        cout << "3. Return Book\n";
        cout << "4. List Available Books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string searchTerm;
            cout << "Enter title, author, or ISBN to search: ";
            getline(cin, searchTerm);
            library.searchBooks(searchTerm);
            break;
        }
        case 2: {
            int bookID;
            string borrowerName;
            cout << "Enter book ID to checkout: ";
            cin >> bookID;
            cin.ignore();
            cout << "Enter borrower name: ";
            getline(cin, borrowerName);
            library.checkoutBook(bookID, borrowerName);
            break;
        }
        case 3: {
            int bookID;
            cout << "Enter book ID to return: ";
            cin >> bookID;
            library.returnBook(bookID);
            break;
        }
        case 4:
            library.listAvailableBooks();
            break;
        case 5:
            cout << "Exiting the system.\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
