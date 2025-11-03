#include <vector>
#include "tree.h"
#include "person.h"

class RBForest{
    private:
    RBTree* id;
    RBTree* fn;
    RBTree* ln;
    RBTree* bd;
    RBTree* ori;
    RBTree* des;

    public:
    std::vector<Person*> Search(std::string category, std::string val);
    void Delete(std::string id);
    void Insert(int id, std::string fn, std::string ln, int bday, std::string origin, std::string dest);
    RBForest();
    ~RBForest();

};