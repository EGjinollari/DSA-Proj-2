#include "bforest.h"
#include "children_trees/bdtree.h"
#include "children_trees/idtree.h"
#include "children_trees/fntree.h"
#include "children_trees/lntree.h"
#include "children_trees/oritree.h"
#include "children_trees/destree.h"

using namespace std;

BForest::BForest() {
    id = new IDTree();
    fn = new FNTree();
    ln = new LNTree();
    bd = new BDTree();
    ori = new ORITree();
    des = new DESTree();
}

BForest::~BForest() {
    delete id;
    delete fn;
    delete ln;
    delete bd;
    delete ori;
    delete des;
}

void BForest::Insert(int id, string fn, string ln, int bday, string origin, string dest) {
    this->id->Insert(id, fn, ln, bday, origin, dest);
    this->fn->Insert(id, fn, ln, bday, origin, dest);
    this->ln->Insert(id, fn, ln, bday, origin, dest);
    this->bd->Insert(id, fn, ln, bday, origin, dest);
    this->ori->Insert(id, fn, ln, bday, origin, dest);
    this->des->Insert(id, fn, ln, bday, origin, dest);
}

void BForest::Delete(string id) {
    auto target = this->id->Search(id);
    this->id->Delete(target[0]->get_id());
    this->fn->Delete(target[0]->get_first());
    this->ln->Delete(target[0]->get_last());
    this->bd->Delete(target[0]->get_birthday());
    this->ori->Delete(target[0]->get_origin());
    this->des->Delete(target[0]->get_destination());
}

vector<Person*> BForest::Search(string cat, string val) {
    if (cat == "id") {
        return id->Search(val);
    }
    if (cat == "first") {
        return fn->Search(val);
    }
    if (cat == "last") {
        return ln->Search(val);
    }
    if (cat == "birthday") {
        return bd->Search(val);
    }
    if (cat == "origin") {
        return ori->Search(val);
    }
    if (cat == "destination") {
        return des->Search(val);
    }
    return vector<Person*>();
}