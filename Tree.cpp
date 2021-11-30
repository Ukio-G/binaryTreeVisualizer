#include <stdexcept>
#include "Tree.hpp"

Tree *Tree::findRoot() {
    Tree * tmp_parent = parent;
    while (tmp_parent)
        if (tmp_parent->parent)
            tmp_parent = parent;
        else
            break;
    return tmp_parent;
}

Tree::Tree(Tree *parent, int value) : parent(parent), root(parent->root), left(nullptr), right(nullptr), value(value), height(parent->height + 1) {
}

const Tree *Tree::getRoot() const {
    return root;
}

Tree *Tree::getRoot() {
    return root;
}

Tree::Tree(int value) : parent(nullptr), root(this), left(nullptr), right(nullptr), value(value), height(1), max_height(1) {

}

void Tree::insert(int value) {
    if (this->value == value)
        throw std::runtime_error("Try to insert existing element in the tree");

    Tree * & appendNode = (this->value < value) ? right : left;
    if (appendNode == nullptr) {
        appendNode = new Tree(this, value);
        appendNode->x_proj = x_proj + ((this->value < value) ? 1 : -1);

        auto root_ptr = appendNode->getRoot();
        root_ptr->max_height = std::max(root_ptr->max_height, appendNode->height);
        root_ptr->x_max = std::max(appendNode->x_proj, root_ptr->x_max);
        root_ptr->x_min = std::min(appendNode->x_proj, root_ptr->x_min);
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
