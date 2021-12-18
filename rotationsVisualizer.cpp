#include "rotationsVisualizer.hpp"

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

void smallLeftRotateKey(Tree *& root, int key) {
    if (root->value == key)
        Tree::smallLeftRotate(root);
    else {
        Tree * node = findNodeByKey(root, key);
        Tree::smallLeftRotate(node);
    }
}

void smallRightRotateKey(Tree *& root, int key) {
    if (root->value == key)
        Tree::smallRightRotate(root);
    else {
        Tree * node = findNodeByKey(root, key);
        Tree::smallRightRotate(node);
    }
}

void bigLeftRotateKey(Tree *& root, int key) {
    if (root->value == key) {
        Tree::bigLeftRotate(root);
    } else {
        Tree * node = findNodeByKey(root, key);
        Tree::bigLeftRotate(node);
    }
}

void bigRightRotateKey(Tree *& root, int key) {
    if (root->value == key) {
        Tree::bigRightRotate(root);
    } else {
        Tree * node = findNodeByKey(root, key);
        Tree::bigRightRotate(node);
    }
}
