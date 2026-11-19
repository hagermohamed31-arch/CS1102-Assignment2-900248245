#include "LibraryData.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
using namespace std;
void loadSampleData(vector<Book>& books, map<string, User>& users, set<string>& categories) {
   users.emplace("librarian", User("librarian", "libpass", true));
    users.emplace("member1", User("member1", "pass1", false));
    users.emplace("member2", User("member2", "pass2", false))   ;
    books.push_back(Book("978-3-16-148410-0", "C Programming", "Bjarne Stroustrup", "Programming", 2013, false, false));
    books.push_back(Book("978-0-13-110362-7", "The C++ Programming Language", "Brian W. Kernighan", "Programming", 1988, false, true));
    books.back().borrowedBy = "member2";
    books.back().waitingList.push("member1");
    books.push_back(Book("978-0-201-83595-3", "Design Patterns", "Erich Gamma", "Software Engineering", 1994, false, false));
    books.push_back(Book("978-0-596-52068-7", "Head First Design Patterns", "Eric Freeman", "Software Engineering", 2004, false, false));
    books.push_back(Book("978-0-321-56384-2", "Clean Code", "Robert C. Martin", "Software Engineering", 2008, false, false));
    books.push_back(Book("978-0-262-03384-8", "Introduction to Algorithms", "Thomas H. Cormen", "Algorithms", 2009, true, false));
    for (const auto& book : books) {
        categories.insert(book.category);}
}
void printBook(const Book& b) {            
    cout << b.title << ", by " << b.author << ", " << b.year << ", " << b.category << ", ISBN " << b.isbn << ". Status: ";
    if (b.isBorrowed) {
        cout << "Borrowed by " << b.borrowedBy << endl;
    } else if (b.isReferenceOnly) {
        cout << "Reference only" << endl;
    }
    else {
        cout << "Available" << endl;
    }
}
void runWelcomeMenu(map<string, User>& users, vector<Book>& books, set<string>& categories) {
    int choice;
    while (true) {
        cout << "1. Log in" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice:" << endl; 
        cin >> choice;        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Error: invalid choice." << endl;   
            continue;
        }
        cin.ignore(1000, '\n');
        if (choice == 1) {
            for (int attempt = 1; attempt <= 3; ++attempt) {
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password); 
                auto it = users.find(username);
                if (it != users.end() && it->second.password == password) {
                    cout << "Done: welcome, " << username << ". You are logged in as a " << (it->second.isLibrarian ? "Librarian" : "Member") << "." << endl;                    
if (it->second.isLibrarian) {
                        runLibrarianMenu(users, books, categories);
}
                                    break;
                } else {
                    int attemptsLeft = 3 - attempt;
                    if (attemptsLeft > 0) {
                        cout << "Error: invalid username or password. You have " << attemptsLeft << " attempts left." << endl;
                    } else {
                        cout << "Error: invalid username or password. You have 0 attempts left. Returning to welcome menu." << endl;                }                         }    
                    }
        } else if (choice == 2) {
            cout << "Done: exiting the system. Goodbye!" << endl; 
            break;
        } else {
            cout << "Error: invalid choice." << endl; 
        }
    }
}
void runLibrarianMenu(map<string, User>& users, vector<Book>& books, set<string>& categories) {
    int choice;
    while (true) {
        cout << "1. List all books (sorted by title)" << endl;
        cout << "2. List books by category" << endl;
        cout << "3. Library statistics" << endl;
        cout << "4. Add a new book" << endl;
        cout << "5. Search, borrow and return" << endl;
        cout << "6. Delete a book" << endl;
        cout << "7. Undo last delete" << endl;
        cout << "8. Log out" << endl;
        cout << "Enter your choice:" << endl;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: invalid choice." << endl;
            continue;
        }
                cin.ignore(1000, '\n');
        switch (choice) {
            case 1:
                sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
    return a.title < b.title;
});
for (auto it = books.begin(); it != books.end(); ++it) {
    printBook(*it);
}
                break;
            case 2:
                // Implementation for listing books by category
                break;
            case 3:
                // Implementation for library statistics
                break;
            case 4:
                // Implementation for adding a new book
                cout << "This option is not ready yet."<< endl;
                break;
            case 5:
                // Implementation for search, borrow and return
                cout << "This option is not ready yet."<< endl;
                break;
            case 6:
                // Implementation for deleting a book
                cout << "This option is not ready yet."<< endl;
                break;
            case 7:
                // Implementation for undoing last delete
                cout << "This option is not ready yet."<< endl;
                break;
            case 8:
                // Implementation for logging out
                return; 
        default:
            cout << "Error: invalid choice." << endl;   
        }
    }
}