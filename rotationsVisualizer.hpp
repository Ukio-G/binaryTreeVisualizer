#ifndef ROTATIONSVISUALIZER_HPP
#define ROTATIONSVISUALIZER_HPP

#include "Tree.hpp"

Tree * findNodeByKey(Tree * node, int key);

void smallLeftRotateKey(Tree *& root, int key);

void smallRightRotateKey(Tree *& root, int key);

void bigLeftRotateKey(Tree *& root, int key);

void bigRightRotateKey(Tree *& root, int key);

#endif
