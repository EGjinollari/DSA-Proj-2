#include "idtree.h"
#include <vector>

void IDTree::Insert(int id, std::string fn, std::string ln, int bday, 
                     std::string origin, std::string dest) {
    bool unique = true;
    for (auto i : taken_ids) {
        if (i == id) {
            unique = false;
            break;
        }
    }

    if (unique) {
        Person* p = new Person(id, fn, ln, bday, origin, dest);
        insert(p, p->get_id());
        taken_ids.push_back(id);
    }
}

std::vector<Person*> IDTree::Search(std::string val) {
    std::vector<Person*> results;
    searchHelper(root, val, results);
    return results;
}

void IDTree::Delete(std::string target) {
    for (auto it = taken_ids.begin(); it != taken_ids.end(); ++it) {
    }
}