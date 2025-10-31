#include <string>
#include "person.h"

Person::Person(int id, std::string fn, std::string ln, int bday, std::string o, std::string d){
    this->id = id;
    first_name = fn;
    last_name = ln;
    birthday = bday;
    origin = o;
    destination = d;
}

std::string Person::get_first(){
    return first_name;
}

std::string Person::get_last(){
    return last_name;
}

std::string Person::get_origin(){
    return origin;
}

std::string Person::get_destination(){
    return destination;
}

int Person::get_birthday(){
    return birthday;
}

int Person::get_id(){
    return id;
}