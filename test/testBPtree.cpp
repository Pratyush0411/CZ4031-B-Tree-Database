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

    for(int i = 0;i<13;i++){
        b->insert(i*4);
    }
    b->display();
    //change insertion to split 2-1
    //b->remove(4);
    //issue when removing from first node
    //b->remove(16);
    //update parent key for when removing from rightmost node
    b->remove(8);
    b->display();


}
int main(){
    testInsertion();

}
