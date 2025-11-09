#include "oritree.h"
#include <vector>

using namespace std;

// Insert into the origin tree
void ORITree::Insert(int id, string fn, string ln, int bday, string origin, string dest) {
    if (taken_ids.count(id) > 0) {
        return;
    }

    Person* p = new Person(id, fn, ln, bday, origin, dest);
    insert(p, p->get_origin());
    taken_ids.insert(id);
}

// Search the origin tree
vector<Person*> ORITree::Search(string val) {
    vector<Person*> results;
    searchHelper(root, val, results);
    return results;
}