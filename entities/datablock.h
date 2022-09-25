//
// Created by praty on 10/9/2022.
//
#pragma once
#include "storage.h"
#include "vector"

class DataBlock : public Block{


private:
    int numRecords;

public:
    vector<Record> recordList;
    DataBlock(int blockSize);
    // ~ DataBlock();
    void insertRecord (Record rec);
    void deleteRecord (Record rec);
    void printBlock();
    bool hasCapacity(Record rec);
};

