#ifndef TREE_HPP
#define TREE_HPP

enum NodeDirectory {LeftDir, RightDir, NoneDir};

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
    Tree * remove(int key);

    /* Unused */
    void setMinimumAsNull();
    Tree* findMinimum();

    /* Public only with visualizer */
#ifdef VISUALIZER_TREE
    static void smallLeftRotate(Tree *& root);
    static void smallRightRotate(Tree *& root);
    static void bigLeftRotate(Tree *& root);
    static void bigRightRotate(Tree *& root);
    static void calculateMaxHeightImpl(Tree *node, int *height);
    int calculateMaxHeight();
    int getWidth();
    int balanceFactor();
#endif

private:
    bool balance();
    Tree* findMaximum();
    void setParentToThisNull();
    void setParentToThisToArg(Tree* new_node);

    void correctHeight();
    void recursiveHeightUpdate();
    void recursiveBalance();
    /* Used for visualize */

#ifndef VISUALIZER_TREE
    int balanceFactor();
    static void smallLeftRotate(Tree *& root);
    static void smallRightRotate(Tree *& root);
    static void bigLeftRotate(Tree *& root);
    static void bigRightRotate(Tree *& root);
#endif
};

int nodesCount(Tree* root);
int distanceToRoot(Tree* node);

#endif
