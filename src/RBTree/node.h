#pragma once

#include <string>
#include "person.h"

struct Node{

    Person* person;
    bool color = true;  // true =  red
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;


    Node(Person* p);
    bool get_color();
    void flip_color();
    Person* get_data();
};