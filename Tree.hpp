#ifndef TREE_HPP
#define TREE_HPP

class Tree  {
public:
    Tree(Tree *parent, int value);
    Tree(int value);
    Tree * left;
    Tree * parent;
    Tree * right;
    int value;
    int height;


    Tree* findRoot();
    void insert(int value);

    int getWidth();

    int calculateMaxHeight();

    void recursiveHeightUpdate();

    void correctHeight();

    int balanceFactor();

    bool balance();

    void recursiveBalance();

private:
    static void calculateMaxHeightImpl(Tree *node, int *height);


};

int nodesCount(Tree* root);
int distanceToRoot(Tree* node);

#endif
