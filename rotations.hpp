#ifndef ROTATIONS_HPP
#define ROTATIONS_HPP

#include "Tree.hpp"

Tree * findNodeByKey(Tree * node, int key);

void smallLeftRotate(Tree *&root);

void smallRightRotate(Tree *&root);

void bigLeftRotate(Tree *&root);

void bigRightRotate(Tree *&root);


void smallLeftRotateKey(Tree *& root, int key);

void smallRightRotateKey(Tree *& root, int key);

void bigLeftRotateKey(Tree *& root, int key);

void bigRightRotateKey(Tree *& root, int key);

#endif //ROTATIONS_HPP
