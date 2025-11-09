#include "destree.h"
#include <vector>

using namespace std;
// Insert into the destination tree
void DESTree::Insert(int id, string fn, string ln, int bday, string origin, string dest) {
    if (taken_ids.count(id) > 0) {
        return;
    }

    Person* p = new Person(id, fn, ln, bday, origin, dest);
    insert(p, p->get_destination());
    taken_ids.insert(id);
}
// Search the destination tree
vector<Person*> DESTree::Search(string val) {
    vector<Person*> results;
    searchHelper(root, val, results);
    return results;
}