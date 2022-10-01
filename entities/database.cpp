//
// Created by praty on 11/9/2022.
//

#include "database.h"
#include "datablock.h"
#include "iostream"

Database::Database(int capacity, int blockSize)
{
    this->MAXSIZE = capacity;
    this->blockSize = blockSize;
}

DataBlock *Database::getFirstBlock()
{
    return &this->blocksList[0];
}

pair<DataBlock *, int> Database::addRecord(Record rec)
{
    cout << "size of record is: " << sizeof(rec) << endl;
    if (sizeof(rec) > this->blockSize)
    {
        cout << "This record's size is larger than the block size" << endl;
        return {NULL, -1};
    }

    // insert Record into a block that has unused space (for a deleted record);
    if (freeBlocks.size())
    {
        DataBlock *blk = *freeBlocks.begin();
        int recIndex = blk->insertRecord(rec);
        if (blk->getNumFreeRecords() == 0)
        {
            freeBlocks.erase(freeBlocks.begin());
        }
        // cout << "added to " << id << " block"<<endl;
        return {blk, recIndex};
    }

    // add new block
    if (this->blocksList.size() == 0 || blocksList.back().hasCapacity(rec) == false)
    {
        cout << "Creating new block" << endl;
        if (this->blockSize * (blocksList.size() + 1) > this->MAXSIZE)
        {
            cout << "Disk storage is full, cannot allocate another block" << endl;
            return {NULL, -1};
        }
        DataBlock blk(this->blockSize);
        blocksList.push_back(blk);
    }

    // insert Record into the last block;
    int recIndex = blocksList.back().insertRecord(rec);
    // cout << "added to the last block"<<endl;
    return {&blocksList.back(), recIndex};
}

void Database::deleteRecordByNumvotes(int numVotes)
{
    for (int i = 0; i < blocksList.size(); i++)
    {
        if (blocksList[i].deleteRecordByNumvotes(numVotes))
        {
            freeBlocks.insert(&blocksList[i]);
        }
    }
}

bool Database::deleteRecordfromBtree(DataBlock *blkPointer, int recordIndex)
{

    if (blkPointer->deleteRecordByIndex(recordIndex))
    {
        cout << "Updating freeblock" << endl;
        freeBlocks.insert(blkPointer);
        return true;
    }
    return false;
}

int Database::getNumBlocks()
{
    return this->blocksList.size();
}

unsigned int Database::getSize()
{
    return this->blockSize * blocksList.size();
}
