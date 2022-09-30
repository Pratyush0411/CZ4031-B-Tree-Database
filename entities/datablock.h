//
// Created by praty on 10/9/2022.
//
#pragma once
#include "storage.h"
#include "vector"
#include "queue"

class DataBlock : public Block{
private:
    int MAXSIZE;
    // a queue to store index of deleted Records, will fill these locations with new Records
    queue<int> freeRecords;
    // a vector to store all records;
    vector<Record> recordList;
public:
    DataBlock(int blockSize);
    // ~ DataBlock();
    Record* insertRecord (Record rec);
    bool deleteRecordByNumvotes (int numVotes);
    void printBlock();
    bool hasCapacity(Record rec);
    int getNumFreeRecords();
};

