#pragma once

#include <string>
#include "person.h"

struct Node{

    Person* person;
    bool color = true;     
    Node* left;
    Node* right;

    bool get_color();
    void flip_color();
    Person* get_data();
};