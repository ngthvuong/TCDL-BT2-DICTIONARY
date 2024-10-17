#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include "Word.h"

using namespace std;

struct AVLNode
{
    WordEntry data;
    AVLNode *pLeft;
    AVLNode *pRight;
    int height;
};

class AVLTree
{
private:
    AVLNode *root;
    bool appendWordFlag;

    AVLNode *leftRotate(AVLNode *);
    AVLNode *rightRotate(AVLNode *);
    AVLNode *createNode(Word);
    AVLNode *appendNode(AVLNode *, Word);
    int getHeight(AVLNode *);
    int getBalance(AVLNode *);
    void release(AVLNode *);
    AVLNode *add(AVLNode *, Word);
    void show(AVLNode *);

public:
    AVLTree();

    bool addNode(Word);
    WordEntry search(string);
    void print();

    ~AVLTree();
};
#endif