//
// Created by praty on 11/9/2022.
//

#pragma once
#include "storage.h"
#include "datablock.h"
#include "vector"
#include <utility>  

using namespace std;

class Database{
private:
    vector<DataBlock> freeBlocks;
    vector<DataBlock> blocksList;
    int MAXSIZE;
    int blockSize;
public:
    Database(int capacity, int blockSize);
    pair<DataBlock*,Record*> addRecord(Record record);
    int getNumBlocks();
    unsigned int getSize();
};

