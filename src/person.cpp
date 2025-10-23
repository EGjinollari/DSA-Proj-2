#include <string>
#include "person.h"

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