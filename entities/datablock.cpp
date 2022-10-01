//
// Created by praty on 10/9/2022.
//

#include "datablock.h"
#include "iostream"
using namespace std;
bool DataBlock ::hasCapacity(Record rec) {

    int recordSize = sizeof(rec);
    int currentBlockSize = (recordList.size()-freeRecords.size())*recordSize;
    //cout << recordSize<< " "<< currentBlockSize<<;
    if (recordSize + currentBlockSize <= MAXSIZE) {
        return true;
    }
    return false;
}

int DataBlock::getNumFreeRecords()
{
    return freeRecords.size();
}


int DataBlock::insertRecord(Record rec) {

    if (this->hasCapacity(rec)){
        if (freeRecords.size() > 0) {
            int id = freeRecords.front();
            freeRecords.pop();
            recordList[id] = rec;
            return id;
        }
        else {
            this->recordList.push_back(rec);
            return this->recordList.size()-1;
        }
    }
    return -1;
}

bool DataBlock::deleteRecordByNumvotes(int numVotes)
{
    bool ans = false;
    for (int j = 0; j < recordList.size(); j++) {
        if (recordList[j].isDeleted == false && recordList[j].numVotes == numVotes) {
            recordList[j].isDeleted = true;
            freeRecords.push(j);
            ans = true;
        }
    }
    return ans;
}

bool DataBlock::deleteRecordByIndex(int index)
{
    cout << recordList[index].isDeleted << " " << recordList[index].tconst << endl;
    if(recordList[index].isDeleted == true) return false;
    recordList[index].isDeleted = true;
    freeRecords.push(index);
    return true;
}


void DataBlock::printBlock() {
    for (Record& rec:this->recordList){
        if(rec.isDeleted==false)
            cout << rec.tconst << " " <<rec.avgRating << " " <<rec.numVotes << endl;
    }
    cout << endl;
}


DataBlock::DataBlock(int blockSize) {
    this->MAXSIZE = blockSize;
}