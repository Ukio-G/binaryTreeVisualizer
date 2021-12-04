#include <stdexcept>
#include "Tree.hpp"

Tree *Tree::findRoot() {
    if (parent == nullptr)
        return this;
    Tree * tmp_parent = parent;
    while (tmp_parent)
        if (tmp_parent->parent)
            tmp_parent = parent;
        else
            break;
    return tmp_parent;
}

Tree::Tree(Tree *parent, int value) : parent(parent), left(nullptr), right(nullptr), value(value), height(parent->height + 1) {
}


Tree::Tree(int value) : parent(nullptr), left(nullptr), right(nullptr), value(value), height(1) {

}

void Tree::calculateMaxHeightImpl(Tree * node, int * height_ptr) {
    if (node == nullptr)
        return;
    calculateMaxHeightImpl(node->left, height_ptr);

    *height_ptr = std::max(node->height, *height_ptr);

    calculateMaxHeightImpl(node->right, height_ptr);
}

int Tree::calculateMaxHeight() {
    Tree * root = findRoot();
    int result = root->height;
    calculateMaxHeightImpl(root, &result);
    return result;
}

void Tree::insert(int value) {
    if (this->value == value)
        throw std::runtime_error("Try to insert existing element in the tree");

    Tree * & appendNode = (this->value < value) ? right : left;
    if (appendNode == nullptr)
        appendNode = new Tree(this, value);
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
