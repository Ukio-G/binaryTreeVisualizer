#ifndef ROTATIONS_HPP
#define ROTATIONS_HPP

#include "Tree.hpp"

Tree * findNodeByKey(Tree * node, int key);

void smallLeftRotate(Tree *&root, int key);

void smallRightRotate(Tree *&root, int key);

void bigLeftRotate(Tree *&root, int key);

void bigRightRotate(Tree *&root, int key);

#endif //ROTATIONS_HPP
