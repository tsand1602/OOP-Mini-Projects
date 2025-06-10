#include <cmath>
#include <cstdio>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Book {
    string isbn;
    int copiesAvailable;
    int totalCopies;
public:
    string title;
    string author;
    Book (): title("UnknownTitle"), author("UnknownAuthor"), isbn("ISBN"), copiesAvailable(0),totalCopies(5) {}
    Book (string title, string author, string isbn, int copiesAvailable, int totalCopies): title(title), author(author), isbn(isbn), copiesAvailable(copiesAvailable), totalCopies(totalCopies) {}
    Book (const Book &B,string isbn): title(B.title), author(B.author), isbn(isbn), copiesAvailable(B.copiesAvailable), totalCopies(B.totalCopies) {}
    string getisbn() {
        return isbn;
    }
    int getcopiesAvailable () {
        return copiesAvailable;
    }
    int gettotalCopies() {
        return totalCopies;
    }
    void updateCopies(int count) {
        if (totalCopies+count<0 || copiesAvailable+count<0)
            cout << "Invalid request! Count becomes negative" << endl;
        else {
            totalCopies+=count;
            copiesAvailable+=count;
        }
    }
    bool borrowBook() {
        if (copiesAvailable)
            return true;
        cout << "Invalid request! Copy of book not available" << endl;
        return false;
    }
    void borrowBook(string memberID) {
        copiesAvailable--;
    }
    bool returnBook() {
        if (copiesAvailable<totalCopies)
            return true;
        cout << "Invalid request! Copy of book exceeds total copies" << endl;
        return false;
    }
    void returnBook(string memberID) {
        copiesAvailable++;
    }
    void printDetails() {
        cout << title << " " << author << endl;
    }
    void printLibDetails(){
        cout << title << " " << author << " " << copiesAvailable << endl;
    }
};  

class Member {
    string memberID;
    map <string,int> borrowedBooks;
    int borrowLimit;
    int no_of_borrowedBooks;
public:
    string name;
    Member() : memberID("UnknownID"), name("UnknownName"), borrowLimit(3), no_of_borrowedBooks(0) {}
    Member (string memberID, string name, int borrowLimit=3): memberID(memberID), name(name), borrowLimit(borrowLimit), no_of_borrowedBooks(0) {}
    bool borrowBook(string isbn) {
        if (no_of_borrowedBooks<borrowLimit) {
            borrowedBooks[isbn]++;
            no_of_borrowedBooks++;
            return true;
        } else {
            cout << "Invalid request! Borrow limit exceeded" << endl;
            return false;
        }
    }
    string getmemberID (){
        return memberID;
    }
    bool returnBook(string isbn) {
        if (borrowedBooks.find(isbn)!=borrowedBooks.end()) {
            if (borrowedBooks[isbn]>1)
                borrowedBooks[isbn]--;
            else
                borrowedBooks.erase(isbn);
            no_of_borrowedBooks--;
            return true;
        } else {
            cout << "Invalid request! Book not borrowed" << endl;
            return false;
        }
    }
    void printDetails() {
        for (auto x:borrowedBooks) {
            cout << memberID << " " << name << " " << x.first << " " << x.second << endl;
        }
    }
    void printLibDetails(){
        cout << memberID << " " << name << endl;
    }
};

class Library {
    vector<string> books;
    map <string,Book> isbnBooks;
    map <string,Member> IDMembers;
    vector<string> members;
public:
    bool addBook (Book &B) {
        if (isbnBooks.find(B.getisbn())!=isbnBooks.end()) {
            cout << "Invalid request! Book with same isbn already exists" << endl;
            return false;
        } else {
            books.push_back(B.getisbn());
            isbnBooks.insert({B.getisbn(),B});
            return true;
        }
    }
    bool registerMember(Member &M) {
        if (IDMembers.find(M.getmemberID())!=IDMembers.end()) {
            cout << "Invalid request! Member with same id already exists" << endl;
            return false;
        } else {
            members.push_back(M.getmemberID());
            IDMembers.insert({M.getmemberID(),M});
            return true;
        }
    }
    bool returnBook(string memberID, string isbn) {
        if (isbnBooks[isbn].returnBook()) {
            if (IDMembers[memberID].returnBook(isbn)) {
                isbnBooks[isbn].returnBook(memberID);
                return true;
            }
        }
        return false;
    }
    bool borrowBook (string memberID, string isbn) {
        if (isbnBooks[isbn].borrowBook()) {
            if (IDMembers[memberID].borrowBook(isbn)) {
                isbnBooks[isbn].borrowBook(memberID);
                return true;
            }
        }
        return false;
    }
    void printLibraryDetails() {
        for (auto x:books)
            isbnBooks[x].printLibDetails();
        for (auto y:members)
            IDMembers[y].printLibDetails();
    }
    Member& findmember (string memberID) {
        return IDMembers[memberID];
    }
    Book& findbook (string isbn) {
        return isbnBooks[isbn];
    }
};
int main() {
    string command;
    cin >> command;
    Library LibIITM;
    while (command!="Done") {
        if (command=="Book") {
            string s;
            cin >> s;
            if (s=="None") {
                Book newBook;
                LibIITM.addBook(newBook);
            } else if (s=="ExistingBook") {
                string oldisbn, newisbn;
                cin >> oldisbn >> newisbn;
                Book newBook(LibIITM.findbook(oldisbn),newisbn);
                LibIITM.addBook(newBook);
            } else {
                string Author,ISBN; int CopiesAvailable,TotalCopies;
                cin >> Author >> ISBN >> CopiesAvailable >> TotalCopies;
                Book newBook(s,Author,ISBN,CopiesAvailable,TotalCopies);
                LibIITM.addBook(newBook);
            }
        } else if (command=="UpdateCopiesCount") {
            int NewCount; string isbn;
            cin >> isbn >> NewCount;
            LibIITM.findbook(isbn).updateCopies(NewCount);
        } else if (command=="Member") {
            string s,name;
            cin >> s;
            if (s=="NoBorrowLimit") {
                string id;
                cin >> id >> name;
                Member newjoinee(id,name);
                LibIITM.registerMember(newjoinee);
            } else {
                int limit; 
                cin >> name >> limit;
                Member newjoinee(s,name,limit);
                LibIITM.registerMember(newjoinee);
            }
        } else if (command=="Borrow") {
            string MemberID, isbn;
            cin >> MemberID >> isbn;
            LibIITM.borrowBook(MemberID,isbn);
        } else if (command=="Return") {
            string MemberID, isbn;
            cin >> MemberID >> isbn;
            LibIITM.returnBook(MemberID,isbn);
        } else if (command=="PrintBook") {
            string isbn;
            cin >> isbn;
            LibIITM.findbook(isbn).printDetails();
        } else if (command=="PrintMember") {
            string memberID;
            cin >> memberID;
            LibIITM.findmember(memberID).printDetails();
        } else if (command=="PrintLibrary"){
            LibIITM.printLibraryDetails();
        }
        cin >> command;
    }
    return 0;
}
