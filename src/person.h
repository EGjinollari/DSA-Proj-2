#pragma once

#include <string>

class Person{
    private:
        

    std::string first_name;
    std::string last_name;
    int birthday;
    std::string origin;
    std::string destination;


    public:
    std::string get_first();
    std::string get_last();
    int get_birthday();
    std::string get_origin();
    std::string get_destination();

};