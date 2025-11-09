#include "bdtree.h"
#include <vector>

using namespace std;

void BDTree::Insert(int id, string fn, string ln, int bday, string origin, string dest) {
    if (taken_ids.count(id) > 0) {
        return;
    }

    Person* p = new Person(id, fn, ln, bday, origin, dest);
    insert(p, p->get_birthday());
    taken_ids.insert(id);
}

vector<Person*> BDTree::Search(string val) {
    vector<Person*> results;
    searchHelper(root, val, results);
    return results;
}