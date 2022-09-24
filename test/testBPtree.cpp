//
// Created by praty on 16/9/2022.
//

#include "../entities/Btree.cpp"

#include <cstring>

void printDuplicateNode(Node* leaf){
    for (int i = 0; i<leaf->getSize();i++){
        cout<< "B Tree Key "<< leaf->getKey(i)<<" Duplicate Node"<<endl;
        leaf->getDuplicateNodePtr(i)->print();
        cout<<"\n";
    }
}

void testInsertion(){
    BPTree* b = new BPTree();
    for(int i = 0;i<1000;i++){
        //cout<<"Iteration "<<i<<endl;
        for (int j = 1; j<=300;j++){
            Record * dummy = new Record("",10,i*j);
            b->insert(i*j,dummy);
        }
    }
    Node *cursor = b->getRootNode();
    while (!cursor->isLeaf1()) {
        cursor = cursor->getPtr(0);
    }

//    while(cursor != NULL){
//        printDuplicateNode(cursor);
//        cursor = cursor->getPtr(cursor->getSize());
//    }
    b->display();
    b->search(299835);

}

void testInsertionFromDataset(){

}


int main(){
    testInsertion();

}