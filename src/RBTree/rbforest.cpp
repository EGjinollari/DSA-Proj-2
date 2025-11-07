#include "rbforest.h"
#include "bdtree.h"
#include "idtree.h"
#include "fntree.h"
#include "lntree.h"
#include "idtree.h"
#include "oritree.h"
#include "destree.h"
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
    this->id->Delete(this->id->get_root(), id);
    this->fn->Delete(this->fn->get_root(), id);
    this->ln->Delete(this->ln->get_root(), id);
    this->bd->Delete(this->bd->get_root(), id);
    this->ori->Delete(this->ori->get_root(), id);
    this->des->Delete(this->des->get_root(), id);
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
    std::vector<Person*> vec;
    return vec;
}