#include <vector>
#include "tree.h"
#include "../person.h"

class RBForest{
    private:
    // Store a Red Black Tree for each category
    RBTree* id;
    RBTree* fn;
    RBTree* ln;
    RBTree* bd;
    RBTree* ori;
    RBTree* des;

    public:
    // Wrapper functions that call search / insert / delete on all trees at once
    std::vector<Person*> Search(std::string category, std::string val);
    void Delete(Person* p);
    void Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest);
    RBForest();
    ~RBForest();

};