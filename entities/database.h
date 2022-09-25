//
// Created by praty on 11/9/2022.
//

#pragma once
#include "storage.h"
#include "datablock.h"
#include "vector"

using namespace std;

class Database{
private:
    vector<DataBlock> freeBlocks;
    vector<DataBlock> blocksList;

public:
    Database(int capacity, int blockSize);
    static int MAXSIZE;
    int blockSize;
    void addNewBlock(DataBlock blk);
    void addRecord(Record record);
    int getNumBlocks();
    unsigned int getSize();
};

