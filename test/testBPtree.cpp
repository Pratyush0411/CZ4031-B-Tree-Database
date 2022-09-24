//
// Created by praty on 16/9/2022.
//

#include "../entities/Btree.cpp"

#include <cstring>

void testSplitLeaf(){
    BPTree* b = new BPTree();
    Node * a = new Node(true);
    a->insertIntoLeafNode(10);
    a->insertIntoLeafNode(12);
    a->insertIntoLeafNode(13);


    // testSplitAndReturnNewLeaf
    Node* c= b->splitAndReturnNewLeaf(a,9);
    a->display();
    c->display();
    a->getPtr(a->getSize())->display();

}

void testInsertion(){
    BPTree* b = new BPTree();

    for(int i = 0;i<4;i++){
        b->insert(i*4);
    }
    b->display();
    b->remove(8);
    b->display();

}
int main(){
    testInsertion();

}
