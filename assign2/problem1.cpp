// CMPT 225 D100 - Summer 2025
// Instructor: Jocelyn Minns
// DO NOT REPOST
// Student name: Makori Dennis Chacha

#include <iostream>
#include <string>
#include <vector>
#include <memory> // Smart pointer utilization? is it allowed??
#include <cassert>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::cout;
using std::cin;
using std::endl;

// Struct for books

struct Book {
    
    string title;
    string author;
    bool isCheckedOut;
    
};

// Abstract class
class Library {
public:
    // virtual destructor, common practice for abstract classes
    virtual ~Library() {}; 

    // Adds a new book to the library at a specific ID (shelf spot)
    virtual bool addBook(int id, const std::string& title, const std::string& author) = 0;

    // Removes a book from the library based on its ID
    virtual bool removeBook(int id) = 0;

    // Replaces an existing book at a given ID with a new title and author
    virtual bool swapBook(int id, const std::string& newTitle, const std::string& newAuthor) = 0;

    // Flags the book at the given ID as checked out (borrowed)
    virtual bool checkOutBook(int id) = 0;

    // Flags the book at the given ID as returned (in the library)
    virtual bool returnBook(int id) = 0;

    // Checks if the book at the given ID is currently in the library
    virtual bool isInLibrary(int id) const = 0;

    // Returns a string with information about the book at the given ID
    virtual std::string getBookInfo(int id) const = 0;

    // Returns the total number of books currently stored in the library
    virtual int totalBooks() const = 0;

    // Returns the number of books that are currently available in the library
    virtual int booksInLibrary() const = 0;

    // Returns the number of books that are currently checked out
    virtual int booksLentOut() const = 0;
    
};


class SFULibrary : public Library{
    

public:
    // Default constructor, initializes the books variables with 100 books with id's from 0-100
    SFULibrary(int defaultCapacity = 0){
        // Setting this to zero ensures efficient memory utilization, no excess memory is created, size starts out at zero and increases as per the user's needs
        
        
        books.resize(defaultCapacity);
    }
    bool addBook(int id, const std::string& title, const std::string& author) override {
        
        // This check here should take care of the case where we have a different signedness comparison
        
        if(id < 0){
            cout << "Invalid book ID .\n";
            return false;
        }
        // If the id is integer and books.size() returns an unsigned long int variable, different ranges. s
        if(id >= static_cast<int>(books.size())){
            
            books.resize(id + 1);
            
        }
        // If there already exists a book with that same id.
        if(books[id]){
            cout << "A book already exists with this ID, try a different ID number. \n";
            
            return false;
        }
        // At this point, we already know that there's an null pointer here so we make the pointer at this index point to a new book object with the values provided by the user.
        
        books[id] = make_unique<Book>(Book{title, author, false});
        
        return true;
        
    }
    bool removeBook(int id) override{
        // Check if the book is there.
        /*
         id could be less than 0
         id could be greater than the size
         it could be pointing to a nullptr
         */
        if(id < 0 || id >= static_cast<int>(books.size()) || !books[id]){
            cout << "There's no book with this id at this library" << endl;
            return false;
        }
        
        // The book exists and this doesn't point to a nullptr
        
        if(books[id]){
            books[id] = nullptr;
            return true;
        }
            
        return false;
        
    }
    // Not implemented
    bool swapBook(int id, const std::string& newTitle, const std::string& newAuthor) override {
        
        //Check if there's a book here and then swap the books
        if(id < 0 || id >= static_cast<int>(books.size()) || !books[id])
        {
            cout << "No existing book found at this ID to swap." << endl;
            return false;
        }
    
        books[id] = make_unique<Book>(Book{newTitle, newAuthor, false});
            
        return true;
        
        
    }
    bool checkOutBook(int id) override {
        // Check if it's there
        if(books[id]){
            // A book exists with this id
            if(books[id]->isCheckedOut == true){
                cout << "The book is already lent out, you'll have to wait until it gets returned in order to borrow it." << endl;
                return false;
            }
            books[id]->isCheckedOut = true;
            return true;
        }
        else
            cout << "The library does not have this book, please try a different library." << endl;
            
        return false;
    }
    bool returnBook(int id) override{
        
        // Three different cases here, one is ambigious
        
        // Does the book id exist in the records?
        // out of bounds and nullptrs
        if(id < 0|| id >= static_cast<int>(books.size())){
            cout << "The ID you've entered is invalid" << endl;
            return false;
            
        }
        if(books[id]){
            // Now check if its actually given out??
            if(books[id]->isCheckedOut == true){
                books[id]->isCheckedOut = false;
                return true;
            }
            
            cout << "This book was never checked out, no need to check it in. It might be that the person that checked it in forgot to scan it out." << endl;
            return false;
        }
        // The book doesn't even exist?or it was never borrowed? or there's no record of it being borrowed?
        return false;
    }
    bool isInLibrary(int id) const override{
        // Book exists, non-null ptr, nullptr check is redundant because we have a return false statement out there.
        
        if(id < 0 || id >= static_cast<int>(books.size())){
            cout << "Invalid ID number. \n" ;
            return false;
        }
        
        if (books[id])
            return true;
        
        // Returns false if it doesn't point to anything
        return false;
    }
    string getBookInfo(int id) const override{
        // Should print something or return a string, not sure...?? how exactly do we do this?
        if( id < 0 || id >= static_cast<int>(books.size())){
            return "No book found at this ID. \n";
        }
        // this statement is equivalent to books[id] == nullptr
        else if(!books[id]){
            return "No book found at this ID.\n";
        }
        const Book& book = *books[id];
        
        string status = book.isCheckedOut ? "Checked out" : "Available";
        
        return "Title: " + book.title + "\nAuthor: " + book.author + "\nStatus: " + status;
        
    }
    
    int totalBooks() const override{
        int bookCount = 0;
        
        // Run a loop and add all the non-null ptrs
        
        for(int i = 0; i < static_cast<int>(books.size()); i++){
            // Non-null ptr, a book exists with this id in the records
            if(books[i]){
                bookCount++;
            }
            else{
                continue;
            }
        }
        // Go through everything and count the number of books stored inside
        
        return bookCount;
        
    }
    int booksInLibrary() const override{
        
        int inLibrary = 0;
        
        // Just count the ones where isCheckedOut == false
        
        for(int i = 0; i< static_cast<int>(books.size()); i++){
            
            // If there's a book with the id
            
            if(books[i]){
                
                // Only count books that are still at the library and not lent out
                if(books[i]->isCheckedOut == false)
                    inLibrary++;
                else
                    continue;
                
            }
        }
        return inLibrary;
    }
    
    int booksLentOut() const override {
        
        int lentOut = 0;
        
        // Count the ones where the isCheckedOut == true.
        
        for(int i = 0; i < static_cast<int>(books.size()); i++) {
            // Check if the book exists
            if(books[i]){
                if(books[i]->isCheckedOut == true)
                    lentOut++;
            }
        }
        
        return lentOut;
    }
    
private:
    vector<unique_ptr<Book>> books;
};

// Revise
void runAllTests() {
    SFULibrary lib;
    
     // Check that this first statement returns false and prints the error statement in the function
    assert(!lib.addBook(-1, "Invalid", "X"));
    // this one should work without any issues
    
    assert(lib.addBook(0, "Clean Code", "Martin"));
    
    assert(lib.checkOutBook(0));
    
    assert(!lib.checkOutBook(0));
    
    // after a book is checked out, checkOutBook should return false, the assertion will be true if so
    
    assert(lib.returnBook(0));
    
    assert(!lib.returnBook(0));
    // the being being returned should reflect in the code
    
    assert(lib.removeBook(0));
    // should be true
    
    assert(!lib.removeBook(0));
    // will be true then evaluated to false
    
    // Same deal as before
    
    assert(lib.totalBooks() == 0);
    // no more books in the library
    
    assert(lib.getBookInfo(0) == "No book found at this ID.\n");
    //this assertion keeps failing
    // All good now the test passed, not sure why it passed now but not before
}

/*
 
 assertions can help find bugs more effectively
 you put lines in your code that you know should work and if they don't you get it immediately instead of waiting for something like a segmentation fault or something else that might happen down the line
 how to implement?
 don't put anything in an assertion that's actually required for the code to work
 leave them in all the time
 even for speed, remove them after you've tested it extensively
 there is a performance penalty for this
 idk if this is important
 
 */
int main() {
    
    // unique_ptr<Library> lib = make_unique<SFULibrary>();
    
     Library* lib = new SFULibrary();
    
    lib->addBook(0, "1984", "George Orwell");
    lib->addBook(1, "The Hobbit", "J.R.R. Tolkien");
    lib->addBook(2, "Dune", "Frank Herbert");

    std::cout << lib->getBookInfo(0) << "\n";
    lib->checkOutBook(0);
    std::cout << lib->getBookInfo(0) << "\n";

    lib->returnBook(0);
    std::cout << lib->getBookInfo(0) << "\n";
    
    cout << lib->getBookInfo(2) <<"\n";
    
    lib->swapBook(2, "Foundation", "Isaac Asimov");
    
    std::cout << lib->getBookInfo(2) << "\n";

    std::cout << "Total books: " << lib->totalBooks() << "\n";
    std::cout << "Books in: " << lib->booksInLibrary() << "\n";
    std::cout << "Books out: " << lib->booksLentOut() << "\n";
    
    
    runAllTests();
    cout << "All tests passed !\n" <<endl;
    
     delete lib;
    return 0;
    
}
// DONE and dusted
// Problem 2 now

