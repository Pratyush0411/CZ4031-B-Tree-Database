//
// Created by praty on 17/9/2022.
//
#pragma once

#include "vector"
#include "storage.cpp"

class DuplicateNode {
private:
    int N;
    int size;
public:
    int getSize() const;

    void setSize(int size);

private:
    int determineN(int);

    DuplicateNode *nextNode;
public:
    vector<Record *> recordArray;

    DuplicateNode();

    void pushRecord(Record *);

    void print();

    int getN() const;

    void setN(int n);

    DuplicateNode *getNextNode() const;

    void setNextNode(DuplicateNode *nextNode);

};

class Node {
    bool isLeaf;
    int size;
    int *key; // array of keys
    Node **ptr;// array of node pointers
    Node *parent;
    DuplicateNode **duplicateNodePtr;


public:
    void print();

    static int MAXSIZE;

    explicit Node(bool);

    bool checkAndInsertDuplicateIntoLeaf(int x, Record *rec);

    void insertIntoLeafNode(int, Record *);

    void insertIntoInternal(int, Node *);

    bool isLeaf1() const;

    void setSize(int size);

    int getKey(int i) const;

    void setKey(int, int);

    Node *getPtr(int i) const;

    void setPtr(int, Node *);

    DuplicateNode *getDuplicateNodePtr(int i) const;

    void setDuplicateNodePtr(int, DuplicateNode *);

    Node *getParent() const;

    void setParent(Node *parent);

    int getSize() const;

    bool hasCapacity();

    Node *returnNextNode(int x);

    void display();
};


class BPTree {
    Node *rootNode;
public:
    Node *getRootNode() const;

private:
    int determineN(int);
    Node *searchLeafNode(int);

    void createRootNode(Node *orgNode, Node *newNode, int smallestLB);

public:
    BPTree();

    void insert(int, Record *);

    void display();

    void changeInternalNode(int smallestLB, Node *parent, Node *newLeaf);

    Node *splitAndReturnNewInternal(Node *orgInternal, int x, Node *newChild);

    Node *splitAndReturnNewLeaf(Node *orgNode, int x, Record *);

    int findSmallestLB(Node *cursor);


};
