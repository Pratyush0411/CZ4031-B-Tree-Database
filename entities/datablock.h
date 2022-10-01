//
// Created by praty on 10/9/2022.
//
#pragma once
#ifndef datablock_h
#define datablock_h
#include "storage.h"
#include "vector"
#include "queue"

class DataBlock : public Block
{
private:
    int MAXSIZE;
    // a queue to store index of deleted Records, will fill these locations with new Records
    queue<int> freeRecords;
    // a vector to store all records;

public:
    vector<Record> recordList;
    DataBlock(int blockSize);
    // ~ DataBlock();
    int insertRecord(Record rec);
    bool deleteRecordByNumvotes(int numVotes);
    bool deleteRecordByIndex(int index);
    void printBlock();
    bool hasCapacity(Record rec);
    int getNumFreeRecords();
};

#endif