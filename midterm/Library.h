#pragma once
#include <vector>
#include <string>

typedef struct Book {
    long long int isbn;
    std::string title;
    std::string author;
    std::string category;
    int id;
    double due_in;  // -1 if in available, nonnegative (>0) if on loan
} Book;

class Library {
    private:
        std::vector<Book> catalog;
        int number_of_books;
        int consec_id;
    public:
        Library();
        void print_book(Book book);
        void print_books_vector(std::vector<Book> bookvec);
        void print_all_books();
        Book* binary_search_catalog(int id, int start, int end);
        Book* search_id(int id);
        Book borrow_book(int id, int borrow_days);
        void return_book(int id);
        bool delete_book(int id);
        void add_book(long long int isbn, std::string title, std::string author, std::string category);
        void update_day(double days);
        Book search_catalog_by_id(int id, int start, int end);
        void operator<<(const Book& book);
        void sort_alphabetically_title(std::vector<Book>& vec);
        friend std::istream& operator>>(std::istream& in, const Book& book);
        std::vector<Book> search_book_isbn(long long int isbn);
        std::vector<Book> search_book_title(std::string title);
        std::vector<Book> search_book_category(std::string category);
        std::vector<Book> search_book_author(std::string author);
        void set_loan_duration(int id, int borrow_days);
        Book get_last_book();
};