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
    int balance = getHeight(node->pRight) - getHeight(node->pLeft);
    return (balance < -1) ? -1 : (balance > 1) ? 1
                                               : 0;
}

AVLNode *AVLTree::rightRotate(AVLNode *node)
{
    if (node->pLeft)
    {
        cout << "right co node->pLeft" << endl;
    }
    else
    {
        cout << "right khong co node->pLeft" << endl;
    }

    AVLNode *x = node->pLeft;
    cout << "test run1" << endl;

    node->pLeft = x->pRight;
    cout << "test run2" << endl;

    x->pRight = node;
    cout << "test run2" << endl;

    node->height = 1 + max(getHeight(node->pLeft), getHeight(node->pRight));
    x->height = 1 + max(getHeight(x->pLeft), getHeight(x->pRight));

    return x;
}

AVLNode *AVLTree::leftRotate(AVLNode *node)
{

    AVLNode *x = node->pRight;
    node->pRight = x->pLeft;
    x->pLeft = node;

    node->height = 1 + max(getHeight(node->pLeft), getHeight(node->pRight));
    x->height = 1 + max(getHeight(x->pLeft), getHeight(x->pRight));

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
        int balanceLeft = getBalance(node->pLeft);
        int balanceRight = getBalance(node->pRight);

        // Left Left
        if (balance < 0 && WordService::compareKey(word.key, node->data.key) < 0)
        {
            cout << "left left" << endl;
            cout << "left height: " << getHeight(node->pLeft) << endl;
            cout << "right height: " << getHeight(node->pRight) << endl;
            cout << "===========" << endl;
            return rightRotate(node);
        }
        // Right Right
        if (balance > 0 && WordService::compareKey(word.key, node->data.key) > 0)
        {
            cout << "left left" << endl;
            cout << "left height: " << getHeight(node->pLeft) << endl;
            cout << "right height: " << getHeight(node->pRight) << endl;
            cout << "===========" << endl;

            return leftRotate(node);
        }
        // Left Right
        if (balance < 0 && WordService::compareKey(word.key, node->data.key) > 0)
        {
            cout << "Left Right" << endl;
            cout << "left height: " << getHeight(node->pLeft) << endl;
            cout << "right height: " << getHeight(node->pRight) << endl;
            cout << "===========" << endl;
            cout << node->data.key << endl;

            node->pLeft = leftRotate(node->pLeft);
            cout << "Left Right END" << endl;

            return rightRotate(node);
        }
        // Right Left
        if (balance > 0 && WordService::compareKey(word.key, node->data.key) < 0)
        {
            cout << "Right Left" << endl;
            cout << "left height: " << getHeight(node->pLeft) << endl;
            cout << "right height: " << getHeight(node->pRight) << endl;
            cout << "===========" << endl;

            // cout << "word key: " << word.key << endl;
            // cout << "node->data.key: " << node->data.key << endl;
            // cout << "node->pLeft->data.key: " << node->pLeft->data.key << endl;

            // cout << "node->pLeft->pLeft->data.key: " << node->pLeft->pLeft->data.key << endl;

            cout << "Right Left" << endl;
            cout << node->data.key << endl;
            cout << "Left" << getHeight(node->pLeft) << endl;
            cout << "Right" << getHeight(node->pRight) << endl;

            if (node->pRight)
            {
                cout << "Co right" << endl;
            }
            else
            {
                cout << "Ko right" << endl;
            }

            node->pRight = rightRotate(node->pRight);
            return leftRotate(node);
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
    cout << "print dictionary" << endl;
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