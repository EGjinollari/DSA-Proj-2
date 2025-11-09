#pragma once

#include <string>
// Class to store the data from the csv
class Person{
    private:
        
    std::string id;
    std::string first_name;
    std::string last_name;
    std::string birthday;
    std::string origin;
    std::string destination;

    public:
    Person(int id, std::string fn, std::string ln, int bday, std::string o, std::string d);
    
    // Getters
    std::string get_first();
    std::string get_last();
    std::string get_birthday();
    std::string get_id();
    std::string get_origin();
    std::string get_destination();

};