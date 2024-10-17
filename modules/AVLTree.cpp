#include "Word.h"
#include "AVLTree.h"
#include <iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;

AVLTree::AVLTree()
{
    root = nullptr;
    appendWordFlag = false;
}

int AVLTree::getHeight(AVLNode *node)
{
    if (!node)
    {
        return 0;
    }
    return node->height;
}
void AVLTree::updateHeight(AVLNode *node)
{
    node->height = 1 + max(getHeight(node->pLeft), getHeight(node->pRight));
}

AVLNode *AVLTree::createNode(Word word)
{
    WordEntry wordEntry = WordService::createWordEntry(word);
    AVLNode *newNode = new AVLNode();
    newNode->data = wordEntry;
    newNode->height = 1;
    newNode->pLeft = nullptr;
    newNode->pRight = nullptr;

    return newNode;
}
AVLNode *AVLTree::appendNode(AVLNode *node, Word word)
{
    node->data.items.push_back(word);
    return node;
}

int AVLTree::getBalance(AVLNode *node)
{
    return getHeight(node->pRight) - getHeight(node->pLeft);
}

AVLNode *AVLTree::rightRotate(AVLNode *node)
{
    AVLNode *x = node->pLeft;
    node->pLeft = x->pRight;
    x->pRight = node;

    updateHeight(node);
    updateHeight(x);

    return x;
}
AVLNode *AVLTree::leftRotate(AVLNode *node)
{

    AVLNode *x = node->pRight;
    node->pRight = x->pLeft;
    x->pLeft = node;

    updateHeight(node);
    updateHeight(x);

    return x;
}

AVLNode *AVLTree::add(AVLNode *node, Word word)
{
    if (!node)
    {
        node = createNode(word);
        return node;
    }

    if (WordService::compareKey(word.key, node->data.key) == 0)
    {
        appendNode(node, word);
        appendWordFlag = true;
        return node;
    }

    if (WordService::compareKey(word.key, node->data.key) < 0)
    {
        node->pLeft = add(node->pLeft, word);
    }
    else
    {
        node->pRight = add(node->pRight, word);
    }

    if (!appendWordFlag)
    {
        node->height = 1 + max(getHeight(node->pLeft), getHeight(node->pRight));

        int balance = getBalance(node);
        if (balance < -1)
        {
            int leftBalance = getBalance(node->pLeft);

            // Left Left
            if (leftBalance <= 0)
            {
                return rightRotate(node);
            }
            // Left Right
            else
            {
                node->pLeft = leftRotate(node->pLeft);
                return rightRotate(node);
            }
        }
        if (balance > 1)
        {
            int rightBalance = getBalance(node->pRight);
            // Right Right
            if (rightBalance >= 0)
            {
                return leftRotate(node);
            }
            // Right Left
            else
            {
                node->pRight = rightRotate(node->pRight);
                return leftRotate(node);
            }
        }
    }
    return node;
}
bool AVLTree::addNode(Word word)
{
    root = add(root, word);
    appendWordFlag = false;
    return 1;
}

AVLNode *AVLTree::findNode(AVLNode *node, string key)
{
    if (!node)
    {
        return NULL;
    }

    if (node->data.key == key)
    {
        return node;
    }

    int compareResult = WordService::compareKey(key, node->data.key);
    if (compareResult < 0)
    {
        return findNode(node->pLeft, key);
    }
    else
    {
        return findNode(node->pRight, key);
    }
}
WordEntry *AVLTree::search(string keyword)
{
    string key = WordService::getKey(keyword);
    AVLNode *result = findNode(root, key);
    WordEntry *wordEntry = &result->data;
    return wordEntry;
}

void AVLTree::show(AVLNode *node)
{
    if (!node)
    {
        return;
    }
    show(node->pLeft);
    show(node->pRight);
    cout << "Key: \t" << node->data.key << "\t height: \t" << node->height << endl;
    for (Word &word : node->data.items)
    {
        cout << word.translatedMeaning << endl;
    }
    return;
}
void AVLTree::print()
{
    cout << "Print Dictionary B Tree: " << endl;
    show(root);
}

void AVLTree::release(AVLNode *node)
{
    if (!node)
    {
        return;
    }

    release(node->pLeft);
    release(node->pRight);

    delete node;
}
AVLTree::~AVLTree()
{
    release(root);
}