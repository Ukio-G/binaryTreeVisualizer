#include <stdexcept>
#include "Tree.hpp"
#include "rotationsVisualizer.hpp"

Tree *Tree::findRoot() {
    if (parent == nullptr)
        return this;
    Tree * tmp_parent = parent;
    while (tmp_parent)
        if (tmp_parent->parent)
            tmp_parent = tmp_parent->parent;
        else
            break;
    return tmp_parent;
}

Tree::Tree(Tree *parent, int value) : parent(parent), left(nullptr), right(nullptr), value(value), height(1) { }

Tree::Tree(int value) : parent(nullptr), left(nullptr), right(nullptr), value(value), height(1) { }

void Tree::calculateMaxHeightImpl(Tree * node, int * height_ptr) {
    if (node == nullptr)
        return;
    calculateMaxHeightImpl(node->left, height_ptr);

    *height_ptr = std::max(distanceToRoot(node), *height_ptr);

    calculateMaxHeightImpl(node->right, height_ptr);
}

int Tree::calculateMaxHeight() {
    Tree * root = findRoot();
    int result = (root != nullptr);
    calculateMaxHeightImpl(root, &result);
    return result;
}

void Tree::recursiveHeightUpdate() {
    Tree *parent_ = parent;
    correctHeight();
    while (parent_) {
        parent_->correctHeight();
        parent_ = parent_->parent;
    }
}

int Tree::balanceFactor() {
    int left_height = (left) ? left->height : 0;
    int right_height = (right) ? right->height : 0;
    return right_height - left_height;
}

void Tree::correctHeight() {
    auto left_height = (left) ? left->height : 0;
    auto right_height = (right) ? right->height : 0;
    height = std::max(right_height, left_height) + 1;
}

void Tree::insert(int value) {
    if (this->value == value)
        throw std::runtime_error("Try to insert existing element in the tree");

    Tree * & appendNode = (this->value < value) ? right : left;
    if (appendNode == nullptr) {
        appendNode = new Tree(this, value);
        appendNode->recursiveHeightUpdate();
        appendNode->recursiveBalance();
    }
    else
        appendNode->insert(value);
}

int Tree::getWidth() {
    int result = 1;
    Tree *tmp = left;
    while (tmp) {
        result++;
        tmp = tmp->left;
    }
    tmp = right;
    while (tmp) {
        result++;
        tmp = tmp->right;
    }
    return result;
}

bool Tree::balance() {
    Tree * node = this;
    if (balanceFactor() == 2) {
        if( right && right->balanceFactor() < 0 )
            bigLeftRotate(node);
        else
            smallLeftRotate(node);
        return true;
    } else if (balanceFactor() == -2) {
        if( left && left->balanceFactor() > 0 )
            bigRightRotate(node);
        else
            smallRightRotate(node);
        return true;
    }
    return false;
}

void Tree::recursiveBalance() {
    Tree * parent_ = parent;
    balance();
    while (parent_) {
        if (parent_->balance())
            return;
        parent_ = parent_->parent;
    }
}

Tree* Tree::find(int key) {
    if (value == key)
        return this;

    if (left && left->find(key))
        return left->find(key);

    if (right && right->find(key))
        return right->find(key);

    return 0;
}

void Tree::setMinimumAsNull() {
    Tree * min_node = left;
    while (min_node)
    {
        if (min_node->left)
            min_node = min_node->left;
        else 
            break;
    }
    Tree * parent_min = min_node->parent;
    parent_min->left = parent_min->right;
    parent_min->recursiveBalance();
}


Tree* Tree::findMinimum() {
    return (left) ? left->findMinimum() : this;
}

Tree* Tree::findMaximum() {
    return (right) ? right->findMaximum() : this;   
}

void Tree::setParentToThisNull() {
    if (parent) {
        if (parent->left == this)
            parent->left = 0;
        else if (parent->right == this)
            parent->right = 0;
    }
}

void Tree::setParentToThisToArg(Tree* new_node) {
    if (parent) {
        if (parent->left == this)
            parent->left = new_node;
        else if (parent->right == this)
            parent->right = new_node;
    }
}

Tree * Tree::remove(int key) {
    Tree* delete_node = find(key);
    if (!delete_node)
        return findRoot();
    Tree* delete_parent = delete_node->parent;


    /* Just leaf */
    if (delete_node->left == 0 && delete_node->right == 0) {
        delete_node->setParentToThisNull();
        if (delete_parent) {
            delete_parent->recursiveHeightUpdate();
            delete_parent->recursiveBalance();
        }
        delete delete_node; /* Possible 'delete this' ? */
        return delete_parent;
    }

    /* No left subtree => only one node in right subtree available */
    if (delete_node->left == 0) {
        delete_node->setParentToThisToArg(delete_node->right);
        delete_node->right->parent = delete_parent;
        if (delete_parent) {
            delete_parent->recursiveHeightUpdate();
            delete_parent->recursiveBalance();
        }
        Tree * result = delete_node->right;
        delete delete_node;
        return result;
    }

    /* Find maximum node in left subtree and make it new root of subtree (instead of deleted node) */

    Tree* new_node = delete_node->left->findMaximum();
    Tree* new_node_parent = new_node->parent;
    new_node->setParentToThisToArg(new_node->left);
    if(new_node->left)
        new_node->left->parent = new_node->parent;
    delete_node->setParentToThisToArg(new_node);
    new_node->parent = delete_parent;
    new_node->left = delete_node->left; new_node->right = delete_node->right;
    
    if (delete_node->left) delete_node->left->parent = new_node;
    if (delete_node->right) delete_node->right->parent = new_node;

    delete delete_node;

    if (delete_parent) {
        Tree *balance_node = (new_node_parent == delete_node) ? new_node : new_node_parent;
        balance_node->recursiveHeightUpdate();
        balance_node->balance();
        return delete_parent;
    }
    return new_node;
}

void nodesCountImpl(Tree* root, int * counter) {
    if (root == nullptr)
        return;
    nodesCountImpl(root->left, counter);
    (*counter)++;
    nodesCountImpl(root->right, counter);
}

int nodesCount(Tree* root) {
    int result = 0;
    nodesCountImpl(root, &result);
    return result;
}

int distanceToRoot(Tree* node) {
    int distance = 1;
    Tree *parent = node->parent;
    while (parent) {
        distance++;
        parent = parent->parent;
    }
    return distance;
}


void Tree::smallLeftRotate(Tree *& root) {
    auto a = root;
    auto parent = a->parent;

    auto direction = (parent) ? (parent->left == a) ? LeftDir : RightDir : NoneDir;

    /* Get subtrees */
    auto b = a->right; auto l = a->left; auto c = b->left; auto r = b->right;

    /* Unbinding connections */
    b->left = b->right = a->left = a->right = b->parent = a->parent = nullptr;
    if (l) l->parent = nullptr; if (c) c->parent = nullptr; if (r) r->parent = nullptr;

    /* Parent and child connections binding */
    a->left = l; a->right = c; if (l) l->parent = a; if (c) c->parent = a;
    b->left = a; b->right = r; if (r) r->parent = b;
    a->parent = b;
    if (direction != NoneDir)
        b->parent = parent;
    else {  // Change root
        b->parent = nullptr;
        root = b;
    }
    if (direction == LeftDir) parent->left = b; else if (direction == RightDir) parent->right = b;
    /* Height correction */
    a->correctHeight();
    b->correctHeight();
    b->recursiveHeightUpdate();
}

void Tree::smallRightRotate(Tree *& root) {
    auto a = root;
    auto parent = a->parent;

    auto direction = (parent) ? (parent->left == a) ? LeftDir : RightDir : NoneDir;

    /* Get subtrees */
    auto b = a->left; auto l = b->left; auto c = b->right; auto r = a->right;

    /* Unbinding connections */
    b->left = b->right = a->left = a->right = b->parent = a->parent = nullptr;
    if (l) l->parent = nullptr; if (c) c->parent = nullptr; if (r) r->parent = nullptr;

    /* Parent and child connections binding */
    a->left = c; a->right = r; if (r) r->parent = a; if (c) c->parent = a;  /* node A connections */
    b->left = l; b->right = a; if (l) l->parent = b;                        /* node B connections */
    a->parent = b;
    if (direction != NoneDir)
        b->parent = parent;
    else {  // Change root
        b->parent = nullptr;
        root = b;
    }
    if (direction == LeftDir) parent->left = b; else if (direction == RightDir) parent->right = b;
    /* Height correction */
    a->correctHeight();
    b->correctHeight();
    b->recursiveHeightUpdate();
}

void Tree::bigLeftRotate(Tree *& root) {
    smallRightRotate(root->right);
    smallLeftRotate(root);
    root->recursiveHeightUpdate();
}

void Tree::bigRightRotate(Tree *& root) {
    smallLeftRotate(root->left);
    smallRightRotate(root);
    root->recursiveHeightUpdate();
}


