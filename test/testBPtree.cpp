//
// Created by praty on 16/9/2022.
//

#include "../entities/Btree.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <cstring>
//#include "../entities/BTree.cpp"
#include <typeinfo>

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

    for(int i = 0;i<17;i++){
        b->insert(i*1);
    }
    b->display();
    //b->remove(1);
    //b->display();
    int counter;
    counter = b->remove(0);
    //b->display();
    //b->remove(0);
    b->display();
    cout<<counter<<" nodes deleted"<<endl;

}
int main(){
    testInsertion();


    /*
    ifstream dataFile("C:/Users/colin/source/repos/cz4031-database-system-principles/data/data.tsv");

    vector<tuple<void *, uint>> dataset;
    bool flag = true;
    if (dataFile.is_open()){
        string line;
        while(getline(dataFile,line)){
            if(flag){
                flag = false;
                continue;
            }
        Record record;
        string tempLine;

        }
    }
*/
}
