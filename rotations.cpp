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

void smallLeftRotate(Tree * root, int key) {
    auto a = findNodeByKey(root, key);
    auto parent = a->parent;

    auto direction = (parent->left == a) ? LeftDir : RightDir;

    /* Get subtrees */
    auto b = a->right; auto l = a->left;auto c = b->left; auto r = b->right;

    /* Unbinding connections */
    b->left = b->right = a->left = a->right = b->parent = a->parent = nullptr;
    if (l) l->parent = nullptr; if (c) c->parent = nullptr; if (r) r->parent = nullptr;

    /* Parent and child connections binding */
    a->left = l; a->right = c; if (l) l->parent = a; if (c) c->parent = a;
    b->left = a; b->right = r; if (r) r->parent = b;
    a->parent = b; b->parent = parent;
    if (direction == LeftDir) parent->left = b; else parent->right = b;

    /* Height correction */
    a->height++; b->height--; if (l) l->height++; if(r) r->height--;
}

void smallRightRotate(Tree * root, int key) {
    auto a = findNodeByKey(root, key);
    auto parent = a->parent;
    auto direction = (parent->left == a) ? LeftDir : RightDir;

    /* Get subtrees */
    auto b = a->left; auto l = b->left; auto c = b->right; auto r = a->right;

    /* Unbinding connections */
    b->left = b->right = a->left = a->right = nullptr;
    b->parent = a->parent = l->parent = c->parent = r->parent = nullptr;

    /* Parent binding */
    a->left = c; a->right = r; c->parent = r->parent = a;
    b->left = l; b->right = a; l->parent = a->parent = b;
    b->parent = parent;
    if (direction == LeftDir) parent->left = b; else parent->right = b;

    /* Height correction */
    a->height++; b->height--; l->height--; r->height++;
}

void bigLeftRotate(Tree * root, int key) {

}

void bigRightRotate(Tree * root, int key) {

}