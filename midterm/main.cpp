#include "Library.h"
#include "Teacher.h"
#include "Student.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <chrono>
#define SECONDS_PER_DAY 5

int main() {
	Student student = Student();
	Teacher teacher = Teacher();
	Library library = Library();

	std::string usr;
	std::string pas;
	bool proceed;
	bool valid_student, valid_teacher;

	while (1) {
		auto start = std::chrono::steady_clock::now();
		std::cout << "Enter username and password, space-separated: ";
		std::cin >> usr;
		std::cin >> pas;

		valid_student = student.check_auth(usr, pas);
		valid_teacher = teacher.check_auth(usr, pas);

		if (!valid_teacher  && !valid_student) {
			std::cout << "Invalid login! Please check your username and password" << std::endl;
			continue;
		}

		auto end = std::chrono::steady_clock::now();
		double days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
		student.update_day(days_passed);
		teacher.update_day(days_passed);
		library.update_day(days_passed);

		if (valid_teacher) {  // If it is valid teacher, then call menu from teacher
			auto start = std::chrono::steady_clock::now();
			do {
				proceed = teacher.menu(library);
			} while (proceed);
			auto end = std::chrono::steady_clock::now();
			double days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
			student.update_day(days_passed);
		}
		
		if (valid_student) {  // If it is valid student, then call menu from teacher
			auto start = std::chrono::steady_clock::now();
			do {
				proceed = student.menu(library);
			} while (proceed);
			auto end = std::chrono::steady_clock::now();
			double days_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / (1000.0 * SECONDS_PER_DAY);
			teacher.update_day(days_passed);
		}
	}
	return 0;
}