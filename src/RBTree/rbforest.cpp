#include "rbforest.h"
#include "children_trees/bdtree.h"
#include "children_trees/idtree.h"
#include "children_trees/fntree.h"
#include "children_trees/lntree.h"
#include "children_trees/idtree.h"
#include "children_trees/oritree.h"
#include "children_trees/destree.h"

// Call all destructors
RBForest::~RBForest(){

    delete id;
    delete fn;
    delete ln;
    delete bd;
    delete ori;
    delete des;
}

// Construct all trees
RBForest::RBForest(){
    id = new IDRBTree();
    fn = new FNRBTree();
    ln = new LNRBTree();
    bd = new BDRBTree();
    ori = new ORIRBTree();
    des = new DESRBTree();
}


// Insert into all trees
void RBForest::Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest){

    Person* p = new Person(id, fn, ln, bday, origin, dest);
    
    this->id->Insert(p); 
    this->fn->Insert(p);
    this->ln->Insert(p);
    this->bd->Insert(p);
    this->ori->Insert(p);
    this->des->Insert(p);
}

// Delete from all trees
void RBForest::Delete(Person* p){

    this->id->Delete(p);
    this->fn->Delete(p);
    this->ln->Delete(p);
    this->bd->Delete(p);
    this->ori->Delete(p);
    this->des->Delete(p);

    delete p;
}

// Search speciifc tree based on category
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