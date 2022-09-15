//
// Created by praty on 12/9/2022.
//
#include "../entities/datablock.h"
#include "../entities/datablock.cpp"
#include "../entities/storage.cpp"

#include <cstring>
int main(){

    DataBlock* blk1 = new DataBlock();

    Record* rec1 = new Record("t00000000",9.5,23);
    Record* rec2 = new Record("t00000001",9.0,20);
    blk1->insertRecord(*rec1);
    blk1->insertRecord(*rec2);
    blk1->printBlock();
    blk1->deleteRecord(*rec1);
    blk1->printBlock();


}