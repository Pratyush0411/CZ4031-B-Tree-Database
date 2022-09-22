#include "Storage2.h"
#include <iostream>
#include <vector>

using namespace std;

Database::Database(int MemSize, int BlkSize)
{
    this->MAXSIZE = MemSize;
    int sizeLeft = MemSize;
    while (sizeLeft >= BlkSize)
    {
        Block newBlk = Block(BlkSize);
        BlockList.push_back(newBlk.BlkPtr);
    }
};

Block::Block(int BlkSize)
{
    this->BlkSize = BlkSize;
    int sizeLeft = BlkSize;
    Record *CurPtr = (Record *)malloc(BlkSize);
    this->BlkPtr = (Block *)CurPtr;
    CurPtr = new Record();
    while (sizeLeft >= sizeof(Record))
    {
        CurPtr += 1;
        *CurPtr = Record();
        sizeLeft -= sizeof(Record);
    }
};

Record::Record()
{
    this->used = false;
    this->tconst = "";
    this->avgRating = 0;
    this->numVotes = 0;
}