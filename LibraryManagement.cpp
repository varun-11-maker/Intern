#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Book class
class Book {
private:
    int bookID;
    string title;
    string author;
    bool isAvailable;

public:
    Book(int id, const string& t, const string& a) 
        : bookID(id), title(t), author(a), isAvailable(true) {}

    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getAvailability() const { return isAvailable; }

    void checkOut() { isAvailable = false; }
    void returnBook() { isAvailable = true; }

    void displayBookInfo() const {
        cout << "Book ID: " << bookID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Patron class
class Patron {
private:
    int patronID;
    string name;
    vector<int> borrowedBooks;

public:
    Patron(int id, const string& n) : patronID(id), name(n) {}

    int getPatronID() const { return patronID; }
    string getName() const { return name; }

    void borrowBook(int bookID) {
        borrowedBooks.push_back(bookID);
    }

    void returnBook(int bookID) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }

    void displayPatronInfo() const {
        cout << "Patron ID: " << patronID << endl;
        cout << "Name: " << name << endl;
        cout << "Borrowed Books: ";
        for (int bookID : borrowedBooks) {
            cout << bookID << " ";
        }
        cout << endl;
    }
};

// Library class
class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void addPatron(const Patron& patron) {
        patrons.push_back(patron);
    }

    void displayBooks() const {
        for (const auto& book : books) {
            book.displayBookInfo();
            cout << "---------------------" << endl;
        }
    }

    void displayPatrons() const {
        for (const auto& patron : patrons) {
            patron.displayPatronInfo();
            cout << "---------------------" << endl;
        }
    }

    void checkOutBook(int bookID, int patronID) {
        auto bookIt = find_if(books.begin(), books.end(), 
            [bookID](const Book& book) { return book.getBookID() == bookID; });

        if (bookIt != books.end() && bookIt->getAvailability()) {
            auto patronIt = find_if(patrons.begin(), patrons.end(), 
                [patronID](const Patron& patron) { return patron.getPatronID() == patronID; });

            if (patronIt != patrons.end()) {
                bookIt->checkOut();
                patronIt->borrowBook(bookID);
                cout << "Book checked out successfully." << endl;
            } else {
                cout << "Patron not found." << endl;
            }
        } else {
            cout << "Book not available or not found." << endl;
        }
    }

    void returnBook(int bookID, int patronID) {
        auto bookIt = find_if(books.begin(), books.end(), 
            [bookID](const Book& book) { return book.getBookID() == bookID; });

        if (bookIt != books.end()) {
            auto patronIt = find_if(patrons.begin(), patrons.end(), 
                [patronID](const Patron& patron) { return patron.getPatronID() == patronID; });

            if (patronIt != patrons.end()) {
                bookIt->returnBook();
                patronIt->returnBook(bookID);
                cout << "Book returned successfully." << endl;
            } else {
                cout << "Patron not found." << endl;
            }
        } else {
            cout << "Book not found." << endl;
        }
    }
};

// Function to display the menu
void displayMenu() {
    cout << "\nLibrary Management System" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add Patron" << endl;
    cout << "3. Display Books" << endl;
    cout << "4. Display Patrons" << endl;
    cout << "5. Check Out Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Library library;
    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, author;
                cout << "Enter book ID: ";
                cin >> id;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(Book(id, title, author));
                break;
            }
            case 2: {
                int id;
                string name;
                cout << "Enter patron ID: ";
                cin >> id;
                cout << "Enter patron name: ";
                cin.ignore();
                getline(cin, name);
                library.addPatron(Patron(id, name));
                break;
            }
            case 3:
                library.displayBooks();
                break;
            case 4:
                library.displayPatrons();
                break;
            case 5: {
                int bookID, patronID;
                cout << "Enter book ID to check out: ";
                cin >> bookID;
                cout << "Enter patron ID: ";
                cin >> patronID;
                library.checkOutBook(bookID, patronID);
                break;
            }
            case 6: {
                int bookID, patronID;
                cout << "Enter book ID to return: ";
                cin >> bookID;
                cout << "Enter patron ID: ";
                cin >> patronID;
                library.returnBook(bookID, patronID);
                break;
            }
            case 7:
                running = false;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
