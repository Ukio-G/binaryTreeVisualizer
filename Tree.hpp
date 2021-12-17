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
    
    Tree* find(int key);

    int getWidth();

    int calculateMaxHeight();

    void recursiveHeightUpdate();

    void correctHeight();

    int balanceFactor();

    bool balance();

    void recursiveBalance();

    Tree * remove(int key);

    Tree* findMinimum();
    Tree* findMaximum();

    void setMinimumAsNull();

private:
    static void calculateMaxHeightImpl(Tree *node, int *height);
    void setParentToThisNull();
    void setParentToThisToArg(Tree* new_node);

};

int nodesCount(Tree* root);
int distanceToRoot(Tree* node);

#endif
