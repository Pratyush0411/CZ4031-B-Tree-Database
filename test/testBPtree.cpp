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
#include "../entities/database.cpp"
#include "../entities/datablock.cpp"
#include "../entities/storage.cpp"
#include <typeinfo>
#include "../entities/storage.h"

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
    // testInsertion();

    BPTree* b = new BPTree();
    
    ifstream dataFile("C:/Users/colin/source/repos/cz4031-database-system-principles/data/data.tsv");

    Record* rec1 = new Record("t00000000",9.5,23);
    //Record* rec2 = new Record("t00000001",9.0,20);
    int DbSize = 100000000;
    int blockSize = 100;
    Database* db = new Database(DbSize, blockSize);

    // pair<DataBlock*, Record*> p1 = db->addRecord(*rec1);

    pair<DataBlock*, Record*> dataset1;
    // vector<tuple<void *, uint>> dataset;
    bool flag = true;
    if (dataFile.is_open()){
        string line;
        while(getline(dataFile,line)){
            if(flag){
                flag = false;
                continue;
            }
            
        Record* record;
        string tempLine;

        strcpy(record->tconst,line.substr(0,line.find('\t')).c_str());

        stringstream linestream(line);
        getline(linestream,tempLine, '\t');
        linestream >> record->avgRating >> record->numVotes;

        // cout << record->avgRating << '\n';
        // cout << record->numVotes << '\n';
        // cout << record->tconst << '\n';
        // pair<DataBlock*, Record*> dataRecord = db->addRecord();

        db->addRecord(*record);
        cout << db->getNumBlocks();
        // cout << db->getSize();
        // cout << db;

        
        cout << "1:" << db->getNumBlocks() << '\n';
        cout << "2:" << db->getSize() << '\n';
        }

    }
}
