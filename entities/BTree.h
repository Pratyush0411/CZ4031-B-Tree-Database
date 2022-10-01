//
// Created by praty on 17/9/2022.
//
#include "../entities/datablock.h"
#include "../entities/datablock.cpp"
#pragma once
class Duplicates : private Node
{
public:
    vector<pair<DataBlock *, int>> recptrs;
    int key;
    Duplicates();
};
class Node
{
    bool isLeaf;
    int size;
    int *key;   // array of keys
    Node **ptr; // array of node pointers
    Node *parent;
    Duplicates **dptr;

public:
    static int MAXSIZE;

    explicit Node(bool);

    void insertIntoLeafNode(int, pair<DataBlock *, int> p1);

    void insertIntoInternal(int, Node *);

    bool isLeaf1() const;

    void setSize(int size);

    int getKey(int i) const;

    void setKey(int, int);

    Node *getPtr(int i) const;

    void setPtr(int, Node *);

    Node *getParent() const;

    void setParent(Node *parent);

    int getSize() const;

    bool hasCapacity();

    Node *returnNextNode(int x);

    void deleteKeyPtrNode();

    void display();

    Duplicates *Node::insertIntoDuplicates(int key, pair<DataBlock *, int> p1);
};

class BPTree
{
    Node *rootNode;

private:
    Node *searchLeafNode(int);

    void createRootNode(Node *orgNode, Node *newNode, int smallestLB);

public:
    BPTree();

    void insert(int, pair<DataBlock *, int>);

    int removeFromInternal(int, Node *, Node *);

    int remove(int);

    void display();

    void changeInternalNode(int smallestLB, Node *parent, Node *newLeaf);

    Node *splitAndReturnNewInternal(Node *orgInternal, int x, Node *newChild);

    Node *splitAndReturnNewLeaf(Node *orgNode, int x);

    int findSmallestLB(Node *cursor);

    Node *search(float x, bool flag, bool pointer);
};
