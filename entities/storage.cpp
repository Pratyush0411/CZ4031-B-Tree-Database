//
// Created by praty on 8/9/2022.
//
#include <iostream>
#include "storage.h"
#include "cstring"

int Block::getBlkSize() {
    return sizeof(*this);
}

bool Record:: operator == (Record rhs){

    if (this->avgRating == rhs.avgRating && strcmp(this->tconst,rhs.tconst)==0
    && this->numVotes == rhs.numVotes){
        return true;
    }
    else{
        return false;
    }

}
/*
Record::Record(string tconst, float averageRating, uint numVotes) {
    strcpy(this->tconst,tconst.c_str());
    this->avgRating = averageRating;
    this->numVotes = numVotes;

}
*/
int Block::MAXSIZE = 200;
