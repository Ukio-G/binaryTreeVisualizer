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
    int max_height;


    int x_max = 0;
    int x_min = 0;
    int x_proj = 0;


    Tree* findRoot();
    const Tree* getRoot() const;
    Tree* getRoot();
    void insert(int value);

    int getWidth();

private:
    Tree * root;

};

#endif
