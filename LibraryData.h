#pragma once
#include <string>
#include <vector>
#include <map>
#include <queue>
#include<set>
using namespace std;
struct User {
    string username;
    string password;
    bool isLibrarian;
           User(string u, string p, bool l) : username(u), password(p), isLibrarian(l) { }
};  
struct Book {
    string isbn;
    string title;
    string author;
    string category;
    string borrowedBy;
    int year;
    bool isReferenceOnly;
    bool isBorrowed;
    queue<string> waitingList;
    Book(string i, string t, string a, string c, int y, bool r, bool b)
        : isbn(i), title(t), author(a), category(c), year(y), isReferenceOnly(r), isBorrowed(b) {}
};
void loadSampleData(vector<Book>& books, map<string, User>& users, set<string>& categories); 
void printBook(const Book& b);
void runLibrarianMenu(map<string, User>& users, vector<Book>& books, set<string>& categories);
void runWelcomeMenu(map<string, User>& users, vector<Book>& books, set<string>& categories);    