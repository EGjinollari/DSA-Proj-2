#include "bforest.h"
#include "bdtree.h"

class IDBTree : public BTree {
public:
    IDBTree(int degree = 3) : BTree(degree) {}
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override {
        bool unique = true;
        for (auto i : taken_ids) {
            if (i == id) {
                unique = false;
                break;
            }
        }
        if (unique) {
            Person* p = new Person(id, fn, ln, bday, origin, dest);
            insert(p, p->get_id());
            taken_ids.push_back(id);
        }
    }
    std::vector<Person*> Search(std::string val) override {
        std::vector<Person*> results;
        searchHelper(root, val, results);
        return results;
    }
    void Delete(std::string target) override {
        for (auto it = taken_ids.begin(); it != taken_ids.end(); ) {
            if (std::to_string(*it) == target) {
                it = taken_ids.erase(it);
            } else {
                ++it;
            }
        }
    }
};

class FNBTree : public BTree {
public:
    FNBTree(int degree = 3) : BTree(degree) {}
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override {
        bool unique = true;
        for (auto i : taken_ids) {
            if (i == id) {
                unique = false;
                break;
            }
        }
        if (unique) {
            Person* p = new Person(id, fn, ln, bday, origin, dest);
            insert(p, p->get_first());
            taken_ids.push_back(id);
        }
    }
    std::vector<Person*> Search(std::string val) override {
        std::vector<Person*> results;
        searchHelper(root, val, results);
        return results;
    }
    void Delete(std::string target) override {
    }
};

class LNBTree : public BTree {
public:
    LNBTree(int degree = 3) : BTree(degree) {}
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override {
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
    std::vector<Person*> Search(std::string val) override {
        std::vector<Person*> results;
        searchHelper(root, val, results);
        return results;
    }
    void Delete(std::string target) override {
    }
};

class ORIBTree : public BTree {
public:
    ORIBTree(int degree = 3) : BTree(degree) {}
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override {
        bool unique = true;
        for (auto i : taken_ids) {
            if (i == id) {
                unique = false;
                break;
            }
        }
        if (unique) {
            Person* p = new Person(id, fn, ln, bday, origin, dest);
            insert(p, p->get_origin());
            taken_ids.push_back(id);
        }
    }
    std::vector<Person*> Search(std::string val) override {
        std::vector<Person*> results;
        searchHelper(root, val, results);
        return results;
    }
    void Delete(std::string target) override {
    }
};

class DESBTree : public BTree {
public:
    DESBTree(int degree = 3) : BTree(degree) {}
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest) override {
        bool unique = true;
        for (auto i : taken_ids) {
            if (i == id) {
                unique = false;
                break;
            }
        }
        if (unique) {
            Person* p = new Person(id, fn, ln, bday, origin, dest);
            insert(p, p->get_destination());
            taken_ids.push_back(id);
        }
    }
    std::vector<Person*> Search(std::string val) override {
        std::vector<Person*> results;
        searchHelper(root, val, results);
        return results;
    }
    void Delete(std::string target) override {
    }
};

BForest::BForest() {
    id = new IDBTree();
    fn = new FNBTree();
    ln = new LNBTree();
    bd = new BDTree();
    ori = new ORIBTree();
    des = new DESBTree();
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
    this->id->Delete(id);
    this->fn->Delete(id);
    this->ln->Delete(id);
    this->bd->Delete(id);
    this->ori->Delete(id);
    this->des->Delete(id);
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