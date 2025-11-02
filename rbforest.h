#include <vector>
#include "tree.h"

class RBForest{
    private:
    RBTree* id;
    RBTree* fn;
    RBTree* ln;
    RBTree* bd;
    RBTree* ori;
    RBTree* des;

    public:
    RBForest();
    ~RBForest();

};