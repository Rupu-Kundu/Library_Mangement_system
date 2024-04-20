#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Book {
    public:
        string book_id;
        string book_name;
        string author_name;
        string book_status;
};
class User {
    public:
        string user_id;
        string user_name;
         string password;
        int num_books_borrowed;
};
class Transaction {
    public:
        string transaction_id;
        string book_id;
        string user_id;
        string date_of_issue;
        string date_of_return;
};

class Librarian {
    public:
        string librarian_id;
        string librarian_name;
         string password;
        int work_hours;
};
vector<Book> books;
vector<User> users;
vector<Transaction> transactions;
vector<Librarian> librarians;
void add_book() {
    Book book;
    cout << "Enter number of books to add: ";
    int num_books;
    cin >> num_books;
    for (int i = 0; i < num_books; ++i) {
        cout << "Book " << i + 1 << ":" << endl;
        cout << "Enter book ID: ";
        cin >> book.book_id;
        cout << "Enter book name: ";
        cin >> book.book_name;
        cout << "Enter author name: ";
        cin >> book.author_name;

        books.push_back(book);
    }
}
void remove_book() {
    string book_id;
    cout << "Enter book ID: ";
    cin >> book_id;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].book_id == book_id) {
            books.erase(books.begin() + i);
            cout << "Book removed successfully!" << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}
void display_books() {
    for (int i = 0; i < books.size(); i++) {
        cout << "Book ID: " << books[i].book_id << endl;
        cout << "Book Name: " << books[i].book_name << endl;
        cout << "Author Name: " << books[i].author_name << endl;
        if (books[i].book_status == "Borrowed") {
            cout << "Book Status: Borrowed" << endl;
        } else {
            cout << "Book Status: Available" << endl;
        }
        cout << endl;
    }
}
void search_book() {
    string search_query;
    cout << "Enter book ID or name to search: ";
    cin.ignore();
    getline(cin, search_query);
    bool found = false;
    for (const Book& book : books) {
        if (book.book_id == search_query || book.book_name == search_query) {
            cout << "Book ID: " << book.book_id << endl;
            cout << "Book Name: " << book.book_name << endl;
            cout << "Author Name: " << book.author_name << endl;
            if (book.book_status == "Borrowed") {
                cout << "Book Status: Borrowed" << endl;
            } else {
                cout << "Book Status: Available" << endl;
            }
            cout << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Book not found!" << endl;
    }
}

void display_users() {
    for (const User& user : users) {
        cout << "User ID: " << user.user_id << endl;
        cout << "User Name: " << user.user_name << endl;

        cout << "Books Borrowed: ";
        bool borrowedBooks = false;
        for (const Transaction& transaction : transactions) {
            if (transaction.user_id == user.user_id) {
                for (const Book& book : books) {
                    if (book.book_id == transaction.book_id) {
                        cout << book.book_id << endl;
                        borrowedBooks = true;
                        break;
                    }
                }
            }
        }
        if (!borrowedBooks) {
            cout << "None";
        }
        cout << endl << endl;
    }
}
void search_user() {
    string search_query;
    cout << "Enter user ID or name to search: ";
    cin >> search_query;
    bool found = false;
    for (const User& user : users) {
        if (user.user_id == search_query || user.user_name == search_query) {
            cout << "User ID: " << user.user_id << endl;
            cout << "User Name: " << user.user_name << endl;

            cout << "Borrowed Books: ";
            bool borrowed_books = false;
            for (const Transaction& transaction : transactions) {
                if (transaction.user_id == user.user_id) {
                    for (const Book& book : books) {
                        if (book.book_id == transaction.book_id) {
                            cout << book.book_id << " - " << book.book_name << endl;
                            borrowed_books = true;
                        }
                    }
                }
            }
            if (!borrowed_books) {
                cout << "None";
            }
            cout << endl;

            cout << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "User not found!" << endl;
    }
}

void update_user() {
    string user_id;
    cout << "Enter user ID: ";
    cin >> user_id;
    for (int i = 0; i < users.size(); i++) {
        if (users[i].user_id == user_id) {
            cout << "Enter new user name: ";
            cin >> users[i].user_name;
            cout << "User updated successfully!" << endl;
            return;
        }
    }
    cout << "User not found!" << endl;
}
void borrow_book() {
    string book_id, user_id, date_of_issue;
    cout << "Enter book ID: ";
    cin >> book_id;
    cout << "Enter user ID: ";
    cin >> user_id;
    cout << "Enter date of issue: ";
    cin >> date_of_issue;
    Transaction transaction;
    transaction.transaction_id = to_string(transactions.size() + 1);
    transaction.book_id = book_id;
    transaction.user_id = user_id;
    transaction.date_of_issue = date_of_issue;
    transactions.push_back(transaction);
    for (int i = 0; i < books.size(); i++) {
        if (books[i].book_id == book_id) {
            if (books[i].book_status != "Borrowed") {
                books[i].book_status = "Borrowed";
                cout << "Book borrowed successfully!" << endl;
            } else {
                cout << "Book is already borrowed!" << endl;
            }
            return;
        }
    }
    cout << "Book not found!" << endl;
}
void return_book() {
    string book_id, user_id, date_of_return;
    cout << "Enter book ID: ";
    cin >> book_id;
    cout << "Enter user ID: ";
    cin >> user_id;
    for (int i = 0; i < transactions.size(); i++) {
        if (transactions[i].book_id == book_id && transactions[i].user_id == user_id) {
            if (transactions[i].date_of_return.empty()) {
                cout << "Enter date of return: ";
                cin >> transactions[i].date_of_return;
                for (int j = 0; j < books.size(); j++) {
                    if (books[j].book_id == book_id) {
                        books[j].book_status = "Available";
                        cout << "Book returned successfully!" << endl;
                        return;
                    }
                }
            } else {
                cout << "Book is already returned!" << endl;
            }
        }
    }
    cout << "Transaction not found!" << endl;
}
void display_transactions() {
    for (int i = 0; i < transactions.size(); i++) {
        cout << "Transaction ID: " << transactions[i].transaction_id << endl;
        cout << "Book ID: " << transactions[i].book_id << endl;
        cout << "User ID: " << transactions[i].user_id << endl;
        cout << "Date of Issue: " << transactions[i].date_of_issue << endl;
        cout << "Date of Return: " << transactions[i].date_of_return << endl;
        cout << endl;
    }
}
bool librarianLogin(Librarian& currentLibrarian) {
    string username, password;
    cout << "Enter librarian id: ";
    cin >>username;
    cout << "Enter librarian password: ";
    cin >> password;

    for (const Librarian& l : librarians) {
        if (l.librarian_id == username && l.password == password) {
            return true;
        }
    }
    return false;
}
bool defaultLibrarianLogin() {
    string defaultUsername = "123"; // Default librarian username
    string defaultPassword = "123"; // Default librarian password
    string username, password;

    cout << "Enter librarian id: ";
    cin >> username;
    cout << "Enter librarian password: ";
    cin >> password;

    if (username == defaultUsername && password == defaultPassword) {
        return true;
    } else {
        return false;
    }
}
bool userLogin(User& currentUser) {
    string username, password;
    cout << "Enter user id: ";
    cin >> username;
    cout << "Enter user password: ";
    cin >> password;
    for (User& u : users) {
        if (u.user_id == username && u.password == password) {
            currentUser = u;
            return true;
        }
    }
    return false;
}
void create_user() {
    User user;
    cout << "Enter user ID: ";
    cin >> user.user_id;
    cout << "Enter user name: ";
    cin >> user.user_name;
    cout << "Enter password: ";
    cin >> user.password;
    users.push_back(user);
    cout << "User account created successfully!" << endl;
}
void display_librarians() {
    cout << "Librarian Details:" << endl;
    for (const Librarian& librarian : librarians) {
        cout << "Librarian ID: " << librarian.librarian_id << endl;
        cout << "Librarian Name: " << librarian.librarian_name << endl;
        cout << "Work Hours: " << librarian.work_hours << endl;
        cout << endl;
    }
}
void update_librarian() {
    string librarian_id;
    cout << "Enter librarian ID to update: ";
    cin >> librarian_id;
    for (Librarian& librarian : librarians) {
        if (librarian.librarian_id == librarian_id) {
            cout << "Enter new librarian name: ";
            cin >> librarian.librarian_name;
            cout << "Enter new work hours: ";
            cin >> librarian.work_hours;
            cout << "Librarian updated successfully!" << endl;
            return;
        }
    }
    cout << "Librarian not found!" << endl;
}
void add_librarian() {
    Librarian librarian;
    cout << "Enter librarian ID: ";
    cin >> librarian.librarian_id;
    cout << "Enter librarian name: ";
    cin >> librarian.librarian_name;
    cout << "Enter password: ";
    cin >> librarian.password;
    cout << "Enter work hours: ";
    cin >> librarian.work_hours;
    librarians.push_back(librarian);
    cout << "Librarian added successfully!" << endl;
}
void remove_user() {
    string user_id;
    cout << "Enter user ID to remove: ";
    cin >> user_id;
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->user_id == user_id) {
            it = users.erase(it); // Remove user from the vector
            cout << "User removed successfully!" << endl;
            return;
        }
    }
    cout << "User not found!" << endl;
}

void remove_librarian() {
    string librarian_id;
    cout << "Enter librarian ID to remove: ";
    cin >> librarian_id;
    for (auto it = librarians.begin(); it != librarians.end(); ++it) {
        if (it->librarian_id == librarian_id) {
            it = librarians.erase(it); // Remove librarian from the vector
            cout << "Librarian removed successfully!" << endl;
            return;
        }
    }
    cout << "Librarian not found!" << endl;
}


int main() {
    Librarian librarian;
    int choice;
      Librarian currentLibrarian;
      Librarian defaultLibrarian;
    User currentUser;
    while (true) {
        cout << "Welcome to the library management system!" << endl;
        cout << "1. Librarian Login" << endl;
        cout << "2. User Login" << endl;
 cout<<"3. Default Librarian Login"<<endl;
        cout << "4. Exit" << endl;

       cout << "Enter your choice: ";
        cin >> choice;
switch (choice)  {
            case 1:
                if (librarianLogin(currentLibrarian)) {
                    // Librarian logged in successfully
                    while (true) {
                        // Provide librarian options
                        cout << "Librarian Menu:" << endl;
                        cout << "1. Add Book" << endl;
                        cout << "2. Remove Book" << endl;
                        cout << "3. Display Books" << endl;
                        cout << "4. Search Book" << endl;
                        cout << "6. Display Users" << endl;
                        cout << "7. Search User" << endl;
                        cout << "8. Display Transactions" << endl;
                        cout << "9. Librarian Details" << endl;
                        cout << "10. Update Librarian " << endl;
                        cout << "11. Add Librarian" << endl;
                        cout << "12. Create User Account" << endl;
                        cout << "13. Remove User"<<endl;
                        cout << "14. Update User"<<endl;
                        cout << "15. Remove Librarian"<<endl;
                        cout << "16. Logout" << endl;
                        cout << "17. Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                add_book();
                                break;
                            case 2:
                                remove_book();
                                break;
                            case 3:
                                display_books();
                                break;
                            case 4:
                                search_book();
                                break;

                            case 6:
                                display_users();
                                break;
                            case 7:
                                search_user();
                                break;
                            case 8:
                                display_transactions();
                                break;
                                 case 9:
                display_librarians();
                break;
                                 case 10:
                                    update_librarian();
                break;

                            case 11 :
                                add_librarian();
                                break;

            case 12:
                create_user();
                break;
                          case 13:
                               remove_user() ;
                                break;
                            case 14:
                              update_user()  ;
                                break;
                            case 15:
                               remove_librarian()  ;
                                break;
                                       case 16:
                                cout << "Logged out successfully!" << endl;
                                break;

                            default:
                                cout << "Invalid choice!" << endl;
                                break;
                        }
                        if (choice == 16)
                            break;
                    }
                } else {
                    cout << "Login failed! Please try again." << endl;
                }
                break;
            case 2:
                if (userLogin(currentUser)) {
                    while (true) {
                        cout << "User Menu:" << endl;
                        cout << "1. Borrow Book" << endl;
                        cout << "2. Return Book" << endl;
                        cout << "3. Display Transactions" << endl;
                        cout << "4. Search Book" << endl;
                        cout << "5. Logout" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                borrow_book();
                                break;
                            case 2:
                                return_book();
                                break;
                            case 3:
                                display_transactions();
                                break;
                            case 4:
                                search_book();
                                break;
                            case 5:
                                cout << "Logged out successfully!" << endl;
                                break;
                            default:
                                cout << "Invalid choice!" << endl;
                                break;
                        }

                        if (choice == 5)
                            break;
                    }
                } else {
                    cout << "Login failed! Please try again." << endl;
                }
                break;

            case 4:
                cout << "Thank you for using the library management system!" << endl;
                return 0;
                break;
                case 3:

                 if (defaultLibrarianLogin()) {

                    while (true) {
                        // Provide librarian options
                        cout << "Librarian Menu:" << endl;
                        cout << "1. Add Book" << endl;
                        cout << "2. Remove Book" << endl;
                        cout << "3. Display Books" << endl;
                        cout << "4. Search Book" << endl;
                        cout << "6. Display Users" << endl;
                        cout << "7. Search User" << endl;
                        cout << "8. Display Transactions" << endl;
                        cout << "9. Librarian Details" << endl;
                        cout << "10. Update Librarian " << endl;
                        cout << "11. Add Librarian" << endl;
                        cout << "12. Create User Account" << endl;
                        cout << "13. Remove User"<<endl;
                        cout << "14. Update User"<<endl;
                        cout << "15. Remove Librarian"<<endl;
                        cout << "16. Logout" << endl;
                        cout << "17. Enter your choice: ";
                        cin >> choice;

switch (choice) {
                            case 1:
                                add_book();
                                break;
                            case 2:
                                remove_book();
                                break;
                            case 3:
                                display_books();
                                break;
                            case 4:
                                search_book();
                                break;

                            case 6:
                                display_users();
                                break;
                            case 7:
                                search_user();
                                break;
                            case 8:
                                display_transactions();
                                break;
                                 case 9:
                display_librarians();
                break;
                                 case 10:
                                    update_librarian();
                break;

                            case 11 :
                                add_librarian();
break;
            case 12:
                create_user();
                break;
                                break;
                         case 13:
                               remove_user() ;
                                break;
                            case 14:
                              update_user()  ;
                                break;
                            case 15:
                               remove_librarian()  ;
                                break;
                                       case 16:
                                cout << "Logged out successfully!" << endl;
                                break;

                            default:
                                cout << "Invalid choice!" << endl;
                                break;
                        }
                        if (choice == 16)
                            break;
                    }
                } else {
                    cout << "Login failed! Please try again." << endl;
                }
                break;

                break;



            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}
