#include "Librarian.h"
#include "Student.h"
#include "Teacher.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <chrono>

Librarian::Librarian()
{
    fill_creds();
    for (std::string username : usernames) {
        database.push_back({ username });
    }
}

void Librarian::fill_creds() {
    std::ifstream student;
    student.open("student.txt");
    int role;
    std::string id, pw;
    while (!student.eof()) {
        student >> role >> id >> pw;
        if (role == 2) {
            usernames.push_back(id);
            passwords.push_back(pw);
        }
        all_users.push_back({ role, id, pw });

    }
}

bool Librarian::check_auth(std::string id, std::string pw) {
    for (int i = 0; i < usernames.size(); ++i) {
        if (id == usernames[i]) {
            if (pw == passwords[i]) {
                session_username = usernames[i];
                session_password = passwords[i];
                index_in_database = i;
                return true;
            }
            else {
                break;
            }
        }
    }
    return false;
}

void Librarian::add_new_user(int role, std::string username, std::string password)
{
    LibrarianData info = { role, username, password };
    all_users.push_back(info);
    this->total_num_of_users = all_users.size();
}

bool Librarian::delete_users(std::string username)
{   
    LibrarianData to_delete = *search_username(username);
    if (to_delete.job == 2)
    {
        int index = search_username(username) - &all_users[0];
        all_users.erase(all_users.begin() + index);
        all_users.shrink_to_fit();
        return true;
    }
    else if (to_delete.job == 0 || to_delete.job == 1)
    {
        //check to see if the user has any books on loan
        if (to_delete.job == 1)
        {
            Teacher t1;
            bool borrow_teacher = t1.has_borrowed_books_teacher(username);
            if (borrow_teacher == true)
            {
                std::cout << "User cannot be deleted. Books are still on loan." << std::endl;
                return false;
            }
            else
            {
                //remove from any reserve's list
                Library temp;
                temp.remove_reserver(username);
                //delete from all_users
                int index = search_username(username) - &all_users[0];
                all_users.erase(all_users.begin() + index);
                all_users.shrink_to_fit();
                std::cout << "User has been deleted successfully." << std::endl;
                return true;
            }
        }
        if (to_delete.job == 0)
        {
            Student s1;
            bool borrow_student = s1.has_borrowed_books_student(username);
            if (borrow_student == true)
            {
                std::cout << "User cannot be deleted. Books are still on loan." << std::endl;
                return false;
            }
            else
            {
                //remove from any reserve's list
                Library temp;
                temp.remove_reserver(username);
                //delete from all_users
                int index = search_username(username) - &all_users[0];
                all_users.erase(all_users.begin() + index);
                all_users.shrink_to_fit();
                std::cout << "User has been deleted successfully." << std::endl;
                return true;
            }
        }
    }
    return false;
}

LibrarianData* Librarian::search_username(std::string username)
{
    std::vector<LibrarianData> values;
    for (LibrarianData info : all_users) {
        if (info.user == username) {
            values.push_back(info);
        }
    }
    return &values[0];
}

void Librarian::add_new_user(int role, std::string name, std::string password)
{
    LibrarianData new_user = { role, name, password };
    all_users.push_back(new_user);
    this->total_num_of_users = all_users.size();
}
