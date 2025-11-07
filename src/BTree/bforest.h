#ifndef BFOREST_H
#define BFOREST_H

#include <vector>
#include <string>
#include "person.h"

class BDTree;
class IDTree;
class FNTree;
class LNTree;
class ORITree;
class DESTree;

class BForest {
private:
    IDTree* id;
    FNTree* fn;
    LNTree* ln;
    BDTree* bd;
    ORITree* ori;
    DESTree* des;

public:
    BForest();
    ~BForest();
    
    void Insert(int id, std::string fn, std::string ln, int bday, 
                std::string origin, std::string dest);
    void Delete(std::string id);
    std::vector<Person*> Search(std::string category, std::string val);
};

#endif