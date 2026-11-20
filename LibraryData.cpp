#include "LibraryData.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
#include<utility>
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
                } else {
                    runMemberMenu(username, books);
                }
                break;
            }
        else {
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
int getAvailableBookCount(const vector<Book>& books) {
    return std::count_if(books.begin(), books.end(), [](const Book& b) {
        return !b.isBorrowed && !b.isReferenceOnly;
    });
}
std::pair<int, int> getBookCounts(const vector<Book>& books) {
    int availableCount = getAvailableBookCount(books);
    int borrowedCount = std::count_if(books.begin(), books.end(), [](const Book& b) {
        return b.isBorrowed;
    });
    return std::make_pair(availableCount, borrowedCount);
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
    printBook(*it);}
                break;
            case 2:
{              
                int idx = 1;      
                for (const auto& cat : categories) {
                    cout << idx << ". " << cat << endl;
                    ++idx;                  }       
cout << "Enter your choice:" << endl;   
int catChoice;
cin >> catChoice;
if (cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Error: invalid choice." << endl;
    break; 
}
cin.ignore(1000, '\n'); 
if (catChoice < 1 || catChoice > static_cast<int>(categories.size())) {
    cout << "Error: invalid choice." << endl; 
    break; 
}
std::set<string>::iterator it = std::next(categories.begin(), catChoice - 1);
string selectedCategory = *it;
for (const auto& book : books) {
    if (book.category == selectedCategory) {    
        printBook(book);    
    }
}
                break;
}
            case 3: {
pair<int, int> counts = getBookCounts(books);
                    int referenceOnlyCount = std::count_if(books.begin(), books.end(), [](const Book& b) { return b.isReferenceOnly; });
                int memberCount = 0;
                for (const auto& entry : users) {
                    if (!entry.second.isLibrarian) {
                        ++memberCount;
                    }
                }
                cout << "Total books: " << books.size() << endl;
                cout << "Available: " << counts.first << endl;
                cout << "Borrowed: " << counts.second << endl;
                cout << "Reference only: " << referenceOnlyCount << endl;
                cout << "Categories: " << categories.size() << endl;
                cout << "Members: " << memberCount << endl;
                break;
            }
            case 4:
            addNewBook(books, categories);
                break;
          case 5: {
    int subChoice;
    cout << "1. Search for a book" << endl;
    cout << "2. Borrow a book" << endl;
    cout << "3. Return a book" << endl;
    cout << "4. Back" << endl;
    cout << "Enter your choice:" << endl;
    cin >> subChoice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: invalid choice." << endl;
        break;
    }
    cin.ignore(1000, '\n');
    if (subChoice == 1) searchBooks(books);
    else if (subChoice == 2) borrowBook("librarian", books);
    else if (subChoice == 3) returnBook("librarian", books);
    else if (subChoice != 4) cout << "Error: invalid choice." << endl;
    break;
}
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
std::pair<bool, int> findByIsbn(const std::vector<Book>& books, const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(), [&isbn](const Book& b) { return b.isbn == isbn; });
    if (it == books.end()) {
        return {false, -1};
    }
    return {true, static_cast<int>(std::distance(books.begin(), it))};
}
void addNewBook(std::vector<Book>& books, std::set<std::string>& categories) {
    std::string title, author, isbn, category, refInput;
    int year;
    bool isRef;

        while (true) {  
            cout << "Enter title: ";    
        std::getline(std::cin, title);
            if (title.empty()) {
                cout << "Error: title cannot be empty." << endl;
            }
                else {    
            break;
        }
    }   
        while (true) {
            cout << "Enter author: ";   
        std::getline(std::cin, author); 
            if (author.empty()) {
                cout << "Error: author cannot be empty." << endl;
            }   
            else {
            break;
        }
    }   
        while (true) {
            cout << "Enter ISBN: ";   
        std::getline(std::cin, isbn);
            if (isbn.empty()) {
                cout << "Error: ISBN cannot be empty." << endl;
            }      
            else {
                auto searchResult = findByIsbn(books, isbn);
                if (searchResult.first) {
                    cout << "Error: a book with this ISBN already exists." << endl;
                }   
else {
            break;
        }     
    }
}
   while (true) {
        cout << "Enter year: "; 
         cin >> year;   
            if (cin.fail()) {
            cout << "Error: invalid year." << endl;
            cin.clear();    
             cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
            }
             cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
if(year < 1450 || year > 2026) {
            cout << "Error: year must be between 1450 and 2026." << endl;
        } else {
            break;
        }
    }       
while (true) {
        cout << "Enter category: ";   
        std::getline(std::cin, category); 
        if (category.empty()) {
            cout << "Error: category cannot be empty." << endl;
        } else {
            break;
        }
    }   
        while (true) {
            cout << "Is this book reference-only? (y/n): ";
        std::getline(std::cin, refInput);
        if (refInput == "y" || refInput == "Y") {
            isRef = true;
            break;  
        }
            else if (refInput == "n" || refInput == "N") {
            isRef = false;  
            break;
        } else {
            cout << "Error: please enter y or n." << endl;
        }
    }
books.push_back(Book(isbn, title, author, category, year, isRef, false));   
  auto  insertResult = categories.insert(category); 
  if (insertResult.second) {
    cout << "New category added: " << category << "." << endl;
}
cout << "Done: " << title << " was added. The library now has " << books.size() << " books." << endl;
}       
void searchBooks(const std::vector<Book>& books) {
    int searchType;
    cout << "Search by" << endl;
    cout << "1. Title" << endl;
    cout << "2. Author" << endl;
    cout << "3. ISBN" << endl;
    cout << "Enter your choice: " << endl;
    cin >> searchType;
    if(cin.fail() || searchType < 1 || searchType > 3) {
     cin.clear();   
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "Error: invalid choice." << endl;
        return;
}
cin.ignore(1000, '\n'); 
    cout << "Enter search term: " << endl;
    string query;
    getline(cin, query);
    if(query.empty()) {
        cout << "Error: search term cannot be empty." << endl;
        return;
    }
  vector<Book> matches;
for (const auto& book : books) {
    if (searchType == 1 && book.title.find(query) != string::npos) {
        matches.push_back(book);
    } else if (searchType == 2 && book.author.find(query) != string::npos) {
        matches.push_back(book);
    } else if (searchType == 3 && book.isbn == query) {
        matches.push_back(book);
    }
}
    if (matches.empty()) {
    cout << "No book found." << endl;
} else {
    cout << "Found " << matches.size() << " book(s):" << endl;
    for (const auto& m : matches) {
        printBook(m);
    }
}
}
void borrowBook(const std::string& currentUser, std::vector<Book>& books) {
    cout << "Enter ISBN to borrow: " << endl;
    string isbn;
    getline(cin, isbn);
if(isbn.empty()) {
        cout << "Error: ISBN cannot be empty." << endl;
        return;
}
auto result = findByIsbn(books, isbn);
if (!result.first) {
    cout << "Error: no book found with that ISBN." << endl;
    return;
}
Book& book = books[result.second];    
 if (book.isReferenceOnly) {
 cout << "Error: this book is reference-only and cannot be borrowed." << endl;
        return;
}
    if(!book.isBorrowed) {
 book.isBorrowed = true;
  book.borrowedBy = currentUser;
cout << "Done: you have borrowed " << book.title << "." <<endl;
return;
    }
    else 
    { if(book.borrowedBy == currentUser) {
          cout << "Error: you have already borrowed this book." << endl;
            return;
}
        queue<string> tempQueue = book.waitingList;
        while (!tempQueue.empty()) {
        if(tempQueue.front() == currentUser) {
            cout << "Error: you are already on the waiting list for this book." << endl;
                return;
        }
tempQueue.pop();
    }
book.waitingList.push(currentUser);
        cout << "This book is currently borrowed. You have been added to the waiting list (position " << book.waitingList.size() << ")." << endl;
}
}
void returnBook(const std::string& currentUser, std::vector<Book>& books) {
cout << "Enter ISBN to return: " << endl;
string isbn;
getline(cin, isbn);
if(isbn.empty()) {
cout << "Error: ISBN cannot be empty." << endl;
return;
}
auto result = findByIsbn(books, isbn);
if(!result.first) {
    cout << "Error: no book found with that ISBN." << endl;
    return;
}
Book& book = books[result.second]; 
if (!book.isBorrowed || book.borrowedBy != currentUser) {
cout << "Error: you have not borrowed this book." << endl;
return;
}
cout << "Done: " << book.title << " has been returned." << endl;
if (!book.waitingList.empty()) {
    string nextUser = book.waitingList.front();
book.waitingList.pop(); 
book.borrowedBy = nextUser;
cout << "Notice: " << book.title << " has been automatically assigned to " << nextUser << "from the waiting list." << endl;
}
else {
    book.isBorrowed = false; 
    book.borrowedBy = "";
}
}
void runMemberMenu(const std::string& currentUser, std::vector<Book>& books) {
int choice;
while(true) {
    cout << "1. Search for a book: " << endl;
    cout << "2. Borrow a book" << endl;
cout << "3. Return a book" << endl;
cout << "4. My borrowed books" << endl;
cout <<"5. logout" << endl;
cout << "Enter your choice: " << endl;
cin >> choice;
if(cin.fail()) {
    cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
cout << "Error: invalid choice." << endl; 
continue; 
}
cin.ignore(1000, '\n');
switch (choice) {
case 1:
searchBooks(books);
break;
case 2:
borrowBook(currentUser, books);
break;
case 3:
returnBook(currentUser, books);
break;
case 4: {
    bool foundAny = false;
    for (const auto& book : books) {
        if (book.isBorrowed && book.borrowedBy == currentUser) {
            printBook(book);
            foundAny = true;
        }
    }
    if (!foundAny) {
        cout << "You have not borrowed any books." << endl;
    }
    break;
}
case 5:
    return;
default:
    cout << "Error: invalid choice." << endl;
}
}
}