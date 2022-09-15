//
// Created by praty on 10/9/2022.
//
#include "vector"
#include "../entities/storage.h"
using namespace std;
class Node:Block {

public:
    vector<int> keys;

};

class leafNode: Node{
    Node* nextLeaf;
};


class intermediateNode: Node{
    vector<Node* > pointers;

};


class BPTree{

};