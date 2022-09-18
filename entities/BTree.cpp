//
// Created by praty on 10/9/2022.
//
#include "vector"
#include <queue>
#include "../entities/storage.h"
#include "BTree.h"

using namespace std;


int Node::MAXSIZE = 3;

Node::Node(bool isLeaf) {
    this->isLeaf = isLeaf;
    key = new int[MAXSIZE];
    ptr = new Node *[MAXSIZE + 1];
    parent = NULL;
    size = 0;
}

BPTree::BPTree() {
    this->rootNode = NULL;
}

bool Node::hasCapacity() {
    if (this->size < MAXSIZE) {
        return true;
    } else
        return false;
}

void Node::insertIntoLeafNode(int x) {
    if (this->size < MAXSIZE) {
        cout << "Inserting into the leaf node" << endl;
        int i = 0;
        while (x > this->key[i] && i < this->size)
            i++;
        for (int j = this->size; j > i; j--) {
            this->key[j] = this->key[j - 1];
        }
        this->key[i] = x;
        this->size++;
        this->ptr[this->size] = this->ptr[this->size - 1];
        this->ptr[this->size - 1] = NULL;
    }
}

void Node::insertIntoInternal(int x, Node *child) {
    if (this->size < MAXSIZE) {
        cout << "Inserting into the internal node" << endl;

        int i = 0;
        while (x > this->key[i] && i < this->size)
            i++;
        for (int j = this->size; j > i; j--) {
            this->key[j] = this->key[j - 1];
        }
        for (int j = this->size + 1; j > i + 1; j--) {
            this->ptr[j] = this->ptr[j - 1];
        }
        this->key[i] = x;
        this->size++;
        this->ptr[i + 1] = child;
    }
}

bool Node::isLeaf1() const {
    return isLeaf;
}

void Node::setSize(int size) {
    this->size = size;
}


int Node::getKey(int i) const {
    return this->key[i];
}

void Node::setKey(int i, int x) {
    this->key[i] = x;
}

Node *Node::getPtr(int i) const {
    return this->ptr[i];
}

void Node::setPtr(int i, Node *ptr) {
    this->ptr[i] = ptr;
}

Node *Node::getParent() const {
    return parent;
}

void Node::setParent(Node *parent) {
    this->parent = parent;
}

int Node::getSize() const {
    return this->size;
}

Node *Node::returnNextNode(int x) {
    if (!this->isLeaf) {
        for (int i = 0; i < this->size; i++) {
            if (x < this->key[i]) {
                return this->ptr[i];
            }
            if (i == this->size - 1) {
                return this->ptr[i + 1];
            }
        }
    }
}

void Node::display() {
    for (int i = 0; i < this->getSize(); i++) {
        cout << this->getKey(i) << " ";
    }
    cout<<"\t";
}

Node *BPTree::searchLeafNode(int x) {
    Node *cursor = this->rootNode;
    while (!cursor->isLeaf1()) {
        cursor = cursor->returnNextNode(x);
    }
    return cursor;
}

Node *BPTree::splitAndReturnNewLeaf(Node *orgNode, int x) {
    Node *newNode = new Node(true);
    int virtualNode[Node::MAXSIZE + 1];

    for (int i = 0; i < Node::MAXSIZE; i++) {
        virtualNode[i] = orgNode->getKey(i);
    }
    int i = 0;
    while (x > virtualNode[i] && i < Node::MAXSIZE)
        i++;
    for (int j = Node::MAXSIZE + 1; j > i; j--) {
        virtualNode[j] = virtualNode[j - 1];
    }
    // inserting x if Node was of size MAX+1
    virtualNode[i] = x;
//    for (int j =0; j <= Node::MAXSIZE; j++)
//        cout << virtualNode[j]<<"\t";
//    cout<<"\n";
    orgNode->setSize((Node::MAXSIZE + 1) / 2);
    newNode->setSize((Node::MAXSIZE + 1) - orgNode->getSize());

    // resetting pointers
    orgNode->setPtr(orgNode->getSize(), newNode);
    newNode->setPtr(newNode->getSize(), orgNode->getPtr(Node::MAXSIZE));
    orgNode->setPtr(Node::MAXSIZE, NULL);

    // changing original leaf keys
    for (i = 0; i < orgNode->getSize(); i++) {
        orgNode->setKey(i, virtualNode[i]);
    }

    int j;
    // changing keys in the new leaf
    for (i = 0, j = orgNode->getSize(); i < newNode->getSize(); i++, j++) {
        newNode->setKey(i, virtualNode[j]);
    }

    return newNode;
}

Node *BPTree::splitAndReturnNewInternal(Node *orgInternal, int x, Node *newChild) {
    Node *newInternal = new Node(false);
    int MAX = Node::MAXSIZE;
    int virtualKey[MAX + 1];
    Node *virtualPointer[MAX + 2];
    for (int i = 0; i < MAX; i++) {
        virtualKey[i] = orgInternal->getKey(i);
    }
    for (int i = 0; i < MAX + 1; i++) {
        virtualPointer[i] = orgInternal->getPtr(i);
    }
    int i, j;
    for (i = 0; i < MAX; i++) {
        if (x < virtualKey[i])
            break;
    }
    for (int j = MAX + 1; j > i; j--) {
        virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
        virtualPointer[j] = virtualPointer[j - 1];
    }
    virtualPointer[i + 1] = newChild;
    orgInternal->setSize((MAX / 2));
    newInternal->setSize((MAX) - orgInternal->getSize());

    // orgInternal
    for (i = 0; i < orgInternal->getSize()+1; i++) {
        orgInternal->setKey(i, virtualKey[i]);
    }

    for (i = 0; i < orgInternal->getSize() + 1; i++) {
        orgInternal->setPtr(i, virtualPointer[i]);
    }

    // skipping one key
    j = orgInternal->getSize() + 1;
    for (i = 0; i < newInternal->getSize(); i++) {
        newInternal->setKey(i, virtualKey[j]);
        j++;
    }

    j = orgInternal->getSize() + 1;
    for (i = 0; i < newInternal->getSize() + 1; i++) {
        newInternal->setPtr(i, virtualPointer[j]);
        j++;
    }

    return newInternal;


}

void BPTree::createRootNode(Node *orgNode, Node *newNode, int smallestLB) {

    Node *newRoot = new Node(false);

    newRoot->setKey(0, smallestLB);
    newRoot->setPtr(0, orgNode);
    newRoot->setPtr(1, newNode);
    newRoot->setSize(1);
    orgNode->setParent(newRoot);
    newNode->setParent(newRoot);
    this->rootNode = newRoot;

}

int BPTree::findSmallestLB(Node* startNode){
    Node* cursor = startNode;
    while (!cursor->isLeaf1()) {
        cursor = cursor->getPtr(0);
    }
    return cursor->getKey(0);

}
void BPTree::changeInternalNode(int smallestLB, Node *parent, Node *newChild) {
    if (parent->hasCapacity()) {
        parent->insertIntoInternal(smallestLB, newChild);
        newChild->setParent(parent);
    } else {
        Node *newInternal = this->splitAndReturnNewInternal(parent, smallestLB, newChild);
        newChild->setParent(parent);
        for (int i = 0; i < newInternal->getSize() + 1; i++) {
            Node *child = newInternal->getPtr(i);
            if (child == newChild) {
                newChild->setParent(newInternal);
                break;
            }
        }
        //int smallestLB = parent->getKey(parent->getSize());
        int smallestLB = this->findSmallestLB(newInternal);
        if (this->rootNode == parent) {
            // smallestLb here is a big brain strat to remember
            // we retrieve the node which was skipped while splitting internal nodes
            this->createRootNode(parent, newInternal, smallestLB);

        } else {
            this->changeInternalNode(smallestLB, parent->getParent(), newInternal);
        }

    }
}

void BPTree::insert(int x) {

    if (this->rootNode == NULL) {
        this->rootNode = new Node(true);
        this->rootNode->insertIntoLeafNode(x);
    } else {
        // searching for leaf
        Node *leafNode = this->searchLeafNode(x);

        // if leaf has capacity then add to leaf
        if (leafNode->hasCapacity())
            leafNode->insertIntoLeafNode(x);
        else {
            cout<<"Splitting leaf node for "<< x<< endl;
            Node *newLeaf = this->splitAndReturnNewLeaf(leafNode, x);
            if (leafNode->getParent() == NULL) {
                // create new root
                this->createRootNode(leafNode, newLeaf, newLeaf->getKey(0));
            } else {
                this->changeInternalNode(newLeaf->getKey(0), leafNode->getParent(), newLeaf);
            }
        }

    }

}

void BPTree::display() {
//    if (cursor != NULL) {
//        for (int i = 0; i < cursor->getSize(); i++) {
//            cout << cursor->getKey(i) << " ";
//        }
//        cout << "\n";
//        if (cursor->isLeaf1() != true) {
//            for (int i = 0; i < cursor->getSize() + 1; i++) {
//                display(cursor->getPtr(i));
//            }
//        }
//    }

// BFS printing the tree

    vector<Node *> q;
    q.push_back(rootNode);
    int level = 0;
    while (!q.empty()) {

        cout<<"Level "<<level<<":"<<" ";
        vector<Node*> cpy;
        for (Node *node: q) {
            node->display();
            cpy.push_back(node);
        }
        q.clear();
        for (Node* node:cpy){
            if (!node->isLeaf1()){
                for (int i = 0; i < node->getSize() + 1; i++) {
                    q.push_back(node->getPtr(i));
                }
            }
        }
        level ++;
        cout << "\n";
    }


}


