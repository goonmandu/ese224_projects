#include "third_party/json.hpp"
#include <iterator>
#include <iostream>
#include <fstream>
#include <list>

using json = nlohmann::json;

template <typename T>
void print_list(std::list<T> tlist) {
    auto it = tlist.begin();
    while (it != tlist.end()) {
        std::cout << *it << ", ";
        std::advance(it, 1);
    }
    std::cout << std::endl;
}

int main() {
    std::ifstream r("json/readers.json");
    std::ifstream c("json/catalog.json");
    std::ifstream resv("json/resandlikes.json");
    json readers = json::parse(r);
    json catalog = json::parse(c);
    json reservations = json::parse(resv);
    readers["added"] = {
        {"is_teacher", false},
        {"borrowed_books", {}}
    };
    readers.erase(readers.find("Student1"));
    std::cout << readers["added"]["is_teacher"] << std::endl;
    for (auto it = readers.begin(); it != readers.end(); ++it) {
        std::cout << it.key() << " : " << it.value()["is_teacher"] << "\n";
    }
    std::ofstream o("json/rmodified.json");
    o << std::setw(4) << readers << std::endl;

    std::list<std::string> rlist;
    for (auto it = reservations["1234321"]["reservers"].begin(); it != reservations["1234321"]["reservers"].end(); ++it) {
        rlist.push_back(*it);
    }
    print_list(rlist);
    
    json testjson = {
        {"u1", {
            {"username", "u1lmao"},
            {"password", "pass1kek"}
        }}
    };

    std::string username;
    std::string newpass;
    std::cout << testjson["u1"] << std::endl;
    std::cout << "Enter a username ";
    std::cin >> username;
    if (testjson.contains(username)) {
        std::cout << "Enter new password ";
        std::cin >> newpass;
        testjson["u1"]["password"] = newpass;
    }
    std::cout << testjson["u1"] << std::endl;
}