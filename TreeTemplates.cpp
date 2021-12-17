#include "TreeTemplates.hpp"


Tree* bigLeftRotateTree() {
    Tree *t = new Tree(50);
    t->insert(25);
    t->insert(100);
    t->insert(200);
    t->insert(75);
    t->insert(67);
    t->insert(88);
    return t;
}


Tree* bigRightRotateTree() {
    Tree *t = new Tree(50);

    /* Right subtree */
    t->insert(100);
    

    /* Left subtree */
    t->insert(25); t->insert(11); t->insert(37); t->insert(30); t->insert(42);


    return t->findRoot();
}


Tree* heightCorrectionTree() {
    Tree *t = new Tree(50);

    /* Right subtree */
    t->insert(100);
    

    /* Left subtree */
    t->insert(25); t->insert(11); t->insert(37); t->insert(30); t->insert(42); t->insert(200);

    bigRightRotateKey(t, 50);

    t->insert(400);

    return t;
}

Tree* simpleTree() {
    Tree *t = new Tree(100);
    t->insert(50);
    t->insert(200);
    t->insert(400);
    t->insert(800);
    t->insert(25);

    return t;
}

Tree * twoNodesTree() {
    Tree *t = new Tree(100);
    t->insert(50);
    return t;
}

Tree *complicatedBalanceTree() {
    Tree *t = new Tree(100);
    t->insert(50);
    t->insert(200);
    t->insert(400);
    t->insert(800);
    t->insert(25);
    t->insert(12);
    t->insert(10);
    t->insert(37);
    t->insert(30);

    return t;
}

