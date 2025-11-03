#include <idtree.h>

IDRBTree::IDRBTree() : RBTree(nullptr){}

void IDRBTree::Search_Helper(Node* root, std::vector<Person*> &vec, std::string val){
    if (!root) {
        return;
    }
    if (root->get_data()->get_id() == val) {
        vec.push_back(root->get_data());
    }
    Search_Helper(root->left, vec, val);
    Search_Helper(root->right, vec, val);
}

Node* IDRBTree::Insert_Helper(Node* root, Person* p, std::string val){
    if (!root){
        Node* n = new Node(p);
        n->flip_color();
        return n;
    }
    if (stoi(root->get_data()->get_id()) < stoi(val)){
        Node* rChild = Insert_Helper(root->right, p, val);
        root->right = rChild;
        rChild->parent = root;
    }else{  
        Node* lChild = Insert_Helper(root->left, p, val);
        root->left = lChild;
        lChild->parent = root;
    } 
    return root;
}

Node* IDRBTree::Delete_Helper(Node* root, std::string target, Node*& successor, bool& color) {
    if (!root) return nullptr;

    std::string curr = root->get_data()->get_id();
    if (target < curr)
        root->left = Delete_Helper(root->left, target, successor, color);
    else if (target > curr)
        root->right = Delete_Helper(root->right, target, successor, color);
    else {
        color = root->color;
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        } else if (!root->left) {
           Node* temp = root->right;
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            temp->parent = root->parent;
            successor = temp;
            delete root;
            return temp;
        } else {
            Node* succ = root->right;
            while (succ->left) succ = succ->left;
            root->set_data(succ->get_data());
            root->right = Delete_Helper(root->right, succ->get_data()->get_id(), successor, color);
        }
    }
    return root;
}
