//
// Created by praty on 10/9/2022.
//
#pragma once
#include "storage.h"
#include "vector"

class DataBlock : Block{


private:
    int numRecords;
    bool hasCapacity(Record rec);

public:
    vector<Record> recordList;
    DataBlock();
    // ~ DataBlock();
    void insertRecord (Record rec);
    void deleteRecord (Record rec);
    void printBlock();

};

