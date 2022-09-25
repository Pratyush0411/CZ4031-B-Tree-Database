//
// Created by praty on 11/9/2022.
//

#include "database.h"
#include "datablock.h"
#include "iostream"

Database::Database(int capacity, int blockSize) {
    this->MAXSIZE = capacity;
    this->blockSize = blockSize;
}

void Database:: addNewBlock(DataBlock blk){
    this->blocksList.push_back(blk);
}

void Database::addRecord(Record record)
{
}

void Database::addRecord(Record rec) {
    if (sizeof(rec) > this->blockSize) {
        cout << "This record's size is larger than the block size"<<endl;
        return;
    }

    if (this->blocksList.size() == 0 || blocksList.back().hasCapacity(rec)==false) {
        if (sizeof(*this) + this->blockSize > this->MAXSIZE) {
            cout << "Disk storage is full, cannot allocate another block" << endl;
            return;
        }
        DataBlock blk(this->blockSize);
        blocksList.push_back(blk);
    }

    blocksList.back().insertRecord(rec);
}

int Database::getNumBlocks() {
    return this->blocksList.size();
}

unsigned int Database::getSize() {
    return sizeof(*this);
}

