#include "fntree.h"
#include <vector>

void FNTree::Insert(int id, std::string fn, std::string ln, int bday, 
                     std::string origin, std::string dest) {
    bool unique = true;
    if (taken_ids.find(id) == taken_ids.end()){
        unique = false;
    }


    if (unique) {
        Person* p = new Person(id, fn, ln, bday, origin, dest);
        insert(p, p->get_first());
        taken_ids.insert(id);
    }
}

std::vector<Person*> FNTree::Search(std::string val) {
    std::vector<Person*> results;
    searchHelper(root, val, results);
    return results;
}

