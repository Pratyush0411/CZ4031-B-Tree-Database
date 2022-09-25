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

pair<DataBlock*, Record*> Database::addRecord(Record rec) {
    if (sizeof(rec) > this->blockSize) {
        cout << "This record's size is larger than the block size"<<endl;
        return{NULL,NULL};
    }

    if (this->blocksList.size() == 0 || blocksList.back().hasCapacity(rec)==false) {
        if (sizeof(*this) + this->blockSize > this->MAXSIZE) {
            cout << "Disk storage is full, cannot allocate another block" << endl;
            return{ NULL,NULL };
        }
        DataBlock blk(this->blockSize);
        blocksList.push_back(blk);
    }

    Record* recPointer = blocksList.back().insertRecord(rec);
    return{ &blocksList.back(),recPointer };
}

int Database::getNumBlocks() {
    return this->blocksList.size();
}

unsigned int Database::getSize() {
    return sizeof(*this);
}

