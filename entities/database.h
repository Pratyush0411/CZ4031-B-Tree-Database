//
// Created by praty on 11/9/2022.
//

#pragma once
#include "storage.h"
#include "vector"

using namespace std;

class Database{
private:
    vector<Block> freeBlocks;
    vector<Block> blocksList;

public:
    Database(int capacity, int blockSize);
    static int MAXSIZE;
    int blockSize;
    void addNewBlock(Block blk);
    void addRecord(Record record);
    int getNumBlocks();
    unsigned int getSize();
};