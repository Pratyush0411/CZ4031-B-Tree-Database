//
// Created by praty on 17/9/2022.
//
#pragma once
class DuplicateNode{
    Block** blkPtr;
    Record** recordPtr;
};
class Node {
    bool isLeaf;
    int size;
    int *key; // array of keys
    Node **ptr;// array of node pointers
    Node *parent;


public:
    static int MAXSIZE;

    explicit Node(bool);

    void insertIntoLeafNode(int);

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
};


class BPTree {
    Node *rootNode;
private:
    Node *searchLeafNode(int);

    void createRootNode(Node *orgNode, Node *newNode, int smallestLB);

public:
    BPTree();

    void insert(int);

    int removeFromInternal(int, Node*, Node*);

    int remove(int);

    void display();

    void changeInternalNode(int smallestLB, Node *parent, Node *newLeaf);

    Node *splitAndReturnNewInternal(Node *orgInternal, int x, Node *newChild);

    Node *splitAndReturnNewLeaf(Node *orgNode, int x);

    int findSmallestLB(Node *cursor);

    Node *search(float x, bool flag, bool pointer);
};
