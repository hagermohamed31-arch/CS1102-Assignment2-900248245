#include "LibraryData.h"
#include <iostream>
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
        cout << "Borrowed by " << b.borrowedBy;
    } else {
        cout << "Available" << endl;
    }
}