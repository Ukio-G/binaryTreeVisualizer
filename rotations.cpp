#include "rotations.hpp"


Tree * findNodeByKey(Tree * node, int key) {
    if (node == nullptr)
        return nullptr;
    if (node->value == key)
        return node;

    Tree * left_subtree = findNodeByKey(node->left, key);
    if (left_subtree)
        return left_subtree;

    return findNodeByKey(node->right, key);
}

enum NodeDirectory {LeftDir, RightDir, NoneDir};

void smallLeftRotate(Tree *& root) {
    auto a = root; //findNodeByKey(root, key);
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

void smallRightRotate(Tree *& root) {
    // auto a = findNodeByKey(root, key);
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

void bigLeftRotate(Tree *& root) {
    smallRightRotate(root->right);
    smallLeftRotate(root);
    root->recursiveHeightUpdate();
}

void bigRightRotate(Tree *& root) {
    smallLeftRotate(root->left);
    smallRightRotate(root);
    root->recursiveHeightUpdate();
}

void smallLeftRotateKey(Tree *& root, int key) {
    if (root->value == key)
        smallLeftRotate(root);
    else {
        Tree * node = findNodeByKey(root, key);
        smallLeftRotate(node);
    }
}

void smallRightRotateKey(Tree *& root, int key) {
    if (root->value == key)
        smallRightRotate(root);
    else {
        Tree * node = findNodeByKey(root, key);
        smallRightRotate(node);
    }
}

void bigLeftRotateKey(Tree *& root, int key) {
    if (root->value == key) {
        bigLeftRotate(root);
    } else {
        Tree * node = findNodeByKey(root, key);
        bigLeftRotate(node);
    }
}

void bigRightRotateKey(Tree *& root, int key) {
    if (root->value == key) {
        bigRightRotate(root);
    } else {
        Tree * node = findNodeByKey(root, key);
        bigRightRotate(node);
    }
}