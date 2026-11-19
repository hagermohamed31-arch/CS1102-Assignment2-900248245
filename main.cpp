#include "LibraryData.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
int main() {
cout << "Library System is starting " << endl;
vector<Book> books;
    map<string, User> users;
    set<string> categories;
    loadSampleData(books, users, categories);
printBook(books[0]); 
return 0;
}