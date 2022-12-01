#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Library.h"
#include "Student.h"
#include "Teacher.h"

typedef struct LibrarianData {
	int job;
	std::string user;
	std::string pass;
}LibrarianData;

class Librarian
{
private:
	std::string session_username, session_password;
	std::vector<std::string> usernames;
	std::vector<std::string> passwords;
	std::vector<std::string> database;
	std::vector<LibrarianData> all_users;
	int index_in_database;
	int total_num_of_users;
public:
	Librarian();
	void fill_creds();
	bool check_auth(std::string id, std::string pw);
	void add_new_user(int role, std::string username, std::string password);
	bool delete_users(std::string username);
	LibrarianData* search_username(std::string username);
	void add_new_user(int role, std::string name, std::string password);

};