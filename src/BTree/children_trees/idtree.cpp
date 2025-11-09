#include "idtree.h"
#include <vector>

using namespace std;
// Insert into the ID tree
void IDTree::Insert(int id, string fn, string ln, int bday, string origin, string dest) {
    if (taken_ids.count(id) > 0) {
        return;
    }

    Person* p = new Person(id, fn, ln, bday, origin, dest);
    insert(p, p->get_id());
    taken_ids.insert(id);
}
// Search the ID tree
vector<Person*> IDTree::Search(string val) {
    vector<Person*> results;
    searchHelper(root, val, results);
    return results;
}