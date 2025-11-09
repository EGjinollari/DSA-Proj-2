#include "tree.h"
#include "node.h"
Node* RBTree::get_root(){
    return this->root;
}

// Return root
RBTree::RBTree(Node* root){
    this->root = root;
}

// Recursive function to destroy a tree
void RBTree::Destructor_Helper(Node* root){
    if (!root){
        return;
    }

    Destructor_Helper(root->left);
    Destructor_Helper(root->right);
    delete root;
}

// Destructor wrapper
RBTree::~RBTree(){
    Destructor_Helper(root);
}

// Search wrappper that returns the results if any
std::vector<Person*> RBTree::Search(std::string &name)  {
    std::vector<Person*> vec;
    Search_Helper(root, vec, name); // All children overide this to search by their unique categories.
    return vec;
}


// Rebalance the RBtree after a deletion has occured.
void RBTree::DeleteBalance(Node* node) {
    // Handle double black after deletion
    while (node != root && (node == nullptr || node->color == 0)) {
        Node* p = node->parent;
        // Node is left child
        if (node == p->left) {
            Node* u = p->right;
            // Case 1: sib red
            if (u && u->color == 1) {
                u->flip_color();
                p->flip_color();
                LRotate(p);
                u = p->right;
            }
            // Case 1: black children / sib
            if ((!u->left || u->left->color == 0) && (!u->right || u->right->color == 0)) {
                if (u) {
                    u->flip_color();
                }
                node = p;
            } 
            else {
                // Handle if left / right child is red
                if (!u->right || u->right->color == 0) {
                    if (u->left) {
                        u->left->flip_color();
                    }
                    u->flip_color();
                    RRotate(u);
                    u = p->right;
                }
                u->color = p->color;
                p->color = 0;
                if (u->right) {
                    u->right->color = 0;
                }
                LRotate(p);
                node = root;
            }
        } 
        // Repeat this process on if the node is a right child
        else {
            Node* u = p->left;
            if (u && u->color == 1) {
                u->flip_color();
                p->flip_color();
                RRotate(p);
                u = p->left;
            }
            if ((!u->right || u->right->color == 0) && (!u->left || u->left->color == 0)) {
                if (u) {
                    u->flip_color();
                }
                node = p;
            } 
            else {
                if (!u->left || u->left->color == 0) {
                    if (u->right){ 
                        u->right->flip_color();
                    }
                    u->flip_color();
                    LRotate(u);
                    u = p->left;
                }
                u->color = p->color;
                p->color = 0;
                if (u->left){ 
                    u->left->color = 0;
                }
                RRotate(p);
                node = root;
            }
        }
    }
    if (node) {
        node->color = 0;
    }
}

// Balance after RBTree insertion
void RBTree::InsertBalance(Node* node){
    Node* p = nullptr;
    Node* gp = nullptr;
    // Red node cant have red parents
    while((node != root) && (node->color == 1) && (node->parent->color == 1)){
        p = node->parent;
        gp = p->parent;
        if (!gp){break;}
        // if parent is left child of grandparent
        if (p == gp->left){
            Node* u = gp->right;
            // If uncle is red recolor
            if (u != nullptr && u->color == 1){
                gp->flip_color();
                p->flip_color();
                u->flip_color();
                node = gp;
            }
            // If uncle is black rotate
            else{
                if (node == p->right) {
                    LRotate(p);
                    node = p;
                    p = node->parent;
                }
                RRotate(gp);
                int temp = p->color;
                p->color = gp->color;
                gp->color = temp;
                node = p;
            }
        }
        // Repeated process for if parent is right child of grandparent
        else{
            Node* u = gp->left;

            if (u != nullptr && u->color == 1){
                gp->flip_color();
                p->flip_color();
                u->flip_color();
                node = gp;
            }
            else{
                if (node == p->left){
                    RRotate(p);
                    node = p;
                    p = node->parent;
                }
                LRotate(gp);
                int temp = p->color;
                p->color = gp->color;
                gp->color = temp;
                node = p;
            }
        }
    }
    // Go to root then make it black
    while(node->parent != nullptr){
        node = node->parent;
    }
    root = node;
    root->color = 0;

}

// Delete a node from the red black tree. This wraps the recursive deletion and makes sure root is black
void RBTree::Delete(Person* target){
    Node* node = nullptr;
    bool color = 1;
    this->root = Delete_Helper(this->root, target, node, color);
    if (color == 0 && node){
        DeleteBalance(node);
    }
    if (this->root){
        this->root->color = 0;
    }
}

// Left rotate utility function
void RBTree::LRotate(Node* root){
    Node* right = root->right;
    root->right = right->left;
    if (right-> left != nullptr){
        right->left->parent = root;
    }
    right->parent = root->parent;
    if(root->parent == nullptr){
        this->root = right;
    }
    else if (root == root->parent->left){
        root->parent->left = right;
    }
    else{
        root->parent->right = right;
    }
    right->left = root;
    root->parent = right;

}

// Right rotate utility function
void RBTree::RRotate(Node* root){
    Node* left = root->left;
    root->left = left->right;
    if (left-> right != nullptr){
        left->right->parent = root;
    }
    left->parent = root->parent;
    if(root->parent == nullptr){
        this->root = left;
    }
    else if (root == root->parent->right){
        root->parent->right = left;
    }
    else{
        root->parent->left = left;
    }
    left->right = root;
    root->parent = left;
}
