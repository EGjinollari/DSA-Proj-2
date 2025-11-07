#include "lntree.h"
#include <vector>

void LNTree::Insert(int id, std::string fn, std::string ln, int bday, 
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
        insert(p, p->get_last());
        taken_ids.push_back(id);
    }
}

std::vector<Person*> LNTree::Search(std::string val) {
    std::vector<Person*> results;
    searchHelper(root, val, results);
    return results;
}

void LNTree::Delete(std::string target) {
    for (auto it = taken_ids.begin(); it != taken_ids.end(); ) {
        if (std::to_string(*it) == target) {
            it = taken_ids.erase(it);
        } else {
            ++it;
        }
    }
}