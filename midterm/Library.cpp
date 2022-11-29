#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "Library.h"
#include <cstring>
#include <iterator>

Library::Library() {
    std::ifstream books, users;
    long long int isbn;
    std::string title;
    std::string author;
    std::string category;
    int copies;
    int is_teacher;
    std::string username;
    std::string password;
    Book book;
    consec_id = 0;

    books.open("book.txt");
    if (books.fail()) {
        std::cerr << "Could not open books file!" << std::endl;
        exit(1);
    }

    users.open("student.txt");
    if (users.fail()) {
        std::cerr << "Could not open credentials file!";
        exit(1);
    }

    catalog.push_back({ -1, "", "", "", -1, -1 });  // Invalid book in catalog to return pointers as

    while (!books.eof()) {
        books >> isbn >> title >> author >> category >> copies;
        for (int i = 0; i < copies; ++i) {
            book = { isbn, title, author, category, consec_id, -1 };
            this->catalog.push_back(book);
            consec_id++;
        }
    }
    number_of_books = catalog.size();
}

void Library::print_book(Book book) {
    std::cout << "ISBN:     " << book.isbn << std::endl;
    std::cout << "Title:    " << book.title << std::endl;
    std::cout << "Author:   " << book.author << std::endl;
    std::cout << "Category: " << book.category << std::endl;
    std::cout << "Intrn ID: " << book.id << std::endl;
    std::cout << "Due in:   " << book.due_in << std::endl << std::endl;
}

Book* Library::binary_search_catalog(int id, int start, int end) {
    if (start <= end) {
        int mid = (start + end) / 2;
        if (catalog[mid].id == id) {
            return &catalog[mid];
        }
        if (catalog[mid].id > id) {
            return binary_search_catalog(id, start, mid - 1);
        }
        if (catalog[mid].id < id) {
            return binary_search_catalog(id, mid + 1, end);
        }
    }
    return &catalog[0];
}

void Library::print_books_vector(std::vector<Book> bookvec) {
    for (Book book : bookvec) {
        print_book(book);
    }
}

void Library::print_all_books() {
    for (Book book : catalog) {
        print_book(book);
    }
};

Book Library::borrow_book(int id, int borrow_days) {
    Book* bookptr = search_id(id);
    int index = bookptr - &catalog[0];
    catalog[index].due_in = borrow_days;
    return *(bookptr);
}

Book* Library::search_id(int id) {
    return binary_search_catalog(id, 0, this->number_of_books - 1);
}

void Library::return_book(int id) {
    Book* bookptr = search_id(id);
    bookptr->due_in = -1;
}

bool Library::delete_book(int id) {
    Book to_delete = *search_id(id);
    if (to_delete.isbn != -1) {
        int index = search_id(id) - &catalog[0];
        catalog.erase(catalog.begin() + index);
        catalog.shrink_to_fit();
        return true;
    }
    return false;
}

void Library::add_book(long long int isbn, std::string title, std::string author, std::string category) {
    Book book = { isbn, title, author, category, consec_id++, -1 };
    catalog.push_back(book);
    this->number_of_books = catalog.size();
}

void Library::update_day(double days) {
    for (int book_iter = 0; book_iter < catalog.size(); ++book_iter) {
        if (catalog[book_iter].due_in > 0) {
            catalog[book_iter].due_in -= days;
            if (catalog[book_iter].due_in < 0) {
                catalog[book_iter].due_in = 0;
            }
        }
    }
}

void Library::operator<<(const Book& book) {
    std::cout << "ISBN:     " << book.isbn << std::endl;
    std::cout << "Title:    " << book.title << std::endl;
    std::cout << "Author:   " << book.author << std::endl;
    std::cout << "Category: " << book.category << std::endl;
    std::cout << "Intrn ID: " << book.id;
    //return out;
}

void Library::sort_alphabetically_title(std::vector<Book>& vec) {  // Pass vector of structs. If you want to modify the original vector, call it by reference.
    int sorted = 0;                                       // If you want to return a new vector without modifying the original vector, you need to
    while (sorted < vec.size() - 1) {                     // declare the function return type as std::vector<BookAndDue> and have a temporary vector
        sorted = 0;                                       // inside this function to hold the vector to be worked on (ex. std::vector<BookAndDue> temp = vec;)
        for (int i = 0; i < vec.size() - 1; ++i) {
            if (strcmp(vec[i].title.c_str(), vec[i + 1].title.c_str()) > 0) {  // Make the comparison between the name strings, c_str() is called because strcmp is a C function and can only take in C style strings
                std::swap(vec[i], vec[i + 1]);                               // Swap the vector indices (which are structs) if the name is not in alphabecial order
            }
            else {
                sorted++;
            }
        }
    }
}

/* Search functions by Liz */
std::vector<Book> Library::search_book_isbn(long long int isbn) {
    std::vector<Book> values;
    for (Book book : catalog) {
        if (book.isbn == isbn) {
            values.push_back(book);
        }
    }
    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::vector<Book> Library::search_book_title(std::string title) {
    std::vector<Book> values;
    for (Book book : catalog) {
        if (book.title == title) {
            values.push_back(book);
        }
    }
    
    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::vector<Book> Library::search_book_author(std::string author) {
    std::vector<Book> values;
    for (Book book : catalog) {
        if (book.author == author) {
            values.push_back(book);
        }
    }
    
    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::vector<Book> Library::search_book_category(std::string category) {
    std::vector<Book> values;
    for (Book book : catalog) {
        if (book.category == category) {
            values.push_back(book);
        }
    }

    //checking if there is more than one book
    if (values.size() > 1) {
        sort_alphabetically_title(values);
    }
    return values;
}

std::istream& operator>>(std::istream& in, Book& book) {
    std::cout << "ISBN:     ";
    in >> book.isbn;
    std::cout << "Title:    ";
    in >> book.title;
    std::cout << "Author:   ";
    in >> book.author;
    std::cout << "Category: ";
    in >> book.category;
    std::cout << "Intrn ID: ";
    in >> book.id;
    return in;
}

void Library::set_loan_duration(int id, int borrow_days) {
    int index = search_id(id) - &catalog[0];
    catalog[index].due_in = borrow_days;
}

Book Library::get_last_book() {
    return catalog.back();
}