#include "node.h"


bool Node::get_color(){
    return color;
}

void Node::flip_color(){
    color = !color;
}

Person* Node::get_data(){
    return person;
}