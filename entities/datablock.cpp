//
// Created by praty on 10/9/2022.
//

#include "datablock.h"
#include "iostream"
using namespace std;
bool DataBlock ::hasCapacity(Record rec) {

    int recordSize = sizeof(rec);
    int currentBlockSize = sizeof(*this);

    if (recordSize + currentBlockSize <= MAXSIZE){
        return true;
    }
    else
        return false;
}


void DataBlock::insertRecord(Record rec) {

    if (this->hasCapacity(rec)){
        this->recordList.push_back(rec);
        this->numRecords ++;
    }
}

void DataBlock::deleteRecord(Record rec) {

    int pos = 0;
    bool foundFlag = false;
    for (Record iter: this->recordList){
        if (iter == rec)
        {

            foundFlag = true;
            break;
        }
        else
            pos++;

    }
    if (foundFlag) {
        cout << "Erasing data .." << endl;
        this->recordList.erase(recordList.begin() + pos);
    }


}

void DataBlock::printBlock() {
    for (Record rec:this->recordList){
        cout << rec.tconst << " " <<rec.avgRating << " " <<rec.numVotes << endl;
    }
}


DataBlock::DataBlock() {

    this->numRecords = 0;
}