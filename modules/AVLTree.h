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

    int getHeight(AVLNode *);
    void updateHeight(AVLNode *);

    AVLNode *createNode(Word);
    AVLNode *appendNode(AVLNode *, Word);

    AVLNode *leftRotate(AVLNode *);
    AVLNode *rightRotate(AVLNode *);

    int getBalance(AVLNode *);

    AVLNode *add(AVLNode *, Word);
    AVLNode *findNode(AVLNode *, string);
    void show(AVLNode *);

    void release(AVLNode *);

public:
    AVLTree();

    bool addNode(Word);
    
    WordEntry *search(string);
    void print();

    ~AVLTree();
};
#endif