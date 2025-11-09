#include "bforest.h"
#include "children_trees/bdtree.h"
#include "children_trees/idtree.h"
#include "children_trees/fntree.h"
#include "children_trees/lntree.h"
#include "children_trees/oritree.h"
#include "children_trees/destree.h"

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

void BForest::Insert(int id, std::string fn, std::string ln, int bday, 
                      std::string origin, std::string dest) {
    this->id->Insert(id, fn, ln, bday, origin, dest);
    this->fn->Insert(id, fn, ln, bday, origin, dest);
    this->ln->Insert(id, fn, ln, bday, origin, dest);
    this->bd->Insert(id, fn, ln, bday, origin, dest);
    this->ori->Insert(id, fn, ln, bday, origin, dest);
    this->des->Insert(id, fn, ln, bday, origin, dest);
}

void BForest::Delete(std::string id) {

    auto target = this->id->Search(id);

    std::string delete_id = target[0]->get_id();
    std::string first = target[0]->get_first();
    std::string last = target[0]->get_last();
    std::string bday = target[0]->get_birthday();
    std::string origin = target[0]->get_origin();
    std::string destination = target[0]->get_destination();


    this->id->Delete(delete_id);
    this->fn->Delete(first);
    this->ln->Delete(last);
    this->bd->Delete(bday);
    this->ori->Delete(origin);
    this->des->Delete(destination);
}

std::vector<Person*> BForest::Search(std::string category, std::string val) {
    if (category == "id") {
        return id->Search(val);
    }
    if (category == "first") {
        return fn->Search(val);
    }
    if (category == "last") {
        return ln->Search(val);
    }
    if (category == "birthday") {
        return bd->Search(val);
    }
    if (category == "origin") {
        return ori->Search(val);
    }
    if (category == "destination") {
        return des->Search(val);
    }
    return std::vector<Person*>();
}