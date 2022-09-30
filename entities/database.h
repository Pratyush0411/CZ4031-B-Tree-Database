//
// Created by praty on 11/9/2022.
//

#pragma once
#include "storage.h"
#include "datablock.h"
#include "vector"
#include <utility>  
#include<unordered_set>

using namespace std;

class Database{
private:
    unordered_set<int> freeBlocks;
    vector<DataBlock> blocksList;
    int MAXSIZE;
    int blockSize;
public:
    Database(int capacity, int blockSize);
    pair<DataBlock*,Record*> addRecord(Record record);
    void deleteRecordByNumvotes(int numVotes);
    int getNumBlocks();
    unsigned int getSize();
};

