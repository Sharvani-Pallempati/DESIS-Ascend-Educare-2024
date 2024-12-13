#include <bits/stdc++.h>
#include <thread>  
#include <chrono>  
using namespace std;


// Helper functions
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    cout << "\033[2J\033[1;1H";
#endif
}

void wait(int seconds = 2) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

// Defining classes
//forward declaration of inventory class to give friend access
class Inventory;

// Book Class
// Attributes : Name, Author, Genre, Publishing Year, Stock, Books sold, Price, Series(Optional)
class Book {
    static long long bookID;
    static long long totalBooks;
    public:
        // Attributes
        long long id;
        string name;
        string author;
        string genre;
        int pubYear;
        int stock;
        int booksSold;
        float price;
        string series;
        bool newCollection;
        float rating;
        string language;

        // Constructor
        Book(string name, string author, string genre, int pubYear, float price, int stock, bool newCollection, string series = "", int booksSold = 0, float rating = 0.0, string language = "English") 
    : name(name), author(author), genre(genre), pubYear(pubYear), price(price), 
      stock(stock), newCollection(newCollection), series(series), booksSold(booksSold), 
      rating(rating), language(language) {
        this->id = bookID++;
        totalBooks++;
      }

      friend class Inventory;

};
long long Book::bookID = 10000;
long long Book::totalBooks = 0;

// Magazine Class
// Attributes: ID, Title, Publisher, Genre, Publishing Year, Stock, Issues Sold, Price, Is New Collection, Is monthly
class Magazine {
    static long long magazineID;
    static long long totalMagazines;
    public:
        // Attributes
        long long id;
        string title;
        string publisher;
        string genre;
        int pubYear;
        int stock;
        int issuesSold;
        float price;
        bool newCollection;
        string language;
        bool isMonthly;

        // Constructor
        Magazine(string title, string publisher, string genre, int pubYear, float price, 
         int stock, bool newCollection = false, string language = "English", 
         int issuesSold = 0, bool isMonthly = true) 
    : title(title), publisher(publisher), genre(genre), pubYear(pubYear), price(price), 
      stock(stock), newCollection(newCollection), language(language), 
      issuesSold(issuesSold), isMonthly(isMonthly) {
        this->id = magazineID++;
        totalMagazines++;
      }

      friend class Inventory;

};
long long Magazine::magazineID = 20000;
long long Magazine::totalMagazines = 0;

//forward declaration of Users class to give friend access
class Users;

// Customer Class
// Attributes: ID, Name, Phn no., BooksBought
class Customer {
    static long long customerID;
    static long long totalCustomers;
    public:
        // Attributes
        long long id;
        string name;
        long long phNo;
        vector<string> booksPurchased;

        // Constructor
        Customer(string name, long long phNo) 
            : name(name), phNo(phNo) {
                this->id = customerID++;
                totalCustomers++;
            }

        void addBookToPurchaseHistory(string book) {
            booksPurchased.push_back(book);
        }

        friend class Users;
};
long long Customer::customerID = 100;
long long Customer::totalCustomers = 0; 

// Cashier Class
// Attributes: ID, Name, Phn no., Salary
class Cashier{
    static long long cashierID;
    static long long totalCashiers;
    public:
        long long id;
        string name;
        long long phNo;
        long long salary;
        Cashier(string name, long long phNo, long long salary) 
            : name(name), phNo(phNo), salary(salary) {
                this->id = cashierID++;
                totalCashiers++;
        }

        friend class Users;
};
long long Cashier::cashierID = 10; 
long long Cashier::totalCashiers = 0;

// Store Manager
// Attributes: ID, Name, Phn no.
class Manager {
    static int managerID;
    public:
        int id;
        string name;
        long long phNo;

        Manager(string name, long long phNo) {
            this->name = name;
            this->phNo = phNo;
            this->id = managerID;
        }
};
int Manager::managerID = 1; 

// Inventory
// Books, Magazines
class Inventory {
private:
    vector<Book> books;
    vector<Magazine> magazines;
    vector<string> bookGenres;
    vector<string> authors;
    vector<string> series;
    vector<string> magazineGenres;

public:
    void addBook(Book book) {
        books.push_back(book);
        
        if (find(bookGenres.begin(), bookGenres.end(), book.genre) == bookGenres.end()) {
            bookGenres.push_back(book.genre);
        }
        
        if (find(authors.begin(), authors.end(), book.author) == authors.end()) {
            authors.push_back(book.author);
        }

        if (find(series.begin(), series.end(), book.series) == series.end()) {
            series.push_back(book.series);
        }

    }

    void addMagazine(Magazine magazine) {
        magazines.push_back(magazine);
        
        if (find(magazineGenres.begin(), magazineGenres.end(), magazine.genre) == magazineGenres.end()) {
            magazineGenres.push_back(magazine.genre);
        }

    }

    void updateStock(string itemTitle, int newStock) {
        for (auto &book : books) {
            if (book.name == itemTitle) {
                book.stock += newStock;
                cout << "Stock updated successfully..." << endl;
                return;
            }
        }
        for (auto &magazine : magazines) {
            if (magazine.title == itemTitle) {
                magazine.stock += newStock;
                cout << "Stock updated successfully..." << endl;
                return;
            }
        }
        cout << "Item not found..." << endl;
        return;
    }

    void updateStock(int itemId, int newStock) {
        if (itemId >= 10000 && itemId < 20000) {
            for (auto &book : books) {
                if (book.id == itemId) {
                    book.stock += newStock;
                    cout << "Stock updated successfully..." << endl;
                    return;
                }
            }
        }else if (itemId >= 20000) {
            for (auto &magazine : magazines) {
                if (magazine.id == itemId) {
                    magazine.stock += newStock;
                    cout << "Stock updated successfully..." << endl;
                    return;
                }
            }
        }
        cout << "Item with ID " << itemId << " not found." << endl;
    }

    void searchBook(const string &bookName) {
        bool found = false;
        for (const auto &book : books) {
            if (book.name == bookName) {
                cout << "      Bookshop Inventory Management System       " << endl;
                cout << "-------------------------------------------------" << endl;
                cout << "                ---Book details---               " << endl;
                if(book.newCollection){
                    cout << "                   NEW COLLECTION                " << endl;
                }
                cout << "             Name: " << book.name << endl;
                cout << "             Author: " << book.author << endl;
                cout << "             Genre: " << book.genre << endl;
                cout << "             Series: " << book.series << endl;
                cout << "             Publishing year: " << book.pubYear << endl;
                cout << "             Language: " << book.language << endl;
                if(book.rating != 0.0){
                    cout << "             Rating: " << book.rating << endl;
                }
                cout << "             Price: " << book.price << endl;
                if(book.stock > 0 ){
                    cout << "                  Book available                 " << endl;
                }else{
                    cout << "      Out of stock. Try contacting the staff...  " << endl;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "      Bookshop Inventory Management System       " << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "Sorry, the book \"" << bookName << "\" is not available" << endl;
        }
    }

    void displayAllBooks(bool isManager = false) {
        clearScreen();
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        for (const auto &book : books) {
            if(book.newCollection){
                cout << "                   NEW COLLECTION                " << endl;
            }
            cout << "             Name: " << book.name << endl;
            cout << "             Author: " << book.author << endl;
            if(book.rating != 0.0){
                cout << "             Rating: " << book.rating << endl;
            }
            cout << "             Price: " << book.price << endl;
            if(isManager){
                cout << "             Stock: " << book.stock << endl;
                cout << "             Issues Sold: " << book.booksSold << endl;
            }
            cout << "-------------------------------------------------" << endl;
        }
    }

    void displayBookByGenre(string genre) {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "          Books of genre " << genre << endl;
        bool found = false;
        for (const auto &book : books) {
            if (book.genre == genre) {
                found = true;
                if(book.newCollection){
                    cout << "                   NEW COLLECTION                " << endl;
                }
                cout << "             Name: " << book.name << endl;
                cout << "             Author: " << book.author << endl;
                if(book.rating != 0.0){
                    cout << "             Rating: " << book.rating << endl;
                }
                cout << "             Price: " << book.price << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }

        if(!found){
            cout << "                Not Found                         " << endl;
        }
    }

    void displayBookByAuthor(string author) {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "            Books by Author " << author << endl;
        bool found = false;
        for (const auto &book : books) {
            if (book.author == author) {
                found = true;
                if(book.newCollection){
                    cout << "                   NEW COLLECTION                " << endl;
                }
                cout << "             Name: " << book.name << endl;
                if(book.rating != 0.0){
                    cout << "             Rating: " << book.rating << endl;
                }
                cout << "             Price: " << book.price << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }

        if(!found){
            cout << "                Not Found                         " << endl;
        }
    }

    void displayBookBySeries(string series) {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "      Books of the series " << series << endl;
        bool found = false;
        for (const auto &book : books) {
            if (book.series == series) {
                found = true;
                if(book.newCollection){
                    cout << "                   NEW COLLECTION                " << endl;
                }
                cout << "             Name: " << book.name << endl;
                cout << "             Author: " << book.author << endl;
                if(book.rating != 0.0){
                    cout << "             Rating: " << book.rating << endl;
                }
                cout << "             Price: " << book.price << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }

        if(!found){
            cout << "                Not Found                         " << endl;
        }
    }

    void displayNewBookCollection() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                   NEW COLLECTION                " << endl;
        for (const auto &book : books) {
            if (book.newCollection) {
                cout << "             Name: " << book.name << endl;
                cout << "             Author: " << book.author << endl;
                cout << "             Genre: " << book.genre << endl;
                if(book.rating != 0.0){
                    cout << "             Rating: " << book.rating << endl;
                }
                cout << "             Price: " << book.price << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }
    }

    void displayAllBookGenres() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---All Book Genres---             " << endl;
        
        for (const auto& genre : bookGenres) {
            cout << "              " << genre << endl;
        }
    }

    void displayAllSeries() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---All Book Series---            " << endl;
        
        for (const auto& seriesName : series) {
            cout << "              " << seriesName << endl;
        }
    }

    void displayAllAuthors() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                 ---All Authors---              " << endl;
        
        for (const auto& author : authors) {
            cout << "              " << author << endl;
        }
    }

    void searchMagazine(const string &title) {
        bool found = false;
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        for (const auto &magazine : magazines) {
            if (magazine.title == title) {
                cout << "              ---Magazine details---          " << endl;
                if(magazine.newCollection){
                    cout << "                   NEW COLLECTION                " << endl;
                }
                if(magazine.isMonthly){
                    cout << "                  MONTHLY MAGAZINE               " << endl;
                }
                cout << "             Title: " << magazine.title << endl;
                cout << "             Publisher: " << magazine.publisher << endl;
                cout << "             Genre: " << magazine.genre << endl;
                cout << "             Year: " << magazine.pubYear << endl;
                cout << "             Price: " << magazine.price << endl;
                if(magazine.stock > 0 ){
                    cout << "               Magazine available                 " << endl;
                }else{
                    cout << "      Out of stock. Try contacting the staff...  " << endl;
                }
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Sorry, the magazine \"" << title << "\" is not available here.\n";
        }
    }

    void displayAllMagazines(bool isManager = false) {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        for (const auto &magazine : magazines) {
            if(magazine.newCollection){
                cout << "                  NEW COLLECTION                 " << endl;
            }
            if(magazine.isMonthly){
                cout << "                 MONTHLY MAGAZINE                " << endl;
            }
            cout << "             Title: " << magazine.title << endl;
            cout << "             Genre: " << magazine.genre << endl;
            cout << "             Price: " << magazine.price << endl;
            if(isManager){
                cout << "             Stock: " << magazine.stock << endl;
                cout << "             Issues sold: " << magazine.issuesSold << endl;
            }
            cout << "-------------------------------------------------" << endl;
        }
    }

    void displayMagazineByGenre(string genre) {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                " << genre << " magazines" << endl;
        bool found = false;
        for (const auto &magazine : magazines) {
            if (magazine.genre == genre) {
                found = true;
                if(magazine.newCollection){
                    cout << "                   NEW COLLECTION                " << endl;
                }
                if(magazine.isMonthly){
                    cout << "                  MONTHLY MAGAZINE               " << endl;
                }
                cout << "             Title: " << magazine.title << endl;
                cout << "             Publisher: " << magazine.publisher << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }
        if(!found){
            cout << "Sorry, the magazines of genre \"" << genre << "\" are not available here." << endl;
        }
    }

    void displayNewMagazineCollection() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                   NEW COLLECTION                " << endl;
        for (const auto &magazine : magazines) {
            if (magazine.newCollection) {
                cout << "             Title: " << magazine.title << endl;
                cout << "             Publisher: " << magazine.publisher << endl;
                cout << "             Genre: " << magazine.genre << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }
    }

    void displayAllMagazineGenres() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "             ---All Magazine Genres---          " << endl;
        
        for (const auto& genre : magazineGenres) {
            cout << "              " << genre << endl;
        }
    }

    int getStock(const string& itemName){
        for (const auto& book : books) {
            if (book.name == itemName) {
                return book.stock;
            }
        }

        for (const auto& magazine : magazines) {
            if (magazine.title == itemName) {
                return magazine.stock;
            }
        }

        return 0;
    }

    float getPrice(const string& itemName) const {
        for (const auto& book : books) {
            if (book.name == itemName) {
                return book.price;
            }
        }

        for (const auto& magazine : magazines) {
            if (magazine.title == itemName) {
                return magazine.price;
            }
        }

        return 0.0;
    }

    void sellItem(const string& itemName) {
        for (auto& book : books) {
            if (book.name == itemName) {
                book.booksSold++;
                book.stock--;
                return; 
            }
        }

        for (auto& magazine : magazines) {
            if (magazine.stock > 0) {
                magazine.issuesSold++;
                magazine.stock--;
                return;
            }
        }
        return;
    }

    void giveRating(const string& bookName) {   

        bool found = false;
        for (auto& book : books) {
            if (book.name == bookName) {
                bool valid = false;
                float rating;
                while(!valid){
                    cout << "Give rating on a scale of 5" << endl;
                    cin >> rating;
                    if (rating < 0.0 || rating > 5.0) {
                        cout << "Invalid rating. Please enter a rating between 0.0 and 5.0." << endl;
                    }else{
                        valid = true;
                    }
                }
                updateRating(book, rating);
                cout << "Thank you for rating \"" << book.name << "\"!" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Book \"" << bookName << "\" not found in the inventory." << endl;
        }

    }

    void updateRating(Book& book, float newRating) {
        static unordered_map<string, int> ratingCount; 

        if (ratingCount.find(book.name) == ratingCount.end()) {
            ratingCount[book.name] = 15;
        }

        book.rating = ((book.rating * ratingCount[book.name]) + newRating) / (ratingCount[book.name] + 1);

        ratingCount[book.name]++;
    }

    long long getTotalBooks(){
        long long a = Book::totalBooks;
        return a;
    }

    long long getTotalMagazines(){
        long long a = Magazine::totalMagazines;
        return a;
    }
};

//Helper functions to get details and then pass to corresponding class
void addBook(Inventory &inventory) {
    cout << "      Bookshop Inventory Management System       " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "             ---Adding a book---                 " << endl;

    cout << "Enter the book name: " << endl;
    string name;
    cin.ignore(); 
    getline(cin, name);

    cout << "Enter the author name: " << endl;
    string author;
    getline(cin, author);

    cout << "Enter the genre: " << endl;
    string genre;
    getline(cin, genre);

    cout << "Does it belong to a series? (y/n): ";
    char check1;
    cin >> check1;
    cin.ignore();
    string series;
    if (check1 == 'y' || check1 == 'Y') {
        cout << "Enter the series: " << endl;
        getline(cin, series);
    } else {
        series = "";
    }

    cout << "Enter Publishing Year: " << endl;
    int pubYear;
    cin >> pubYear;

    cout << "Is it a new collection? (y/n): " << endl;
    char check2;
    cin >> check2;
    bool newCollection = (check2 == 'y' || check2 == 'Y');

    cout << "Does it have an existing rating? (y/n): " << endl;
    char check3;
    cin >> check3;
    float rating = 0.0;
    if (check3 == 'y' || check3 == 'Y') {
        cout << "Enter the rating: " << endl;
        cin >> rating;
    }

    cin.ignore();
    cout << "Enter the language: " << endl;
    string language;
    getline(cin, language);

    cout << "Enter the number of books in stock: " << endl;
    int stock;
    cin >> stock;

    cout << "Enter the price of the book: " << endl;
    float price;
    cin >> price;

    Book newBook(name, author, genre, pubYear, price, stock, newCollection, series, 0, rating, language);

    inventory.addBook(newBook);

    cout << "Book added sucessfully..." << endl;
}

void addMagazine(Inventory &inventory) {
    cout << "      Magazine Inventory Management System       " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "             ---Adding a magazine---             " << endl;

    cout << "Enter the magazine title: " << endl;
    string title; 
    cin.ignore(); 
    getline(cin, title);

    cout << "Enter the publisher name: " << endl;
    string publisher;
    getline(cin, publisher);

    cout << "Enter the genre: " << endl;
    string genre;
    getline(cin, genre);

    cout << "Enter the publishing year: " << endl;
    int pubYear;
    cin >> pubYear;

    cout << "Enter the price: " << endl;
    float price;
    cin >> price;

    cout << "Enter the stock: " << endl;
    int stock;
    cin >> stock;

    cout << "Is it a new collection? (y/n): " << endl;
    char check1;
    cin >> check1;
    bool newCollection = false;
    if(check1 == 'y'){
        newCollection = true;
    }

    cout << "Enter the language: " << endl;
    cin.ignore();
    string language; 
    getline(cin, language);

    cout << "Is it a monthly magazine? (y/n): " << endl;
    char check3;
    cin >> check3;
    bool isMonthly = false;
    if(check3 == 'y'){
        isMonthly = true;
    }

    Magazine newMagazine(title, publisher, genre, pubYear, price, stock, newCollection, language, 0, isMonthly);

    inventory.addMagazine(newMagazine);

    cout << "Magazine added sucessfully..." << endl;
}

// Transaction
// Sell, Receipt generation
class Transaction {
public:
    vector<pair<string, int>> currentTransactionItems;
    double totalAmount = 0.0;

    void addItem(const string& itemName, int quantity, double price) {
        currentTransactionItems.push_back({itemName, quantity});
        totalAmount += (price * quantity);

        cout << "         Item name: " << itemName << endl;
        cout << "         Quantity: " << quantity << endl;
        cout << "         Added item succesfully         " << endl;
        cout << "         Current total: Rs " << totalAmount << endl;
    }

    void generateReceipt() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                ---Receipt---                    " << endl;
        for (const auto& item : currentTransactionItems) {
            cout << item.first << " x" << item.second << endl; 
        }
        cout << "           Total Amount: Rs " << totalAmount << endl;
    }

    void clearTransaction() {
        currentTransactionItems.clear();
        totalAmount = 0.0;
    }
};

//Helper function to get details and then pass to corresponding class
void addItem(Customer* customer, Inventory& inventory, Transaction& transaction) {
    string itemName;
    int quantity;
    cout << "      Bookshop Inventory Management System       " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "            ---Adding Item to Bill---            " << endl;
    cout << "Enter the item name: " << endl;
    cin.ignore();
    getline(cin, itemName);
    cout << "Enter the quantity: " << endl;
    cin >> quantity;

    if(inventory.getStock(itemName) > 0){
        inventory.sellItem(itemName);
        float price = inventory.getPrice(itemName);
        transaction.addItem(itemName, quantity, price);

        for (int i = 0; i < quantity; ++i) {
            customer->addBookToPurchaseHistory(itemName);
        }
    }else{
        cout << "Item out of stock" << endl;
    }
}

// User data
// Customers, Cashiers, Manager
class Users {
    private:
        vector<Customer> customers;
        vector<Cashier> cashiers;

    public:
        void addCustomer(const Customer& customer) {
            customers.push_back(customer);
        }

        void addCashier(const Cashier& cashier) {
            cashiers.push_back(cashier);
        }

        bool removeCashier(int cashierId) {
            for (auto it = cashiers.begin(); it != cashiers.end(); ++it) {
                if (it->id == cashierId) {
                    cashiers.erase(it);
                    return true;
                }
            }
            return false;
        }

        Customer* getCustomerById(int customerId) {
            for (auto& customer : customers) {
                if (customer.id == customerId) {
                    return &customer;
                }
            }
            return nullptr;
        }

        Customer* getCustomerByName(const string& customerName) {
            for (auto& customer : customers) {
                if (customer.name == customerName) {
                    return &customer; 
                }
            }  
            return nullptr;
        }

        Cashier* getCashierById(int cashierId) {
            for (auto& cashier : cashiers) {
                if (cashier.id == cashierId) {
                    return &cashier;
                }
            }
            return nullptr;
        }

        void displayCustomers() {
            cout << "      Bookshop Inventory Management System       " << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "            ---Customers' details---             " << endl;
            for (const auto& customer : customers) {
                cout << "          Customer ID: " << customer.id << endl;
                cout << "          Name: " << customer.name << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }

        void displayCashiers() {
            cout << "      Bookshop Inventory Management System       " << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "            ---Cashiers' details---             " << endl;
            for (const auto& cashier : cashiers) {
                cout << "          Cashier ID: " << cashier.id << endl;
                cout << "          Name: " << cashier.name << endl;
                cout << "          Salary: " << cashier.salary << endl;
                cout << "-------------------------------------------------" << endl;
            }
        }

        void displayCustomerDetails(Customer* customer) {
            cout << "      Bookshop Inventory Management System       " << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "             ---Customer Details---       " << endl;
            cout << "            Customer ID: " << customer->id << endl;
            cout << "            Name: " << customer->name << endl;
            cout << "            Phone Number: " << customer->phNo << endl;
            if((customer->booksPurchased).size() != 0){   
                cout << "      Books Purchased:\n";
                for (const auto& book : customer->booksPurchased) {
                    cout << "- " << book << endl;
                }
            }else{
                cout << "       No books purchased..." << endl;
            }
        }

        void displayPurchases(Customer* customer){
            cout << "      Bookshop Inventory Management System       " << endl;
            cout << "-------------------------------------------------" << endl;
            cout << "               ---Purchase history---       " << endl;
            if((customer->booksPurchased).size() != 0){   
                cout << "             Books Purchased:\n";
                for (const auto& book : customer->booksPurchased) {
                    cout << "       - " << book << endl;
                }
            }else{
                cout << "       No books purchased..." << endl;
            }
        }

        long long getTotalCashiers(){
            long long a = Cashier::totalCashiers;
            return a;
        }

        long long getTotalCustomers(){
            long long a = Customer::totalCustomers;
            return a;
        }

};

//Helper functions to get details and then pass to corresponding class
void addCustomer(Users &users){
    cout << "      Bookshop Inventory Management System       " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter the customer's name: " << endl;
    cin.ignore();
    string customerName;
    getline(cin, customerName);

    cout << "Enter customer's phone number: " << endl;
    long long phNo;
    cin >> phNo;
    Customer newCustomer(customerName, phNo);

    users.addCustomer(newCustomer);

    cout << "Customer registered successfully" << endl;
    cout << "Customer ID " << newCustomer.id << endl;
}

void addCashier(Users &users){
    cout << "      Bookshop Inventory Management System       " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter the cashier's name: " << endl;
    cin.ignore();
    string cashierName;
    getline(cin, cashierName);

    cout << "Enter cashier's phone number: " << endl;
    long long phNo;
    cin >> phNo;

    cout << "Enter cashier's salary: " << endl;
    long long salary;
    cin >> salary;
    Cashier newCashier(cashierName, phNo, salary);

    users.addCashier(newCashier);

    cout << "Cashier registered successfully" << endl;
    cout << "Cashier ID " << newCashier.id << endl;
}

// General UI
// Functions for display
class Menu {
    public:

    void mainMenu(){
        cout << " Welcome to Bookshop Inventory Management System " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                  1. Sign in                     " << endl;
        cout << "      No account? 2. Continue as Guest           " << endl;
        cout << "                  3. Exit the system             " << endl << endl;
    }

    void customerMenu() {
        cout << "      Bookshop Inventory Management System       " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "              ---Customer Menu---                " << endl;
        cout << "                1. My details                    " << endl;
        cout << "                2. My purchase history           " << endl;
        cout << "                3. Browse inventory              " << endl;
        cout << "                4. Rate a book                   " << endl;
        cout << "                5. Logout                        " << endl << endl;
    }

    void browseMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                   ---Browse---                  " << endl;
        cout << "                  1. Books                       " << endl;
        cout << "                  2. Magazines                   " << endl;
        cout << "                  3. Go back to menu             " << endl;
        cout << "                  4. Logout                      " << endl;
    }
    
    void bookMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                ---Books Menu---                 " << endl;
        cout << "               1. Search book                    " << endl;
        cout << "               2. Search book by series          " << endl;
        cout << "               3. Search book by author          " << endl;
        cout << "               4. Search book by genre           " << endl;
        cout << "               5. Display all books              " << endl;
        cout << "               6. Display all series             " << endl;
        cout << "               7. Display all authors            " << endl;
        cout << "               8. Display all genres             " << endl;
        cout << "               9. Display New collection         " << endl;
        cout << "               10. Go back                        " << endl;
        cout << "               11. Logout                        " << endl;
    }

    void magazineMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "              ---Magazines Menu---               " << endl;
        cout << "              1. Search magazine                 " << endl;
        cout << "              2. Search magazine by genre        " << endl;
        cout << "              3. Display all magazines           " << endl;
        cout << "              4. Display all genres              " << endl;
        cout << "              5. Display New collection          " << endl;
        cout << "              6. Go back                         " << endl;
        cout << "              7. Logout                          " << endl;
    }

    void cashierMenu() {
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---Cashier Menu---                " << endl;
        cout << "              1. Manage Inventory                " << endl;
        cout << "              2. Manage Customers                " << endl;
        cout << "              3. Logout                          " << endl;
    }

    void inventoryMenu() {
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---Inventory Menu---             " << endl;
        cout << "               1. Add new stock                  " << endl;
        cout << "               2. Update stock                   " << endl;
        cout << "               3. Check stock                    " << endl;
        cout << "               4. Go back to cashier menu        " << endl;
        cout << "               5. Logout                         " << endl;

    }

    void newStockMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---Add New Stock---               " << endl;
        cout << "                  1. Book                        " << endl;
        cout << "                  2. Magazine                    " << endl;
        cout << "                  3. Go back to inventory menu   " << endl;
    }

    void manageCustomerMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---Manage customers---            " << endl;
        cout << "              1. Register customer               " << endl;
        cout << "              2. View all customers              " << endl;
        cout << "              3. Initiate a purchase             " << endl;
        cout << "              4. Go back to cashier menu         " << endl;
    }

    void purchaseMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---Purchase Menu---               " << endl;
        cout << "                  1. Add item                    " << endl;
        cout << "                  2. Generate receipt            " << endl;
    }

    void managerMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "               ---Manager Menu---                " << endl;
        cout << "              1. Register cashiers               " << endl;
        cout << "              2. View all cashiers              " << endl;
        cout << "              3. View all books                  " << endl;
        cout << "              4. View all magazines              " << endl;
        cout << "              5. Logout         " << endl;
    }

    void guestMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                ---Guest Menu---                 " << endl;
        cout << "              1. Browse inventory                " << endl;
        cout << "              2. About Store                     " << endl;
        cout << "              3. Exit guest menu                 " << endl;
    }

    void guestBrowseMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                   ---Browse---                  " << endl;
        cout << "                  1. Books                       " << endl;
        cout << "                  2. Magazines                   " << endl;
        cout << "                  3. Go back to guest menu       " << endl;
    }

    void guestBookMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "                ---Books Menu---                 " << endl;
        cout << "               1. Search book                    " << endl;
        cout << "               2. Search book by series          " << endl;
        cout << "               3. Search book by author          " << endl;
        cout << "               4. Search book by genre           " << endl;
        cout << "               5. Display all books              " << endl;
        cout << "               6. Display all series             " << endl;
        cout << "               7. Display all authors            " << endl;
        cout << "               8. Display all genres             " << endl;
        cout << "               9. Display New collection         " << endl;
        cout << "               10. Go back                       " << endl;
    }

    void guestMagazineMenu(){
        cout << "       Bookshop Inventory Management System      " << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "              ---Magazines Menu---               " << endl;
        cout << "              1. Search magazine                 " << endl;
        cout << "              2. Search magazine by genre        " << endl;
        cout << "              3. Display all magazines           " << endl;
        cout << "              4. Display all genres              " << endl;
        cout << "              5. Display New collection          " << endl;
        cout << "              6. Go back                         " << endl;
    }
};

void aboutStore(Users &users, Inventory &inventory, Manager &manager){
    cout << " Welcome to Bookshop Inventory Management System " << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "                    Store Details                " << endl;
    cout << "             Store name: " << "Shelf of Tales" << endl;
    cout << "             Manager name: " <<  manager.name << endl;
    cout << "             Manager contact: " << manager.phNo << endl;
    cout << "             Total Cashiers: " << users.getTotalCashiers() << endl;
    cout << "             Total Books: " << inventory.getTotalBooks() << endl;
    cout << "             Total Magazines: " << inventory.getTotalMagazines() << endl;
    cout << "             Total Customers: " << users.getTotalCustomers() << endl;
}

// Loading data from file
class LoadData{
    public:
        void loadBooks(const string& filePath, Inventory &inventory) {
            ifstream file(filePath);
            if (!file) {
                cerr << "Error opening file: " << filePath << endl;
                return;
            }
            
            string line;
            while (getline(file, line)) {
                vector<string> tokens;
                string token;
                stringstream ss(line);

                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }

                if (tokens.size() < 11) {
                    cerr << "Malformed line: " << line << endl;
                    continue;
                }

                try {
                    string name = tokens[0];
                    string author = tokens[1];
                    string genre = tokens[2];
                    int pubYear = stoi(tokens[3]);
                    float price = stof(tokens[4]);
                    int stock = stoi(tokens[5]);
                    bool newCollection = (tokens[6] == "true");
                    string series = tokens[7];
                    int booksSold = stoi(tokens[8]);
                    float rating = stof(tokens[9]);
                    string language = tokens[10];

                    Book newBook(name, author, genre, pubYear, price, stock, newCollection, series, booksSold, rating, language);
                    inventory.addBook(newBook);
                } catch (const exception &e) {
                    cerr << "Error parsing line: " << line << " - " << e.what() << endl;
                }
            }
        }


        void loadMagazines(const string& filePath, Inventory &inventory) {
            ifstream file(filePath);
            if (!file) {
                cerr << "Error opening file: " << filePath << endl;
                return;
            }
            
            string line;
            while (getline(file, line)) {
                vector<string> tokens;
                string token;
                stringstream ss(line);
                
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }
                
                if (tokens.size() < 8) {
                    cerr << "Malformed line: " << line << endl;
                    continue;
                }
                
                try {
                    string title = tokens[0];
                    string publisher = tokens[1];
                    string genre = tokens[2];
                    int pubYear = stoi(tokens[3]);
                    float price = stof(tokens[4]);
                    int stock = stoi(tokens[5]);
                    bool newCollection = (tokens[6] == "true");
                    string language = tokens[7];
                    int issuesSold = stoi(tokens[8]);
                    
                    Magazine newMagazine(title, publisher, genre, pubYear, price, stock, newCollection, language, issuesSold);
                    inventory.addMagazine(newMagazine);
                } catch (const exception &e) {
                    cerr << "Error parsing line: " << line << " - " << e.what() << endl;
                }
            }
        }

        void loadCustomers(const string& filePath, Users &users) {
            ifstream file(filePath);
            if (!file) {
                cerr << "Error opening file: " << filePath << endl;
                return;
            }
            
            string line;
            while (getline(file, line)) {
                vector<string> tokens;
                string token;
                stringstream ss(line);
                
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }
                
                if (tokens.size() < 2) {
                    cerr << "Malformed line: " << line << endl;
                    continue;
                }
                
                try {
                    string name = tokens[0];
                    long long phNo = stoll(tokens[1]);
                    
                    Customer newCustomer(name, phNo);
                    users.addCustomer(newCustomer);
                } catch (const exception &e) {
                    cerr << "Error parsing line: " << line << " - " << e.what() << endl;
                }
            }
        }

        void loadCashiers(const string& filePath, Users &users) {
            ifstream file(filePath);
            if (!file) {
                cerr << "Error opening file: " << filePath << endl;
                return;
            }
            
            string line;
            while (getline(file, line)) {
                vector<string> tokens;
                string token;
                stringstream ss(line);
                
                while (getline(ss, token, ',')) {
                    tokens.push_back(token);
                }
                
                if (tokens.size() < 3) {
                    cerr << "Malformed line: " << line << endl;
                    continue;
                }
                
                try {
                    string name = tokens[0];
                    long long phNo = stoll(tokens[1]);
                    float salary = stof(tokens[2]);
                    
                    Cashier newCashier(name, phNo, salary);
                    users.addCashier(newCashier);
                } catch (const exception &e) {
                    cerr << "Error parsing line: " << line << " - " << e.what() << endl;
                }
            }
        }

};


//Main function
int main(){
    Inventory inventory;
    Users users;
    Menu m;
    LoadData d;

    Manager manager("Shashank Sharma", 1234567890);

    d.loadBooks("book.txt", inventory);
    d.loadMagazines("magazines.txt", inventory);
    d.loadCustomers("customers.txt", users);
    d.loadCashiers("cashiers.txt", users);

    bool mm = true;
    do
    {
        m.mainMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: { 
                // sign in
                cout << "Enter your id: ";
                int curId;
                cin >> curId;
            
                if( curId >= 100 && curId < 10000 ){
                        cout << "Logging in as customer..." << endl;
                        wait();
                        clearScreen();
                        //customer menu
                        bool cm = true;
                        Customer *curCustomer = users.getCustomerById(curId);
                        if(curCustomer == nullptr){
                          cout << "Invalid customer ID. Please try again..." << endl;
                          wait();
                          break;  
                        } 
                        do{
                            m.customerMenu();

                            int customerChoice;
                            cin >> customerChoice;

                            switch(customerChoice){
                                case 1: {
                                    // details
                                    clearScreen();
                                    users.displayCustomerDetails(curCustomer);
                                    cout << endl << "Press any key to continue...";
                                    cin.ignore();
                                    cin.get();
                                    clearScreen();
                                    break;
                                }

                                case 2: {
                                    // purchase history
                                    clearScreen();
                                    users.displayPurchases(curCustomer);
                                    cout << endl << "Press any key to continue...";
                                    cin.ignore();
                                    cin.get();
                                    clearScreen();
                                    break;
                                }

                                case 3: {
                                    // browse
                                    clearScreen();
                                    bool bm = true;

                                    do{
                                        m.browseMenu();
                                        int browseChoice;
                                        cin >> browseChoice;

                                        switch(browseChoice){
                                            case 1: {
                                                //books menu
                                                clearScreen();
                                                bool bkm = true;

                                                do{
                                                    m.bookMenu();
                                                    int bookChoice;
                                                    cin >> bookChoice;

                                                    switch(bookChoice) {
                                                        case 1: {
                                                            clearScreen();
                                                            // search book
                                                            cout << "      Bookshop Inventory Management System       " << endl;
                                                            cout << "-------------------------------------------------" << endl;
                                                            cout << "                Search book                      " << endl;
                                                            cout << "Please enter the name of the book: " << endl;

                                                            string bookName;
                                                            cin.ignore();
                                                            cin >> ws;
                                                            getline(cin, bookName); 
                                                            cout << "Searching the inventory..." << endl;
                                                            wait();
                                                            clearScreen();

                                                            inventory.searchBook(bookName);

                                                            cout << endl << "Press any key to continue..." << endl;;
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 2: {
                                                            // search book by series
                                                            clearScreen();
                                                            cout << "      Bookshop Inventory Management System       " << endl;
                                                            cout << "-------------------------------------------------" << endl;
                                                            cout << "                Search book                      " << endl;
                                                            cout << "Please enter the name of the series: " << endl;

                                                            string seriesName;
                                                            cin.ignore();
                                                            cin >> ws;
                                                            getline(cin, seriesName); 
                                                            cout << "Searching the inventory..." << endl;
                                                            wait();
                                                            clearScreen();

                                                            inventory.displayBookBySeries(seriesName);

                                                            cout << endl << "Press any key to continue..." << endl;
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 3: {
                                                            // search book by author
                                                            clearScreen();
                                                            cout << "      Bookshop Inventory Management System       " << endl;
                                                            cout << "-------------------------------------------------" << endl;
                                                            cout << "                Search book                      " << endl;
                                                            cout << "Please enter the name of the author: " << endl;

                                                            string authorName;
                                                            cin.ignore();
                                                            cin >> ws;
                                                            getline(cin, authorName); 
                                                            cout << "Searching the inventory..." << endl;
                                                            wait();
                                                            clearScreen();

                                                            inventory.displayBookByAuthor(authorName);

                                                            cout << endl << "Press any key to continue..." << endl;
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 4: {
                                                            // search book by genre
                                                            clearScreen();
                                                            cout << "      Bookshop Inventory Management System       " << endl;
                                                            cout << "-------------------------------------------------" << endl;
                                                            cout << "                Search book                      " << endl;
                                                            cout << "Please enter the genre: " << endl;

                                                            string genreName;
                                                            cin.ignore();
                                                            cin >> ws;
                                                            getline(cin, genreName); 
                                                            cout << "Searching the inventory..." << endl;
                                                            wait();
                                                            clearScreen();

                                                            inventory.displayBookByGenre(genreName);

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 5: {
                                                            // display all books
                                                            clearScreen();
                                                            inventory.displayAllBooks();

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 6: {
                                                            // display all series
                                                            clearScreen();
                                                            inventory.displayAllSeries();

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 7: {
                                                            // display all authors
                                                            clearScreen();
                                                            inventory.displayAllAuthors();

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 8: {
                                                            // display all genres
                                                            clearScreen();
                                                            inventory.displayAllBookGenres();

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 9: {
                                                            // new collection
                                                            clearScreen();
                                                            inventory.displayNewBookCollection();

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 10: {
                                                            bkm = false;
                                                            cout << "Going back..." << endl;
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 11: {
                                                            bkm = false;
                                                            bm = false;
                                                            cm = false;
                                                            cout << "Logging out..." << endl;
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        default: {
                                                            cout << "Invalid choice. Please try again...";
                                                            wait();
                                                            clearScreen();
                                                        }
                                                    }
                                                } while(bkm);
                                                break;
                                            }

                                            case 2: {
                                                // magazines menu
                                                clearScreen();
                                                bool mgm = true;

                                                do{
                                                    m.magazineMenu();
                                                    int magazineChoice;
                                                    cin >> magazineChoice;

                                                    switch(magazineChoice){
                                                        case 1: {
                                                            //search magazine
                                                            clearScreen();
                                                            cout << "      Bookshop Inventory Management System       " << endl;
                                                            cout << "-------------------------------------------------" << endl;
                                                            cout << "                Search magazine                      " << endl;
                                                            cout << "Please enter the title of the magazine: " << endl;

                                                            string magazineName;
                                                            cin.ignore();
                                                            cin >> ws;
                                                            getline(cin, magazineName); 
                                                            cout << "Searching the inventory..." << endl;
                                                            wait();
                                                            clearScreen();

                                                            inventory.searchMagazine(magazineName);

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 2: {
                                                            // search magazine by genre
                                                            clearScreen();
                                                            cout << "      Bookshop Inventory Management System       " << endl;
                                                            cout << "-------------------------------------------------" << endl;
                                                            cout << "                Search magazine                      " << endl;
                                                            cout << "Please enter the genre: " << endl;

                                                            string genreName;
                                                            cin.ignore();
                                                            cin >> ws;
                                                            getline(cin, genreName); 
                                                            cout << "Searching the inventory..." << endl;
                                                            wait();
                                                            clearScreen();

                                                            inventory.displayMagazineByGenre(genreName);

                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 3: {
                                                            // display all magazines
                                                            clearScreen();
                                                            inventory.displayAllMagazines();

                                                            cout << endl << "Press any key to continue..." ;
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 4: {
                                                            // display all genres
                                                            clearScreen();
                                                            inventory.displayAllMagazineGenres();

                                                            cout << endl << "Press any key to continue..." ;
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 5: {
                                                            // new collection
                                                            clearScreen();
                                                            inventory.displayNewMagazineCollection();

                                                            cout << endl << "Press any key to continue..." ;
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 6: {
                                                            mgm = false;
                                                            cout << "Going back..." << endl;
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 7: {
                                                            mgm = false;
                                                            bm = false;
                                                            cm = false;
                                                            cout << "Logging out..." << endl;
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        default: {
                                                            cout << "Invalid number entered. Please try again..." << endl;
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }
                                                    }
                                                } while(mgm);
                                                break;
                                            }

                                            case 3: {
                                                bm = false;
                                                cout << "Going back to menu..." << endl;
                                                wait();
                                                clearScreen();
                                                break;
                                            }

                                            case 4: {
                                                bm = false;
                                                cm = false;
                                                cout << "Logging out..." << endl;
                                                wait();
                                                clearScreen();
                                                break;
                                            }

                                            default: {
                                                cout << "Invalid choice. Please try again..." << endl;
                                                wait();
                                                clearScreen();
                                                break;
                                            }
                                        }
                                    } while(bm);
                                    break;
                                }

                                case 4: {
                                    clearScreen();
                                    cout << "      Bookshop Inventory Management System       " << endl;
                                    cout << "-------------------------------------------------" << endl;
                                    cout << "              ---Rate a Book---                  " << endl;
                                    cout << "Please enter the name of the book: " << endl;

                                    string bookName;
                                    cin.ignore();
                                    cin >> ws;
                                    getline(cin, bookName);

                                    inventory.giveRating(bookName);

                                    cout << endl << "Press any key to continue...";
                                    cin.ignore();
                                    cin.get();
                                    clearScreen();
                                    break;
                                }

                                case 5: {
                                    cm = false;
                                    cout << "Logging out..." << endl;
                                    wait();
                                    clearScreen();
                                    break;
                                }

                                default: {
                                    cout << "Invalid choice. Please try again..." << endl;
                                    wait();
                                    clearScreen();
                                    break;
                                }
                            }
                        } while(cm);                        
                }else if( curId >= 10 && curId < 100){
                        // cashier menu
                        cout << "Logging in as cashier..." << endl;
                        wait();
                        clearScreen();
                        bool chm = true;
                        Cashier *curCashier = users.getCashierById(curId);
                        if(curCashier == nullptr){
                          cout << "Invalid cashier ID. Please try again..." << endl;
                          wait();
                          break;  
                        } 
                        do{
                            m.cashierMenu();

                            int cashierChoice;
                            cin >> cashierChoice;

                            switch(cashierChoice){
                                case 1: {
                                    // manage inventory
                                    clearScreen();
                                    bool im = true;

                                    do{
                                        m.inventoryMenu();
                                        int invChoice;
                                        cin >> invChoice;

                                        switch(invChoice){
                                            case 1: {
                                                // add new stock
                                                clearScreen();
                                                bool ns = true;

                                                do{
                                                    m.newStockMenu();
                                                    int addChoice;
                                                    cin >> addChoice;

                                                    switch(addChoice){
                                                        case 1: {
                                                            // add book
                                                            clearScreen();
                                                            addBook(inventory);
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 2: {
                                                            // add magazine
                                                            clearScreen();
                                                            addMagazine(inventory);
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        case 3: {
                                                            ns = false;
                                                            cout << "All the new stock added successfully..." << endl;
                                                            cout << endl << "Press any key to continue...";
                                                            cin.ignore();
                                                            cin.get();
                                                            clearScreen();
                                                            break;
                                                        }

                                                        default: {
                                                            cout << "Invalid number entered. Please try again..." << endl;
                                                            wait();
                                                            clearScreen();
                                                            break;
                                                        }
                                                    }
                                                } while(ns);
                                                break;
                                            }

                                            case 2: {
                                                // update stock
                                                clearScreen();
                                                cout << "      Bookshop Inventory Management System       " << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "            ---Updating the stock---             " << endl;
                                                cout << "Enter the name/ID of book/magazine: " << endl;
                                                string input;
                                                cin.ignore();
                                                getline(cin, input);
                                                
                                                cout << "Enter the number of items being added: " << endl;
                                                int newStock;
                                                cin >> newStock;

                                                bool isID = true;
                                                for (char c : input) {
                                                    if (!isdigit(c)) {
                                                        isID = false;
                                                        break;
                                                    }
                                                }

                                                if (isID) {
                                                    int id = stoi(input);
                                                    inventory.updateStock(id, newStock);
                                                }else{
                                                    inventory.updateStock(input, newStock);
                                                }
                                                wait();
                                                clearScreen();
                                                break;
                                            }

                                            case 3: {
                                                // check stock
                                                clearScreen();
                                                cout << "      Bookshop Inventory Management System       " << endl;
                                                cout << "-------------------------------------------------" << endl;
                                                cout << "            ---Checking the stock---             " << endl;
                                                cout << "Enter the name of the item: " << endl;
                                                string itemName;
                                                cin.ignore();
                                                getline(cin, itemName);

                                                int stock = inventory.getStock(itemName);
                                                if(stock > 0){
                                                    cout << itemName << " has stock " << stock << endl;
                                                }else{
                                                    cout << itemName << " is out of stock..." << endl;
                                                }
                                                wait();
                                                clearScreen();
                                                break;
                                            }

                                            case 4: {
                                                im = false;
                                                cout << "Going back to cashier menu..." << endl;
                                                wait();
                                                clearScreen();
                                                break;
                                            }

                                            case 5: {
                                                im = false;
                                                chm = false;
                                                cout << "Logging out..." << endl;
                                                wait();
                                                clearScreen();
                                                break; 
                                            }

                                            default: {
                                                cout << "Invalid number entered. Please try again..." << endl;
                                                wait();
                                                clearScreen();
                                                break;
                                            }
                                        }
                                    } while(im);
                                    break;
                                }

                                case 2: {
                                    // manage customers
                                    clearScreen();
                                    bool mcm = true;

                                    do{
                                        m.manageCustomerMenu();
                                        int manCustChoice;
                                        cin >> manCustChoice;

                                        switch(manCustChoice){
                                            case 1: {
                                                // register new customer
                                                clearScreen();
                                                addCustomer(users);

                                                cout << endl << "Press any key to continue...";
                                                cin.ignore();
                                                cin.get();
                                                clearScreen();
                                                break;
                                            }

                                            case 2: {
                                                // display customers
                                                clearScreen();
                                                users.displayCustomers();
                                                cout << endl << "Press any key to continue...";
                                                cin.ignore();
                                                cin.get();
                                                clearScreen();
                                                break;
                                            }

                                            case 3: {
                                                // sell items
                                                clearScreen();
                                                bool pm = true;
                                                Transaction transaction;
                                                cout << "Enter customer name: " << endl;
                                                string curCustomerName;
                                                cin.ignore();
                                                getline(cin, curCustomerName);

                                                Customer *curCustomer = users.getCustomerByName(curCustomerName);

                                                if(curCustomer != nullptr){
                                                    do{
                                                        m.purchaseMenu();
                                                        int purchaseChoice;
                                                        cin >> purchaseChoice;

                                                        switch(purchaseChoice){
                                                            case 1: {
                                                                // add item to billing
                                                                clearScreen();
                                                                addItem(curCustomer, inventory, transaction);
                                                                wait();
                                                                wait();
                                                                clearScreen();
                                                                break;
                                                            }

                                                            case 2: {
                                                                //generate receipt
                                                                clearScreen();
                                                                cout << "Generating receipt..." << endl;
                                                                wait();
                                                                clearScreen();

                                                                transaction.generateReceipt();

                                                                pm = false;
                                                                cout << endl << "Press any key to continue...";
                                                                cin.ignore();
                                                                cin.get();
                                                                clearScreen();
                                                                break;
                                                            }
                                                            
                                                            default: {
                                                                cout << "Invalid number entered. Please try again..." << endl;
                                                                wait();
                                                                clearScreen();
                                                                break;
                                                            }
                                                        }
                                                    } while(pm);
                                                }else{
                                                    cout << "Customer not found..." << endl;
                                                    wait();
                                                    clearScreen();
                                                }    
                                                break;
                                            }

                                            case 4: {
                                                mcm = false;
                                                cout << "Going back to cashier menu..." << endl;
                                                wait();
                                                clearScreen();
                                                break;
                                            }

                                            default: {
                                                cout << "Invalid number entered. Please try again..." << endl;
                                                wait();
                                                clearScreen();
                                                break;
                                            }
                                        }
                                    } while(mcm);
                                    break;
                                }

                                case 3: {
                                    chm = false;
                                    cout << "Logging out..." << endl;
                                    wait();
                                    clearScreen();
                                    break;
                                }

                                default: {
                                    cout << "Invalid choice. Please try again..." << endl;
                                    wait();
                                    clearScreen();
                                    break;
                                }
                            }
                        } while(chm);        
                }else if( curId == 1 ){
                        // manager menu
                        cout << "Logging in as manager" << endl;
                        wait();
                        clearScreen();
                        bool mrm = true;

                        do{
                            m.managerMenu();
                            int managerChoice;
                            cin >> managerChoice;

                            switch(managerChoice){
                                case 1: {
                                    // register cashier
                                    clearScreen();
                                    addCashier(users);
                                    
                                    cout << endl << "Press any key to continue...";
                                    cin.ignore();
                                    cin.get();
                                    clearScreen();
                                    break;
                                }

                                case 2: {
                                    // view all cashiers
                                    clearScreen();
                                    users.displayCashiers();

                                    cout << endl << "Press any key to continue...";
                                    cin.ignore();
                                    cin.get();
                                    clearScreen();
                                    break;
                                }

                                case 3: {
                                    // view all books
                                    clearScreen();
                                    inventory.displayAllBooks(true);

                                    cout << endl << "Press any key to continue...";
                                    cin.ignore();
                                    cin.get();
                                    clearScreen();
                                    break;
                                }

                                case 4: {
                                    // view all magazines
                                    clearScreen();
                                    inventory.displayAllMagazines(true);

                                    cout << endl << "Press any key to continue...";
                                    cin.ignore();
                                    cin.get();
                                    clearScreen();
                                    break;
                                }

                                case 5: {
                                    mrm = false;
                                    cout << "Logging out..." << endl;
                                    wait();
                                    clearScreen();
                                    break;
                                }

                                default: {
                                    cout << "Invalid number entered. Please try again..." << endl;
                                    wait();
                                    clearScreen();
                                    break;
                                }
                            }
                        } while(mrm);
                }else{
                    cout << "ID not found. Please try registering..." << endl;
                    cout << "Press any key to continue...";
                    cin.ignore();
                    cin.get();
                    clearScreen();
                }

                break;
            }

            case 2: {
                //guest mode
                cout << "Entering guest mode..." << endl;
                wait();
                clearScreen();
                bool gm = true;

                do{
                    m.guestMenu();

                    int guestChoice;
                    cin >> guestChoice;

                    switch(guestChoice){
                        case 1: {
                            // browse inventory
                            clearScreen();
                            bool gbm = true;

                            do{
                                m.guestBrowseMenu();
                                int browseChoice;
                                cin >> browseChoice;

                                switch(browseChoice){
                                    case 1: {
                                        //books menu
                                        clearScreen();
                                        bool bkm = true;

                                        do{
                                            m.guestBookMenu();
                                            int bookChoice;
                                            cin >> bookChoice;

                                            switch(bookChoice) {
                                                case 1: {
                                                    clearScreen();
                                                    // search book
                                                    cout << "      Bookshop Inventory Management System       " << endl;
                                                    cout << "-------------------------------------------------" << endl;
                                                    cout << "                Search book                      " << endl;
                                                    cout << "Please enter the name of the book: " << endl;

                                                    string bookName;
                                                    cin.ignore();
                                                    cin >> ws;
                                                    getline(cin, bookName); 
                                                    cout << "Searching the inventory..." << endl;
                                                    wait();
                                                    clearScreen();

                                                    inventory.searchBook(bookName);

                                                    cout << endl << "Press any key to continue..." << endl;;
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 2: {
                                                    // search book by series
                                                    clearScreen();
                                                    cout << "      Bookshop Inventory Management System       " << endl;
                                                    cout << "-------------------------------------------------" << endl;
                                                    cout << "                Search book                      " << endl;
                                                    cout << "Please enter the name of the series: " << endl;

                                                    string seriesName;
                                                    cin.ignore();
                                                    cin >> ws;
                                                    getline(cin, seriesName); 
                                                    cout << "Searching the inventory..." << endl;
                                                    wait();
                                                    clearScreen();

                                                    inventory.displayBookBySeries(seriesName);

                                                    cout << endl << "Press any key to continue..." << endl;
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 3: {
                                                    // search book by author
                                                    clearScreen();
                                                    cout << "      Bookshop Inventory Management System       " << endl;
                                                    cout << "-------------------------------------------------" << endl;
                                                    cout << "                Search book                      " << endl;
                                                    cout << "Please enter the name of the author: " << endl;

                                                    string authorName;
                                                    cin.ignore();
                                                    cin >> ws;
                                                    getline(cin, authorName); 
                                                    cout << "Searching the inventory..." << endl;
                                                    wait();
                                                    clearScreen();

                                                    inventory.displayBookByAuthor(authorName);

                                                    cout << endl << "Press any key to continue..." << endl;
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 4: {
                                                    // search book by genre
                                                    clearScreen();
                                                    cout << "      Bookshop Inventory Management System       " << endl;
                                                    cout << "-------------------------------------------------" << endl;
                                                    cout << "                Search book                      " << endl;
                                                    cout << "Please enter the genre: " << endl;

                                                    string genreName;
                                                    cin.ignore();
                                                    cin >> ws;
                                                    getline(cin, genreName); 
                                                    cout << "Searching the inventory..." << endl;
                                                    wait();
                                                    clearScreen();

                                                    inventory.displayBookByGenre(genreName);

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 5: {
                                                    // display all books
                                                    clearScreen();
                                                    inventory.displayAllBooks();

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 6: {
                                                    // display all series
                                                    clearScreen();
                                                    inventory.displayAllSeries();

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 7: {
                                                    // display all authors
                                                    clearScreen();
                                                    inventory.displayAllAuthors();

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 8: {
                                                    // display all genres
                                                    clearScreen();
                                                    inventory.displayAllBookGenres();

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 9: {
                                                    // new collection
                                                    clearScreen();
                                                    inventory.displayNewBookCollection();

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 10: {
                                                    bkm = false;
                                                    cout << "Going back..." << endl;
                                                    wait();
                                                    clearScreen();
                                                    break;
                                                }

                                                default: {
                                                    cout << "Invalid choice. Please try again...";
                                                    wait();
                                                    clearScreen();
                                                }
                                            }
                                        } while(bkm);
                                        break;
                                    }

                                    case 2: {
                                        // magazines menu
                                        clearScreen();
                                        bool mgm = true;

                                        do{
                                            m.guestMagazineMenu();
                                            int magazineChoice;
                                            cin >> magazineChoice;

                                            switch(magazineChoice){
                                                case 1: {
                                                    //search magazine
                                                    clearScreen();
                                                    cout << "      Bookshop Inventory Management System       " << endl;
                                                    cout << "-------------------------------------------------" << endl;
                                                    cout << "                Search magazine                      " << endl;
                                                    cout << "Please enter the title of the magazine: " << endl;

                                                    string magazineName;
                                                    cin.ignore();
                                                    cin >> ws;
                                                    getline(cin, magazineName); 
                                                    cout << "Searching the inventory..." << endl;
                                                    wait();
                                                    clearScreen();

                                                    inventory.searchMagazine(magazineName);

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 2: {
                                                    // search magazine by genre
                                                    clearScreen();
                                                    cout << "      Bookshop Inventory Management System       " << endl;
                                                    cout << "-------------------------------------------------" << endl;
                                                    cout << "                Search magazine                      " << endl;
                                                    cout << "Please enter the genre: " << endl;

                                                    string genreName;
                                                    cin.ignore();
                                                    cin >> ws;
                                                    getline(cin, genreName); 
                                                    cout << "Searching the inventory..." << endl;
                                                    wait();
                                                    clearScreen();

                                                    inventory.displayMagazineByGenre(genreName);

                                                    cout << endl << "Press any key to continue...";
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 3: {
                                                    // display all magazines
                                                    clearScreen();
                                                    inventory.displayAllMagazines();

                                                    cout << endl << "Press any key to continue..." ;
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 4: {
                                                    // display all genres
                                                    clearScreen();
                                                    inventory.displayAllMagazineGenres();

                                                    cout << endl << "Press any key to continue..." ;
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 5: {
                                                    // new collection
                                                    clearScreen();
                                                    inventory.displayNewMagazineCollection();

                                                    cout << endl << "Press any key to continue..." ;
                                                    cin.ignore();
                                                    cin.get();
                                                    clearScreen();
                                                    break;
                                                }

                                                case 6: {
                                                    mgm = false;
                                                    cout << "Going back..." << endl;
                                                    wait();
                                                    clearScreen();
                                                    break;
                                                }

                                                default: {
                                                    cout << "Invalid number entered. Please try again..." << endl;
                                                    wait();
                                                    clearScreen();
                                                    break;
                                                }
                                            }
                                        } while(mgm);
                                        break;
                                    }

                                    case 3: {
                                        gbm = false;
                                        cout << "Going back to guest menu..." << endl;
                                        wait();
                                        clearScreen();
                                        break;
                                    }

                                    default: {
                                        cout << "Invalid choice. Please try again..." << endl;
                                        wait();
                                        clearScreen();
                                        break;
                                    }
                                }
                            } while(gbm);
                            break;
                        }

                        case 2: {
                            // about store
                            clearScreen();
                            aboutStore(users, inventory, manager);

                            cout << endl << "Press any key to continue..." ;
                            cin.ignore();
                            cin.get();
                            clearScreen();
                            break;
                        }

                        case 3: {
                            gm = false;
                            cout << "Exitting guest menu..." << endl;
                            wait();
                            clearScreen();
                            break;
                        }

                        default: {
                            cout << "Invalid number entered. Please try again..." << endl;
                                wait();
                                clearScreen();
                                break;
                        }
                    }
                } while(gm);
                break;
            }

            case 3: {
                mm = false;
                cout << "Exiting the system...";
                break;
            }
            default: {
                cout << "Invalid number entered. Please try again..." << endl;
                wait();
                clearScreen();
                break;
            }
        }
    } while (mm);
    
    
    return 0;
}
