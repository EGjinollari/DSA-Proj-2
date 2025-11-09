#include "rbforest.h"
#include "children_trees/bdtree.h"
#include "children_trees/idtree.h"
#include "children_trees/fntree.h"
#include "children_trees/lntree.h"
#include "children_trees/idtree.h"
#include "children_trees/oritree.h"
#include "children_trees/destree.h"

RBForest::~RBForest(){
    delete id;
    delete fn;
    delete ln;
    delete bd;
    delete ori;
    delete des;
}


RBForest::RBForest(){
    id = new IDRBTree();
    fn = new FNRBTree();
    ln = new LNRBTree();
    bd = new BDRBTree();
    ori = new ORIRBTree();
    des = new DESRBTree();
}

void RBForest::Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest){

    this->id->Insert(id, fn, ln, bday, origin, dest);
    this->fn->Insert(id, fn, ln, bday, origin, dest);
    this->ln->Insert(id, fn, ln, bday, origin, dest);
    this->bd->Insert(id, fn, ln, bday, origin, dest);
    this->ori->Insert(id, fn, ln, bday, origin, dest);
    this->des->Insert(id, fn, ln, bday, origin, dest);
}

void RBForest::Delete(std::string id){

    auto target = this->id->Search(id);

    Person* p = target[0];

    this->id->Delete(this->id->get_root(), p);
    this->fn->Delete(this->fn->get_root(), p);
    this->ln->Delete(this->ln->get_root(), p);
    this->bd->Delete(this->bd->get_root(), p);
    this->ori->Delete(this->ori->get_root(), p);
    this->des->Delete(this->des->get_root(), p);
}

std::vector<Person*> RBForest::Search(std::string category, std::string val){
    if (category == "id"){
        return id->Search(val);
    }
    if (category == "first"){
        return fn->Search(val);
    }
    if (category == "last"){
        return ln->Search(val);
    }
    if (category == "birthday"){
        return bd->Search(val);
    }
    if (category == "origin"){
        return ori->Search(val);
    }
    if (category == "destination"){
        return des->Search(val);
    }
}