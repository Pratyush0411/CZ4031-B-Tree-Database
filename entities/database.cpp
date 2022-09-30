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

    // insert Record into a block that has unused space (for a deleted record);
    if (freeBlocks.size()) {
        int id = *freeBlocks.begin();
        Record* recPointer = blocksList[id].insertRecord(rec);
        if (blocksList[id].getNumFreeRecords() == 0) {
            freeBlocks.erase(freeBlocks.begin());
        }
        //cout << "added to " << id << " block"<<endl;
        return { &blocksList[id],recPointer };
    }

    // add new block
    if (this->blocksList.size() == 0 || blocksList.back().hasCapacity(rec)==false) {
        if (this->blockSize *(blocksList.size()+1) > this->MAXSIZE) {
            cout << "Disk storage is full, cannot allocate another block" << endl;
            return{ NULL,NULL };
        }
        DataBlock blk(this->blockSize);
        blocksList.push_back(blk);
    }

    // insert Record into the last block;
    Record* recPointer = blocksList.back().insertRecord(rec);
    //cout << "added to the last block"<<endl;
    return{ &blocksList.back(),recPointer };
}

void Database::deleteRecordByNumvotes(int numVotes){
    for (int i = 0; i < blocksList.size(); i++) {
        if (blocksList[i].deleteRecordByNumvotes(numVotes)) {
            freeBlocks.insert(i);
        }
    }
}

int Database::getNumBlocks() {
    return this->blocksList.size();
}

unsigned int Database::getSize() {
    return this->blockSize *blocksList.size();
}

